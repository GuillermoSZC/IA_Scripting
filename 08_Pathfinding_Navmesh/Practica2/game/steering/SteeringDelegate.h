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
    SteeringOperations steeringOperations;
    SteeringDelegate* steeringDelegate;

private:


public:
    SteeringOperations DelegateCallback() const;
    void SetDelegate(SteeringDelegate* steering) { steeringDelegate = steering; }

    virtual const SteeringOperations& GetSteering(const USVec2D& _target) { return steeringOperations; }
    virtual const SteeringOperations& GetSteering(float _target) { return steeringOperations; }
    virtual void DrawDebug() const = 0;

protected:


private:


};