#include "stdafx.h"
#include "SeekSteering.h"
#include "character.h"

SeekSteering::SeekSteering(Character* _character)
    : character(_character), target()
{}

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

void SeekSteering::DrawDebug() 
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    // Desired velocity
    USVec2D position = character->GetLoc();
    USVec2D delta = position + desiredVelocity;
    device.SetPenColor(0.9f, 0.2f, 0.2f, 1.f);
    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);

    // Acceleration
    delta = position + acceleration;
    device.SetPenColor(0.2f, 0.7f, 0.2f, 1.f);
    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);
}

void SeekSteering::SetTarget(const USVec3D& _target)
{
    target = _target;
}

