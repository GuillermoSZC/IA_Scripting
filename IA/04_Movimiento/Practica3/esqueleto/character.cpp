#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f), steering(this), alignSteering(this)
{
    RTTI_BEGIN
        RTTI_EXTEND(MOAIEntity2D)
        RTTI_END
}

Character::~Character()
{

}

#pragma region GETTERS_AND_SETTERS
void Character::SetPosition(USVec2D& _position)
{
    position = _position;
}

void Character::SetAcceleration(USVec2D& _acceleration)
{
    acceleration = _acceleration;
}

void Character::SetParams(Params _params)
{
    mParams = _params;
}

USVec2D Character::GetPosition() const
{
    return position;
}

USVec2D Character::GetAcceleration() const
{
    return acceleration;
}

const Params& Character::GetParams() const
{
    return mParams;
}
#pragma endregion

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
    MOAIEntity2D::OnUpdate(step);

    mAngularVelocity += alignSteering.GetSteering() * step;

    rotation = GetRot();
    rotation += mAngularVelocity * step;
    SetRot(rotation);

    /*mLinearVelocity += steering.GetSteering(mParams.targetPosition) * step;

    position = GetLoc();
    position += mLinearVelocity * step;
    SetLoc(position);*/
}

void Character::DrawDebug()
{
    USVec2D pos;
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    // Linear velocity
    device.SetPenColor(0.f, 0.f, 1.f, 1.f);
    pos = GetLoc();
    MOAIDraw::DrawLine(pos.mX, pos.mY, pos.mX + mLinearVelocity.mX, pos.mY + mLinearVelocity.mY);

    // Target
    device.SetPenColor(0.f, 1.f, 1.f, 1.f);
    MOAIDraw::DrawPoint(mParams.targetPosition.mX, mParams.targetPosition.mY);

    // Arrive radius
    device.SetPenColor(1.f, 0.f, 1.f, 1.f);
    MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.arrive_radius, mParams.arrive_radius, 10);

    // Dest radius
    device.SetPenColor(1.f, 0.5f, 1.f, 1.f);
    MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.dest_radius, mParams.dest_radius, 10);

    alignSteering.DrawDebug();
}

// Lua configuration
void Character::RegisterLuaFuncs(MOAILuaState& state)
{
    MOAIEntity2D::RegisterLuaFuncs(state);

    luaL_Reg regTable[] = {
        { "setLinearVel",			_setLinearVel},
        { "setAngularVel",			_setAngularVel},
        { NULL, NULL }
    };

    luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

        float pX = state.GetValue<float>(2, 0.0f);
    float pY = state.GetValue<float>(3, 0.0f);
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
