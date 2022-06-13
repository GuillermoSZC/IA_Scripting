#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <moaicore/MOAIEntity2D.h>
#include "Grid.h"

class Node;

class Pathfinder : public virtual MOAIEntity2D
{
public:
    Pathfinder();
    ~Pathfinder();

public:
    DECL_LUA_FACTORY(Pathfinder)

protected:


private:
    USVec2D m_StartPosition;
    USVec2D m_EndPosition;

    USVec2D gridStartPosition;
    USVec2D gridEndPosition;

    Grid* grid;
    Node* currentNode;

    std::vector<Node*> openNodes;
    std::vector<Node*> closeNodes;
    std::vector<Node*> path;

    // Lua configuration

public:
    void SetStartPosition(float x, float y)
    {
        m_StartPosition = USVec2D(x, y);
        gridStartPosition = grid->LocationWorldToGrid(m_StartPosition);
        UpdatePath();
    }

    void SetEndPosition(float x, float y)
    {
        m_EndPosition = USVec2D(x, y);
        gridEndPosition = grid->LocationWorldToGrid(m_EndPosition);
        UpdatePath();
    }

    const USVec2D& GetStartPosition() const { return m_StartPosition; }
    const USVec2D& GetEndPosition() const { return m_EndPosition; }

    bool PathfindStep();

    virtual void RegisterLuaFuncs(MOAILuaState& state);
    virtual void DrawDebug();

protected:


private:
    void UpdatePath();

    float HeuristicCalculation(const USVec2D& _point);
    void PathFill(Node* _end);
    Node* GetVectorNode(std::vector<Node*>& _vector, const USVec2D& _nodePos) const;
    void DrawNodes(const std::vector<Node*>& _vector, float _radius, const USVec4D& _color) const;

    static int _setStartPosition(lua_State* L);
    static int _setEndPosition(lua_State* L);
    static int _pathfindStep(lua_State* L);
};
#endif