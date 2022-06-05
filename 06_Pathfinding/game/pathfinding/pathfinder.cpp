#include <stdafx.h>
#include <algorithm>

#include "pathfinder.h"
#include "Node.h"

Pathfinder::Pathfinder() : MOAIEntity2D(), m_StartPosition(0.f, 0.f), m_EndPosition(0.f, 0.f)
{
    RTTI_BEGIN
    RTTI_EXTEND(MOAIEntity2D)
    RTTI_END

    grid = Grid::LoadMap("map.txt", "codeMap.txt");
    currentNode = nullptr;
}

Pathfinder::~Pathfinder()
{
    path.clear();
    openNodes.clear();
    closeNodes.clear();
}

void Pathfinder::UpdatePath()
{
    openNodes.clear();
    closeNodes.clear();
    path.clear();
    openNodes.push_back(new Node(nullptr, gridStartPosition, 0, HeuristicCalculation(gridStartPosition)));
}

float Pathfinder::HeuristicCalculation(const USVec2D& _point)
{
    return fabsf(_point.mX - gridEndPosition.mX) + fabsf(_point.mY - gridEndPosition.mY);
}

void Pathfinder::PathFill(Node* _end)
{
    Node* auxNode = _end;
    while (auxNode)
    {
        path.insert(path.begin(), auxNode);
        auxNode = auxNode->parent;
    }
}

Node* Pathfinder::GetVectorNode(std::vector<Node*>& _vector, const USVec2D& _nodePos) const
{
    for (auto iter : _vector)
    {
        if (iter->position.Equals(_nodePos))
        {
            return iter;
        }
    }

    return nullptr;
}

void Pathfinder::DrawNodes(const std::vector<Node*>& _vector, float _radius, const USVec4D& _color) const
{
    for (auto iter : _vector)
    {
        USVec2D center = grid->LocationGridToWorld(iter->position);
        center += grid->GetRectSize() * 0.5f;
        MOAIGfxDevice::Get().SetPenColor(_color.mX, _color.mY, _color.mY, _color.mW);
        MOAIDraw::DrawEllipseFill(center.mX, center.mY, _radius, _radius, 12);
    }
}

void Pathfinder::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    grid->DrawDebug();

    device.SetPenColor(0.f, 0.9f, 0.6f, 1.f);
    USVec2D onStart = grid->LocationGridToWorld(gridStartPosition);

    onStart += grid->GetRectSize() * 0.5f;
    MOAIDraw::DrawEllipseFill(onStart.mX, onStart.mY, 12.f, 12.f, 12);

    device.SetPenColor(0.3f, 0.1f, 1.f, 1.f);
    USVec2D onEnd = grid->LocationGridToWorld(gridEndPosition);

    onEnd += grid->GetRectSize() * 0.5f;
    MOAIDraw::DrawEllipseFill(onEnd.mX, onEnd.mY, 12.f, 12.f, 12);

    DrawNodes(closeNodes, 5.f, USVec4D(0.f, 0.f, 0.5f, 1.f));
    DrawNodes(openNodes, 5.f, USVec4D(0.1f, 0.7f, 0.2f, 1.f));
    DrawNodes(path, 5.f, USVec4D(0.2f, 0.9f, 0.1f, 1.f));
}

bool Pathfinder::PathfindStep()
{
    if (path.empty())
    {

        std::sort(openNodes.begin(), openNodes.end(),
            [](const Node* first, const Node* second) -> bool
        {
            return first->GetCost() < second->GetCost();
        }
        );

        currentNode = openNodes.at(0);
        openNodes.erase(openNodes.begin());
        closeNodes.push_back(currentNode);

        if (currentNode->position.Equals(gridEndPosition))
        {
            PathFill(currentNode);
            return true;
        }

        static const std::vector<USVec2D> deltaPos = {
             {-1.f, 0.f}, {0.f, 1.f},
             {1.f, 0.f},  {0.f, -1.f}
        };

        for (auto& deltaPosition : deltaPos)
        {
            const USVec2D nextPos = currentNode->position + deltaPosition;

            if (grid->PositionIsValid(nextPos) && grid->GetCost(nextPos) >= 0.f)
            {
                auto nodeRep = GetVectorNode(closeNodes, nextPos);

                if (nodeRep == nullptr)
                {
                    nodeRep = GetVectorNode(openNodes, nextPos);
                    const float gCost = currentNode->gCost + grid->GetCost(nextPos);
                    const float hCost = HeuristicCalculation(nextPos);

                    if (nodeRep == nullptr)
                    {
                        auto nodeAux = new Node(currentNode, nextPos, gCost, hCost);
                        openNodes.push_back(nodeAux);
                    }
                    else
                    {
                        if (gCost < nodeRep->gCost)
                        {
                            nodeRep->gCost = gCost;
                            nodeRep->parent = currentNode;
                        }
                    }
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