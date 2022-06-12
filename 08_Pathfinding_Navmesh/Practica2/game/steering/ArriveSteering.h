#pragma once
#include "SteeringDelegate.h"

class Character;

class ArriveSteering : public SteeringDelegate
{
public:
    ArriveSteering(Character* character);





public:


protected:


private:
    USVec2D desiredVelocity;

public:
    virtual const SteeringOperations& GetSteering(const USVec2D& _target) override;
    virtual void DrawDebug() const override;

protected:


private:


};