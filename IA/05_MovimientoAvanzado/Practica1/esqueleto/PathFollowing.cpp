#include "stdafx.h"
#include "PathFollowing.h"
#include "character.h"

PathFollowing::~PathFollowing()
{

}

void PathFollowing::OnUpdate(float _deltaTime)
{
    USVec2D position;
    USVec2D velocity;
    float look_ahead = 0.f;

    if (character)
    {
        position = character->GetLoc();
        velocity = character->GetLinearVelocity();
        step = position + velocity * character->GetParams().time_ahead;

        Path::Point point = character->GetPath().GetNearestPoint(step);
        nearest = point.point;
        look_ahead = character->GetParams().look_ahead;
        target = character->GetPath().GetNextPoint(point, look_ahead);
        character->SetTarget(target);
    }
}

SteeringOperations PathFollowing::GetSteering()
{
    return steeringOperations;
}

void PathFollowing::DrawDebug()
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
    
    device.SetPenColor(0.f, 1.f, 0.f, 1.f);
    MOAIDraw::DrawEllipseFill(target.mX, target.mY, 5.f, 5.f, 10);
    MOAIDraw::DrawLine(USVec2D(character->GetLoc()), target);

    device.SetPenColor(0.f, 0.f, 1.f, 1.f);
    MOAIDraw::DrawEllipseFill(nearest.mX, nearest.mY, 5.f, 5.f, 10);
    MOAIDraw::DrawLine(step, nearest);

    device.SetPenColor(1.0f, 0.f, 0.f, 1.f);
    MOAIDraw::DrawEllipseFill(step.mX, step.mY, 5.f, 5.f, 10);
    MOAIDraw::DrawLine(USVec2D(character->GetLoc()), step);
}

