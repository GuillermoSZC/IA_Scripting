#include "stdafx.h"

#include "ArriveSteering.h"
#include "character.h"

ArriveSteering::ArriveSteering(Character* character) : SteeringDelegate(character)
{

}

SteeringOperations ArriveSteering::GetSteering()
{
    if (character)
    {
        float maxVelocity = 0.f;
        float arriveRadius = 0.f;
        float distToTarget = 0.f;
        USVec3D accel;
        const Params& params = character->GetParams();

        steeringOperations.linear = USVec2D();
        steeringOperations.angular = 0.f;

        desiredVelocity = params.targetPosition - character->GetLoc();
        distToTarget = desiredVelocity.Length();

        maxVelocity = distToTarget <= params.dest_radius ? 0.f : params.max_velocity;

        arriveRadius = params.arrive_radius;

        if (distToTarget < arriveRadius)
        {
            const float factor = distToTarget / arriveRadius;
            maxVelocity *= factor;
        }

        desiredVelocity.NormSafe();
        desiredVelocity *= maxVelocity;

        accel = desiredVelocity - character->GetLinearVelocity();
        accel.NormSafe();

        steeringOperations.linear = accel * params.max_acceleration;

        return steeringOperations + DelegateCallback();
    }

    return SteeringOperations();
}

void ArriveSteering::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    debugPosition = character->GetLoc();
    debugDelta = debugPosition + desiredVelocity;
    device.SetPenColor(1.f, 0.f, 0.f, 1.f);
    MOAIDraw::DrawLine(debugPosition.mX, debugPosition.mY, debugDelta.mX, debugDelta.mY);

    debugDelta = debugPosition + steeringOperations.linear;
    device.SetPenColor(1.f, 1.f, 0.f, 1.f);
    MOAIDraw::DrawLine(debugPosition.mX, debugPosition.mY, debugDelta.mX, debugDelta.mY);

    if (steeringDelegate)
    {
        steeringDelegate->DrawDebug();
    }
}