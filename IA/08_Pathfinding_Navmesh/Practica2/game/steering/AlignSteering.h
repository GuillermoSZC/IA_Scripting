#pragma once
#include "SteeringDelegate.h"

class Character;

class AlignSteering : public SteeringDelegate
{
public:
    AlignSteering(Character* _character);

public:


protected:
    float desiredVelocity;

private:


public:
    void NormalizeAngle(float _degree);
    
    virtual const SteeringOperations& GetSteering(float _target) override;
    virtual void DrawDebug() const override;

protected:


private:


};
