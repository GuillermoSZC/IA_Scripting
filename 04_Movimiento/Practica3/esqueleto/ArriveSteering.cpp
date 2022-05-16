#include "stdafx.h"
#include "ArriveSteering.h"
#include "character.h"

ArriveSteering::ArriveSteering(Character* _character)
{
    character = _character;
}

#pragma region GETTERS_AND_SETTERS
USVec3D ArriveSteering::GetDesiredVelocity() const
{
    return desiredVelocity;
}

USVec3D ArriveSteering::GetAcceleration() const
{
    return acceleration;
}

USVec3D ArriveSteering::GetSteering() const
{
    return steering;
}

USVec2D ArriveSteering::GetPosition() const
{
    return position;
}

USVec2D ArriveSteering::GetDelta() const
{
    return delta;
}

void ArriveSteering::SetDesiredVelocity(USVec3D& _desiredVelocity)
{
    desiredVelocity = _desiredVelocity;
}

void ArriveSteering::SetAcceleration(USVec3D& _acceleration)
{
    acceleration = _acceleration;
}

void ArriveSteering::SetSteering(USVec3D& _steering)
{
    steering = _steering;
}

void ArriveSteering::SetPosition(USVec2D& _position)
{
    position = _position;
}

void ArriveSteering::SetDelta(USVec2D& _delta)
{
    delta = _delta;
}
#pragma endregion

USVec3D ArriveSteering::GetSteering(const USVec3D& _target)
{
    if (character)
    {
        Params params;
        float distToTarget = 0.f;
        float maxVelocity = 0.f;
        float arriveRadius = 0.f;
        float dist = 0.f;

        params = character->GetParams();

        desiredVelocity = _target - character->GetLoc();
        distToTarget = desiredVelocity.Length();
        maxVelocity = distToTarget <= params.dest_radius ? 0.f : params.max_velocity;

        arriveRadius = params.arrive_radius;
        if (distToTarget < arriveRadius)
        {
            dist = distToTarget / arriveRadius;
            maxVelocity *= dist;
        }

        desiredVelocity.NormSafe();
        desiredVelocity *= maxVelocity;

        acceleration = desiredVelocity - character->GetLinearVelocity();
        acceleration.NormSafe();

        steering = acceleration * params.max_acceleration;

        return steering;
    }

    return USVec3D();
}

void ArriveSteering::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
    position = character->GetLoc();

    delta = position + desiredVelocity;
    device.SetPenColor(1.f, 0.f, 0.f, 1.f);
    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);

    delta = position + steering;
    device.SetPenColor(1.f, 1.f, 0.f, 1.f);
    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);
}
