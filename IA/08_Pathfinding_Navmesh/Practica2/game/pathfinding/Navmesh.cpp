#include <stdafx.h>
#include "Navmesh.h"
#include "tinyxml.h"

USVec2D Polygon::GetMiddlePoint(const Link& _link) const
{
    const USVec2D start = vertex.at(_link.start);
    const USVec2D end = vertex.at(_link.end);

    return start + (end - start) * 0.5f;
}

USVec2D Polygon::GetCenter() const
{
    USVec2D center(0.f, 0.f);
    float area = 0.f;

    for (size_t i = 0; i < vertex.size(); ++i)
    {
        USVec2D v1(vertex.at(i).mX, vertex.at(i).mY);
        USVec2D v2(vertex.at((i + 1) % vertex.size()).mX, vertex.at((i + 1) % vertex.size()).mY);

        float aux = (v1.mX * v2.mY) - (v1.mY * v2.mX);
        area += aux;

        center.mX += (v1.mX + v2.mX) * aux;
        center.mY += (v1.mY + v2.mY) * aux;
    }

    return center;
}

bool Polygon::IsInside(const USVec2D& _point) const
{
    bool inside = false;

    for (int32_t i = 0, aux = vertex.size() - 1; i < vertex.size(); aux = i++)
    {
        USVec2D v1 = vertex.at(i);
        USVec2D v2 = vertex.at(aux);

        if ((v1.mY > _point.mY != v2.mY > _point.mY) &&
            (_point.mX < (v2.mX - v1.mX) * (_point.mY - v1.mY) / (v2.mY - v1.mY) + v1.mX))
        {
            inside = !inside;
        }
    }

    return inside;
}

Navmesh::~Navmesh()
{
    printf("Navmesh Object deleted.\n");
}

Navmesh* Navmesh::LoadNavmesh(const char* _fileName)
{
    TiXmlDocument document(_fileName);

    if (!document.LoadFile())
    {
        return nullptr;
    }

    TiXmlHandle documentHandle(&document);
    TiXmlElement* element = documentHandle.FirstChildElement().Element();

    if (!element)
    {
        return nullptr;
    }

    auto auxNavmesh = new Navmesh();

    // Polygons

    TiXmlHandle rootHandle(element);
    TiXmlHandle polygonsHandle = rootHandle.FirstChildElement("polygons");

    TiXmlElement* polygonElement = polygonsHandle.FirstChildElement("polygon").Element();

    for (polygonElement; polygonElement; polygonElement = polygonElement->NextSiblingElement())
    {
        auto auxPolygon = new Polygon();
        TiXmlElement* pointElement = polygonElement->FirstChildElement("point");

        for (pointElement; pointElement; pointElement = pointElement->NextSiblingElement())
        {
            float x = 0.f, y = 0.f;
            pointElement->Attribute("x", &x);
            pointElement->Attribute("y", &y);
            auxPolygon->vertex.push_back(USVec2D(x, y));
        }

        auxNavmesh->polygonsVector.push_back(auxPolygon);
    }

    // Links

    TiXmlHandle linkHandle = rootHandle.FirstChildElement("links");
    TiXmlElement* elementLink = linkHandle.FirstChildElement("link").Element();

    for (elementLink; elementLink; elementLink = elementLink->NextSiblingElement())
    {
        // Sub element start (<start polygon="x" edgestart="x" edgeend="x"/>) 
        TiXmlElement* subElementStart = elementLink->FirstChildElement("start");
        int32_t indexPolygon = 0;
        int32_t edgeStart = 0;
        int32_t edgeEnd = 0;

        subElementStart->Attribute("polygon", &indexPolygon);
        subElementStart->Attribute("edgestart", &edgeStart);
        subElementStart->Attribute("edgeend", &edgeEnd);

        // Sub element end (<end polygon="x" edgestart="x" edgeend="x"/>)
        TiXmlElement* subElementEnd = elementLink->FirstChildElement("end");
        int32_t endIndexPolygon = 0;
        int32_t endEdgeStart = 0;
        int32_t endEdgeEnd = 0;

        subElementEnd->Attribute("polygon", &endIndexPolygon);
        subElementEnd->Attribute("edgestart", &endEdgeStart);
        subElementEnd->Attribute("edgeend", &endEdgeEnd);

        Polygon* firstPolygon = auxNavmesh->polygonsVector.at(indexPolygon);
        Polygon* secondPolygon = auxNavmesh->polygonsVector.at(endIndexPolygon);

        Link firstLink;
        firstLink.polygon = secondPolygon;
        firstLink.start = edgeStart;
        firstLink.end = edgeEnd;
        firstPolygon->links.push_back(firstLink);

        Link secondLink;
        secondLink.polygon = firstPolygon;
        secondLink.start = endEdgeStart;
        secondLink.end = endEdgeEnd;
        secondPolygon->links.push_back(secondLink);
    }

    return auxNavmesh;
}

const Polygon* Navmesh::GetPolygon(const USVec2D& _position) const
{
    for (const auto iterator : polygonsVector)
    {
        if (iterator->IsInside(_position))
        {
            return iterator;
        }
    }

    return nullptr;
}

Polygon* Navmesh::GetPolygon(const USVec2D& _position)
{
    for (auto iterator : polygonsVector)
    {
        if (iterator->IsInside(_position))
        {
            return iterator;
        }
    }

    return nullptr;
}

bool Navmesh::StartPolygon(const USVec2D& _position)
{
    startPolygon = GetPolygon(_position);

    return startPolygon != nullptr;
}

bool Navmesh::EndPolygon(const USVec2D& _position)
{
    endPolygon = GetPolygon(_position);

    return endPolygon != nullptr;
}

const Polygon* Navmesh::GetStartPolygon() const
{
    return startPolygon;
}

const Polygon* Navmesh::GetEndPolygon() const
{
    return endPolygon;
}

void Navmesh::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    for (const auto iterator : polygonsVector)
    {
        if (iterator == startPolygon)
        {
            device.SetPenColor(0.f, 0.2f, 0.f, 0.9f);
            MOAIDraw::DrawPolygonFilled(iterator->vertex);
            device.SetPenColor(1.f, 0.f, 0.f, 0.5f);
            MOAIDraw::DrawPolygon(iterator->vertex);
        }
        else if (iterator == endPolygon)
        {
            device.SetPenColor(0.f, 0.f, 0.f, 0.8f);
            MOAIDraw::DrawPolygonFilled(iterator->vertex);
            device.SetPenColor(1.f, 0.f, 0.f, 0.5f);
            MOAIDraw::DrawPolygon(iterator->vertex);
        }
        else
        {
            device.SetPenColor(0.f, 0.2f, 0.f, 0.2f);
            MOAIDraw::DrawPolygonFilled(iterator->vertex);
            device.SetPenColor(0.f, 1.f, 0.f, 0.5f);
            MOAIDraw::DrawPolygon(iterator->vertex);
        }

        device.SetPenColor(0.4f, 0.1f, 0.6f, 0.4f);

        for (const Link& iteratorLink : iterator->links)
        {
            USVec2D startEdge = iterator->vertex.at(iteratorLink.start);
            USVec2D endEdge = iterator->vertex.at(iteratorLink.end);

            USVec2D centerEdge = endEdge - startEdge;
            centerEdge *= 0.5f;
            centerEdge += startEdge;
            MOAIDraw::DrawEllipseFill(centerEdge.mX, centerEdge.mY, 5.f, 5.f, 10);
        }
    }
}