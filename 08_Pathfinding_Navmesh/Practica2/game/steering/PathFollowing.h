#pragma once

#include "SteeringDelegate.h"

class PathFollowing : public SteeringDelegate
{
public:
    PathFollowing(Character* _character);
    virtual ~PathFollowing();

public:


protected:


private:
    SteeringDelegate* arriveSteering;
    USVec2D target;
    USVec2D nearest;
    USVec2D step;

public:
    virtual const SteeringOperations& GetSteering(const USVec2D& _target) override;
    virtual void DrawDebug() const override;

protected:


private:


};

