#include "stdafx.h"
#include "AlignSteering.h"
#include "params.h"
#include "character.h"


AlignSteering::AlignSteering(Character* _character)
{
    character = _character;
}

float AlignSteering::GetSteering()
{

    if (character)
    {
        float currentRotation = 0.f, currentAngularVel = 0.f, deltaRot = 0.f;

        const Params& params = character->GetParams();
        maxVelocity = MathFunctions::DegreesToRadians(params.maxAngularVelocity);
        maxAcceleration = MathFunctions::DegreesToRadians(params.maxAngularAcceleration);
        targetRotation = MathFunctions::DegreesToRadians(params.targetRotation);
        arriveRadius = MathFunctions::DegreesToRadians(params.arrive_radius);
        destRadius = MathFunctions::DegreesToRadians(params.dest_radius);
        currentRotation = MathFunctions::DegreesToRadians(character->GetRot());
        currentAngularVel = MathFunctions::DegreesToRadians(character->GetAngularVelocity());

        MathFunctions::NormalizeRadianToAngles(maxVelocity);
        MathFunctions::NormalizeRadianToAngles(maxAcceleration);
        MathFunctions::NormalizeRadianToAngles(targetRotation);
        MathFunctions::NormalizeRadianToAngles(arriveRadius);
        MathFunctions::NormalizeRadianToAngles(destRadius);
        MathFunctions::NormalizeRadianToAngles(currentRotation);
        MathFunctions::NormalizeRadianToAngles(currentAngularVel);

        deltaRot = targetRotation - currentRotation;
        desiredVelocity = deltaRot > 0.f ?  1.f : -1.f;

        if (abs(deltaRot) < arriveRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRot) < arriveRadius)
        {
            float aux = abs(deltaRot) / arriveRadius;
            maxVelocity *= aux;
        }

        desiredVelocity *= maxVelocity;

        steering = desiredVelocity - currentAngularVel > 0.f ? 1.f : -1.f;
        steering *= maxAcceleration;

        return MathFunctions::RadiansToDegrees(steering);
    }


    return 0.f;
}

void AlignSteering::DrawDebug()
{
    USVec2D position;
    USVec2D delta;
    float targetRot = 0.f;
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    device.SetPenColor(0.f, 1.f, 0.f, 1.f);
    position = character->GetLoc();
    targetRot = MathFunctions::DegreesToRadians(character->GetParams().targetRotation);
    MathFunctions::NormalizeRadianToAngles(targetRot);

    delta = position + USVec2D(cosf(desiredVelocity), sinf(desiredVelocity)) * 100.f;

    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);
}
