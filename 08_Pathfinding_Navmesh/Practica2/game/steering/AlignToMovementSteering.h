#pragma once
#include "SteeringDelegate.h"

class AlignSteering;

class AlignToMovementSteering : public SteeringDelegate
{
public:
    AlignToMovementSteering(Character* _character);

public:


protected:
    float angularVelocityDesired;
    AlignSteering* alignSteeringDelegate;

private:


public:
    virtual const SteeringOperations& GetSteering(float _target) override;
    virtual void DrawDebug() const override;


protected:


private:


protected:


};
