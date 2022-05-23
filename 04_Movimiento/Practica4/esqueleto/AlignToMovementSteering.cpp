#include "stdafx.h"
#include "AlignToMovementSteering.h"


#include "character.h"
#include "params.h"

AlignToMovementSteering::AlignToMovementSteering(Character* _character)  : SteeringDelegate(_character)
{

}

SteeringOperations AlignToMovementSteering::GetSteering()
{
    if (character)
    {
        const Params& params = character->GetParams();
        const USVec2D nextLinearVelocity = character->GetLinearVelocity();
        float target = 0.f;
        float arriveRadius = 0.f;
        float destRadius = 0.f;
        float currentRotation = 0.f;
        float maxAcceleration = 0.f;
        float maxVelocity = 0.f;
        float currentAngularVelocity = 0.f;

        target = MathFunctions::RadiansToDegrees(atan2f(nextLinearVelocity.mY, nextLinearVelocity.mX));
        maxVelocity = params.maxAngularVelocity;
        maxAcceleration = params.maxAngularAcceleration;
        arriveRadius = params.angularArriveRadius;
        destRadius = params.angularDestRadius;
        currentRotation = character->GetRot();
        currentAngularVelocity = character->GetAngularVelocity();

        MathFunctions::NormalizeDegreeToAngles(target);
        MathFunctions::NormalizeDegreeToAngles(arriveRadius);
        MathFunctions::NormalizeDegreeToAngles(destRadius);
        MathFunctions::NormalizeDegreeToAngles(currentRotation);
        MathFunctions::NormalizeDegreeToAngles(maxAcceleration);
        MathFunctions::NormalizeDegreeToAngles(maxVelocity);
        MathFunctions::NormalizeDegreeToAngles(currentAngularVelocity);

        const float deltaRotation = target - currentRotation;
        angularVelocityDesired = deltaRotation > 0 ? 1.f : -1.f;

        if (abs(deltaRotation) < destRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRotation) < arriveRadius)
        {
            const float factor = abs(deltaRotation) / arriveRadius;
            maxVelocity *= factor;
        }

        angularVelocityDesired *= maxVelocity;

        steeringOperations.angular = angularVelocityDesired - currentAngularVelocity > 0.f ? 1.f : -1.f;
        steeringOperations.angular *= maxAcceleration;


        return steeringOperations + DelegateCallback();
    }

    return SteeringOperations();
}

void AlignToMovementSteering::DrawDebug() {}