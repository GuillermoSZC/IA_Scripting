#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <moaicore/MOAIEntity2D.h>
#include "NavMesh.h"
#include "Path.h"

class Node;


class Pathfinder : public virtual MOAIEntity2D
{
public:
    Pathfinder();
    ~Pathfinder();

    virtual void DrawDebug();

    void SetStartPosition(float x, float y);

    void SetEndPosition(float x, float y);


    const USVec2D& GetStartPosition() const { return m_StartPosition; }
    const USVec2D& GetEndPosition() const { return m_EndPosition; }

    bool PathfindStep();

    const Path* GetPath() const { return path; }
    bool PathCompleted() const { return !path->EmptyPath(); }


private:
    void UpdatePath();
    float HeuristicCalculation(const USVec2D& _point) const;
    void Clear();
    void PathFill(const Node* _end);
    Node* GetVectorNode(std::vector<Node*>& _vector, const Polygon* _polygon);

private:
    USVec2D m_StartPosition;
    USVec2D m_EndPosition;

    Pathfinder* owner;
    Navmesh* navmesh;
    Path* path;

    std::vector<Node*> openNodes;
    std::vector<Node*> closeNodes;

    // Lua configuration
public:
    DECL_LUA_FACTORY(Pathfinder)
public:
    virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
    static int _setStartPosition(lua_State* L);
    static int _setEndPosition(lua_State* L);
    static int _pathfindStep(lua_State* L);
};


#endif
