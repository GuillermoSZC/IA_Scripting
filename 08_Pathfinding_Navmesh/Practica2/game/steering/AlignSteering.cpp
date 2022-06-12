#include "stdafx.h"
#include "AlignSteering.h"
#include "params.h"
#include "character.h"


AlignSteering::AlignSteering(Character* _character) : SteeringDelegate(_character)
{

}

const SteeringOperations& AlignSteering::GetSteering(float _target)
{
    if (!character)
    {
        return SteeringOperations();
    }

    float maxVel = 0.f;
    float maxAccel = 0.f;
    float arriveRadius = 0.f;
    float destRadius = 0.f;
    float currentRot = 0.f;
    float currentAngularVel = 0.f;
    float deltaRot = 0.f;

    const Params& params = character->GetParams();
    maxVel = params.maxAngularVelocity;
    maxAccel = params.maxAngularAcceleration;
    arriveRadius = params.angularArriveRadius;
    destRadius = params.angularDestRadius;
    currentRot = character->GetRot();
    currentAngularVel = character->GetAngularVelocity();

    NormalizeAngle(_target);
    NormalizeAngle(maxVel);
    NormalizeAngle(maxAccel);
    NormalizeAngle(arriveRadius);
    NormalizeAngle(destRadius);
    NormalizeAngle(currentRot);
    NormalizeAngle(currentAngularVel);

    deltaRot = _target - currentRot;
    desiredVelocity = deltaRot > 0 ? 1.f : -1.f;

    if (abs(deltaRot) < deltaRot)
    {
        maxVel = 0.f;
    }

    if (abs(deltaRot) < arriveRadius)
    {
        float aux = abs(deltaRot) / arriveRadius;
        maxVel *= aux;
    }

    desiredVelocity *= maxVel;

    steeringOperations.angular = desiredVelocity - currentAngularVel > 0.f ? 1.f : -1.f;
    steeringOperations.angular *= maxAccel;
    
    return steeringOperations;
}

void AlignSteering::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    device.SetPenColor(0.f, 1.f, 0.4f, 1.f);
}

void AlignSteering::NormalizeAngle(float _degree)
{
    while (_degree < -180.f)
    {
        _degree += 360.f;
    }
    while (_degree > 180.f)
    {
        _degree -= 360.f;
    }
}