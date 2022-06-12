#include <stdafx.h>
#include <algorithm>

#include "pathfinder.h"
#include "Node.h"
#include "Path.h"

Pathfinder::Pathfinder() : MOAIEntity2D()
{
    RTTI_BEGIN
        RTTI_EXTEND(MOAIEntity2D)
        RTTI_END

        navmesh = Navmesh::LoadNavmesh("map.xml");
    path = new Path();

}

Pathfinder::~Pathfinder()
{
    Clear();
}

void Pathfinder::UpdatePath()
{
    Clear();

    Polygon* start = navmesh->GetPolygon(m_StartPosition);
    if (start)
    {
        openNodes.push_back(new Node(nullptr, m_StartPosition, start, 0, HeuristicCalculation(m_StartPosition)));
    }

}

float Pathfinder::HeuristicCalculation(const USVec2D& _point) const
{
    return _point.DistSqrd(m_EndPosition);
}

void Pathfinder::Clear()
{
    for (Node*& iterator : openNodes)
    {
        if (iterator)
        {
            delete iterator;
            iterator = nullptr;
        }
    }

    for (Node*& iterator : closeNodes)
    {
        if (iterator)
        {
            delete iterator;
            iterator = nullptr;
        }
    }

    path->Clear();
    openNodes.clear();
    closeNodes.clear();

}

void Pathfinder::PathFill(const Node* _end)
{
    const Node* it = _end;
    path->AddPoint(m_EndPosition);
    while (it)
    {
        path->AddPoint(it->position);
        it = it->parent;
    }
}

Node* Pathfinder::GetVectorNode(std::vector<Node*>& _vector, const Polygon* _polygon)
{
    for (Node* iter : _vector)
    {
        if (iter->polygon == _polygon)
        {
            return iter;
        }
    }

    return nullptr;
}

void Pathfinder::DrawDebug()
{
    navmesh->DrawDebug();

    MOAIGfxDevice& device = MOAIGfxDevice::Get();


    device.SetPenColor(0.f, 0.9f, 0.6f, 1.f);
    MOAIDraw::DrawEllipseFill(m_StartPosition.mX, m_StartPosition.mY, 12.f, 12.f, 12);
    device.SetPenColor(0.9f, 0.2f, 0.5f, 1.f);
    MOAIDraw::DrawEllipseFill(m_EndPosition.mX, m_EndPosition.mY, 12.f, 12.f, 12);


    device.SetPenColor(0.8f, 0.3f, 0.3f, 1.f);
    for (Node* iterator : openNodes)
    {
        if (iterator)
        {
            MOAIDraw::DrawEllipseFill(iterator->position.mX, iterator->position.mY, 5.f, 5.f, 10);
        }
    }

    device.SetPenColor(0.3f, 0.3f, 0.3f, 1.f);
    for (Node* iterator : closeNodes)
    {
        if (iterator)
        {
            MOAIDraw::DrawEllipseFill(iterator->position.mX, iterator->position.mY, 5.f, 5.f, 10);
        }
    }

    path->DrawDebug();
}

void Pathfinder::SetStartPosition(float x, float y)
{
    m_StartPosition = USVec2D(x, y);
    navmesh->StartPolygon(m_StartPosition);
    UpdatePath();
}

void Pathfinder::SetEndPosition(float x, float y)
{
    m_EndPosition = USVec2D(x, y);
    navmesh->EndPolygon(m_EndPosition);
    UpdatePath();
}

bool Pathfinder::PathfindStep()
{
    if (path->EmptyPath())
    {

        std::sort(openNodes.begin(), openNodes.end(),
            [](const Node* first, const Node* second) -> bool
        {
            return first->GetCost() < second->GetCost();
        }
        );

        Node* currentNode = openNodes.at(0);
        openNodes.erase(openNodes.begin());
        closeNodes.push_back(currentNode);

        if (currentNode->polygon == navmesh->GetEndPolygon())
        {
            PathFill(currentNode);
            return true;
        }

        for (auto& iterator : currentNode->polygon->links)
        {
            Polygon* nextPolygon = iterator.polygon;
            Node* auxNode = GetVectorNode(closeNodes, nextPolygon);
            if (!auxNode)
            {
                auxNode = GetVectorNode(openNodes, nextPolygon);
                const float gCost = currentNode->gCost + 1.f;
                if (auxNode)
                {
                    if (gCost < auxNode->gCost)
                    {
                        auxNode->gCost = gCost;
                        auxNode->parent = currentNode;
                    }
                }
                else
                {
                    const USVec2D position = currentNode->polygon->GetMiddlePoint(iterator);
                    auto node = new Node(currentNode, position, nextPolygon, gCost, HeuristicCalculation(position));
                    openNodes.push_back(node);
                }
            }
        }
    }

    return false;
}

//lua configuration ----------------------------------------------------------------//
void Pathfinder::RegisterLuaFuncs(MOAILuaState& state)
{
    MOAIEntity::RegisterLuaFuncs(state);

    luaL_Reg regTable[] = {
            {"setStartPosition", _setStartPosition},
            {"setEndPosition", _setEndPosition},
            {"pathfindStep", _pathfindStep},
            {nullptr, nullptr}
    };

    luaL_register(state, nullptr, regTable);
}

int Pathfinder::_setStartPosition(lua_State* L)
{
    MOAI_LUA_SETUP(Pathfinder, "U")

        float pX = state.GetValue<float>(2, 0.0f);
    float pY = state.GetValue<float>(3, 0.0f);
    self->SetStartPosition(pX, pY);
    return 0;
}

int Pathfinder::_setEndPosition(lua_State* L)
{
    MOAI_LUA_SETUP(Pathfinder, "U")

        float pX = state.GetValue<float>(2, 0.0f);
    float pY = state.GetValue<float>(3, 0.0f);
    self->SetEndPosition(pX, pY);
    return 0;
}

int Pathfinder::_pathfindStep(lua_State* L)
{
    MOAI_LUA_SETUP(Pathfinder, "U")

        self->PathfindStep();
    return 0;
}