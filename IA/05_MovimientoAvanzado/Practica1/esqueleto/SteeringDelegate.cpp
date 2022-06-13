#include "stdafx.h"
#include "SteeringDelegate.h"


SteeringDelegate::SteeringDelegate(Character* _character) : character(_character), steeringDelegate(nullptr)
{

}

SteeringDelegate::~SteeringDelegate()
{
    delete steeringDelegate;
}

SteeringOperations SteeringDelegate::DelegateCallback() const
{
    if (steeringDelegate)
    {
        return steeringDelegate->GetSteering();
    }

    return SteeringOperations({ 0.f, 0.f }, 0.f);
}