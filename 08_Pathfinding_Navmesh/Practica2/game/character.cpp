#include <stdafx.h>
#include "character.h"
#include "pathfinding/pathfinder.h"
#include "steering/PathFollowing.h"
#include "steering/AlignToMovementSteering.h"

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
    RTTI_BEGIN
    RTTI_EXTEND(MOAIEntity2D)
    RTTI_END
    
    steeringVector.push_back(new PathFollowing(this));
    steeringVector.push_back(new AlignToMovementSteering(this));
    pathfinder = new Pathfinder();
    params.LoadXML("params.xml");
}

Character::~Character()
{

}

void Character::OnStart()
{

}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
    if (pathfinder->PathCompleted())
    {
        SteeringOperations operations;

        for (auto iterator : steeringVector)
        {
            operations += iterator->GetSteering(USVec2D());
        }

        mLinearVelocity += operations.linear * step;
        mAngularVelocity += operations.angular * step;
        SetLoc(mLinearVelocity * step + GetLoc());
        SetRot(mAngularVelocity * step + GetRot());
    }
    else
    {
        pathfinder->PathfindStep();
    }

}

void Character::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
    device.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

    pathfinder->DrawDebug();

    for (auto iterator : steeringVector)
    {
        iterator->DrawDebug();
    }

    //MOAIDraw::DrawPoint(0.0f, 0.0f);
}


// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
    MOAIEntity2D::RegisterLuaFuncs(state);

    luaL_Reg regTable[] = {
            {"setLinearVel", _setLinearVel},
            {"setAngularVel", _setAngularVel},
            {"setStartPosition", _setStartPosition},
            {"setEndPosition", _setEndPosition},
            {nullptr, nullptr}
    };

    luaL_register(state, nullptr, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

        float pX = state.GetValue<float>(2, 0.0f);
    float pY = state.GetValue<float>(2, 0.0f);
    self->SetLinearVelocity(pX, pY);
    return 0;
}

int Character::_setAngularVel(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

        float angle = state.GetValue<float>(2, 0.0f);
    self->SetAngularVelocity(angle);

    return 0;
}

int Character::_setStartPosition(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

        float x = state.GetValue<float>(2, 0.0f);
    float y = state.GetValue<float>(3, 0.0f);
    self->GetPathfinder()->SetStartPosition(x, y);
    self->SetLoc(USVec3D(x, y, 0.f));

    return 0;
}

int Character::_setEndPosition(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

        float x = state.GetValue<float>(2, 0.0f);
    float y = state.GetValue<float>(3, 0.0f);
    self->GetPathfinder()->SetEndPosition(x, y);

    return 0;
}