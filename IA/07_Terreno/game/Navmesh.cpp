#include <stdafx.h>
#include "Navmesh.h"
#include "tinyxml.h"

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

void Navmesh::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    for (const Polygon* iterator : polygonsVector)
    {
        device.SetPenColor(0.f, 0.5f, 0.1f, 0.5f);
        MOAIDraw::DrawPolygonFilled(iterator->vertex);
        device.SetPenColor(0.f, 1.f, 0.0f, 0.5f);
        MOAIDraw::DrawPolygon(iterator->vertex);

        device.SetPenColor(1.f, 0.f, 0.f, 0.4f);
        for (const Link& linkIterator : iterator->links)
        {
            USVec2D startEdge = iterator->vertex.at(linkIterator.start);
            USVec2D endEdge = iterator->vertex.at(linkIterator.end);

            USVec2D centerEdge = endEdge - startEdge;
            centerEdge *= 0.5f;
            centerEdge += startEdge;
            MOAIDraw::DrawEllipseFill(centerEdge.mX, centerEdge.mY, 5.f, 5.f, 10);
        }
    }
}
