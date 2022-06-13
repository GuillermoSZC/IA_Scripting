#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>
#include "AlignToMovementSteering.h"
#include "ArriveSteering.h"

namespace MathFunctions
{
    void NormalizeRadianToAngles(float& angleInRadians)
    {
        if (angleInRadians < -PI || angleInRadians > PI)
        {
            const int rounds = fmodf(angleInRadians, PI);
            angleInRadians += 2 * PI * -1.f * rounds;
        }
    }

    void NormalizeDegreeToAngles(float& angleInDegrees)
    {
        if (angleInDegrees < -180.f || angleInDegrees > 180.f)
        {
            const int rounds = fmodf(angleInDegrees, 180.f);
            angleInDegrees += 2 * 180.f * -1.f * rounds;
        }
    }

    float DegreesToRadians(float angleInDegrees)
    {
        return angleInDegrees * PI / 180.f;
    }

    float RadiansToDegrees(float angleInRadians)
    {
        return angleInRadians * 180.f / PI;
    }
}

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f), steering(nullptr)
{
    RTTI_BEGIN
    RTTI_EXTEND(MOAIEntity2D)
    RTTI_END
}

Character::~Character()
{
    delete steering;
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

void Character::SetParams(Params& _params)
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

    steering = new ArriveSteering(this);
    steering->SetDelegate(new AlignToMovementSteering(this));
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
    MOAIEntity2D::OnUpdate(step);

    SteeringOperations operationsObj = steering->GetSteering();
    mLinearVelocity += operationsObj.linear * step;
    mAngularVelocity += operationsObj.angular * step;
    SetLoc(GetLoc() + mLinearVelocity * step);
    SetRot(GetRot() + mAngularVelocity * step);
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

    steering->DrawDebug();
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
