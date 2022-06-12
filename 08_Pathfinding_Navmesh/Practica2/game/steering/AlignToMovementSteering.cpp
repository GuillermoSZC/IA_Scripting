#include "stdafx.h"
#include "AlignToMovementSteering.h"
#include "AlignSteering.h"
#include "character.h"
#include "params.h"

AlignToMovementSteering::AlignToMovementSteering(Character* _character) : SteeringDelegate(_character)
{

}

const SteeringOperations& AlignToMovementSteering::GetSteering(float _target)
{
    if (!character)
    {
        return steeringOperations;
    }

    float target = 0.f;

    const USVec2D nextLinearVel = character->GetLinearVelocity();
    target = 180.f / M_PI * atan2f(nextLinearVel.mY, nextLinearVel.mX);

    steeringOperations = alignSteeringDelegate->GetSteering(target);

    return steeringOperations;
}

void AlignToMovementSteering::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
    device.SetPenColor(1.f, 1.f, 1.f, 1.f);
}


