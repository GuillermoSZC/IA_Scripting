#include "stdafx.h"
#include "PathFollowing.h"
#include "character.h"
#include "ArriveSteering.h"
#include "pathfinding/pathfinder.h"
#include "pathfinding/path.h"

PathFollowing::PathFollowing(Character* _character) : SteeringDelegate(_character)
{
    arriveSteering = new ArriveSteering(_character);
}

PathFollowing::~PathFollowing()
{
    delete arriveSteering;
    arriveSteering = nullptr;
}

const SteeringOperations& PathFollowing::GetSteering(const USVec2D& _target)
{
    if (!character)
    {
        return steeringOperations;
    }

    if (character->GetPathfinder()->PathCompleted())
    {
        const USVec2D position = character->GetLoc();
        const USVec2D velocity = character->GetLinearVelocity();
        step = position + velocity * character->GetParams().timeAhead;

        const Path::Point pointSegment = character->GetPathfinder()->GetPath()->GetNearestPoint(step);

        nearest = pointSegment.point;
        const float lookAhead = character->GetParams().lookAhead;
        target = character->GetPathfinder()->GetPath()->GetNextPoint(pointSegment, lookAhead);
        steeringOperations = arriveSteering->GetSteering(target);
    }

    return steeringOperations;
}

void PathFollowing::DrawDebug() const
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

