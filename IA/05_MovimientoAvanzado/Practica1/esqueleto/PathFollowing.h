#pragma once

#include "SteeringDelegate.h"

class PathFollowing : public SteeringDelegate
{
public:
    PathFollowing(Character* _character) : SteeringDelegate(_character) {}
    virtual ~PathFollowing();


    

public:


protected:


private:
    USVec2D target;
    USVec2D nearest;
    USVec2D step;

public:
    void OnUpdate(float _deltaTime) override;
    SteeringOperations GetSteering() override;
    void DrawDebug() override;

protected:


private:


};

