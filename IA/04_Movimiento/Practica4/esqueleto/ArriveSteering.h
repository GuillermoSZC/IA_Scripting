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
    USVec2D debugPosition;
    USVec2D debugDelta;

public:
    virtual SteeringOperations GetSteering() override;
    virtual void DrawDebug() override;


protected:


private:
    

};