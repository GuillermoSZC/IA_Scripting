#include "stdafx.h"
#include "SeekSteering.h"
#include "character.h"

SeekSteering::SeekSteering(Character* _character)
{
    character = _character;
}

#pragma region GETTERS_AND_SETTERS
void SeekSteering::SetTarget(USVec3D& _target)
{
    target = _target;
}

void SeekSteering::SetVelocity(USVec3D& _velocity)
{
    desiredVelocity = _velocity;
}

void SeekSteering::SetAcceleration(USVec3D& _acceleration)
{
    acceleration = _acceleration;
}

void SeekSteering::SetPosition(USVec2D& _position)
{
    position = _position;
}

void SeekSteering::SetDelta(USVec2D& _delta)
{
    delta = _delta;
}

USVec3D SeekSteering::GetTarget() const
{
    return target;
}

USVec3D SeekSteering::GetVelocity() const
{
    return desiredVelocity;
}

USVec3D SeekSteering::GetAcceleration() const
{
    return acceleration;
}
#pragma endregion

USVec3D SeekSteering::GetSteering()
{
    if (character)
    {
        target = character->GetParams().targetPosition;
        desiredVelocity = target - character->GetLoc();

        USVec3D accel = desiredVelocity - character->GetLinearVelocity();
        accel.NormSafe();
        acceleration = accel * character->GetParams().max_acceleration;

        return acceleration;
    }

    return USVec3D();
}

USVec2D SeekSteering::GetPosition() const
{
    return position;
}

USVec2D SeekSteering::GetDelta() const
{
    return delta;
}

void SeekSteering::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    position = character->GetLoc();
    delta = position + desiredVelocity;
    device.SetPenColor(0.9f, 0.9f, 0.5f, 1.f);
    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);

    delta = position + acceleration;
    device.SetPenColor(1.f, 0.f, 0.1f, 1.f);
    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);    
}
