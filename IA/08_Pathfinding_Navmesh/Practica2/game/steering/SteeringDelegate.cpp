#include "stdafx.h"
#include "SteeringDelegate.h"


SteeringDelegate::SteeringDelegate(Character* _character) : character(_character)
{

}

SteeringDelegate::~SteeringDelegate()
{
    delete steeringDelegate;
}
