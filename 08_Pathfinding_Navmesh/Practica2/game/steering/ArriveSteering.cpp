#include "stdafx.h"
#include "ArriveSteering.h"
#include "character.h"

ArriveSteering::ArriveSteering(Character* character) : SteeringDelegate(character)
{

}

const SteeringOperations& ArriveSteering::GetSteering(const USVec2D& _target)
{
    if (!character)
    {
        return steeringOperations;
    }

    float distToTarget = 0.f;
    float maxVel = 0.f;
    float arriveRadius = 0.f;

    const Params& params = character->GetParams();
    steeringOperations = SteeringOperations();

    desiredVelocity = _target - character->GetLoc();
    distToTarget = desiredVelocity.Length();
    maxVel = distToTarget <= params.linearDestRadius ? 0.f : params.maxLinearVelocity;

    arriveRadius = params.linearArriveRadius;

    if (distToTarget < arriveRadius)
    {
        float aux = distToTarget / arriveRadius;
        maxVel *= aux;
    }

    desiredVelocity.NormSafe();
    desiredVelocity *= maxVel;

    USVec3D accel = desiredVelocity - character->GetLinearVelocity();
    accel.NormSafe();

    steeringOperations.linear = accel * params.maxLinearAcceleration;
    
    return steeringOperations;
}

void ArriveSteering::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
}