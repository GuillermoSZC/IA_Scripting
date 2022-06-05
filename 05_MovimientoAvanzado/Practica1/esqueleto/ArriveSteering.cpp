#include "stdafx.h"

#include "ArriveSteering.h"
#include "character.h"

ArriveSteering::ArriveSteering(Character* character) : SteeringDelegate(character)
{

}

void ArriveSteering::OnUpdate(float _deltaTime)
{
    if (character)
    {
        const Params& params = character->GetParams();
        steeringOperations.linear = USVec2D();
        steeringOperations.angular = 0.f;

        desiredVelocity = params.targetPosition - character->GetLoc();
        const float distToTarget = desiredVelocity.Length();
        float maxVel = distToTarget <= params.dest_radius ? 0.f : params.max_velocity;

        const float arrive_radius = params.arrive_radius;
        if (distToTarget < arrive_radius)
        {
            const float aux = distToTarget / arrive_radius;
            maxVel *= aux;
        }

        desiredVelocity.NormSafe();
        desiredVelocity *= maxVel;

        USVec3D acceleration = desiredVelocity - character->GetLinearVelocity();
        acceleration.NormSafe();

        steeringOperations.linear = acceleration * params.max_acceleration;
    }
}

SteeringOperations ArriveSteering::GetSteering()
{
    return steeringOperations;
}

void ArriveSteering::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
}