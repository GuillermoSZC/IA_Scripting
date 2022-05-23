#pragma once

class Character;

struct SteeringOperations
{
    USVec2D linear;
    float angular;

    SteeringOperations(const USVec2D& linear = USVec2D(0.f, 0.f), float angular = 0.f)
        : linear(linear), angular(angular) {}

    SteeringOperations operator+(const SteeringOperations& _aux)
    {
        SteeringOperations operations;
        operations.linear = linear + _aux.linear;
        operations.angular = angular + _aux.angular;
        return operations;
    }

    void operator+=(const SteeringOperations& _aux)
    {
        linear += _aux.linear;
        angular += _aux.angular;
    }
};

class SteeringDelegate
{
public:
    SteeringDelegate(Character* _character);
    virtual ~SteeringDelegate();

public:


protected:
    Character* character;
    USVec2D desiredVelocity;
    SteeringOperations steeringOperations;
    SteeringDelegate* steeringDelegate;

private:


public:
    SteeringOperations DelegateCallback() const;
    void SetDelegate(SteeringDelegate* steering) { steeringDelegate = steering; }

    virtual SteeringOperations GetSteering() = 0;
    virtual void DrawDebug() = 0;

protected:


private:


};