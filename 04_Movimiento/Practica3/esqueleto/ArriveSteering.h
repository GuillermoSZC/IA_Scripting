#pragma once

class Character;

class ArriveSteering
{
public:

    ArriveSteering(Character* _character);

public:


protected:


private:
    Character* character;
    USVec3D desiredVelocity;
    USVec3D acceleration;
    USVec3D steering;
    USVec2D position;
    USVec2D delta;

public:
    USVec3D GetDesiredVelocity() const;
    USVec3D GetAcceleration() const;
    USVec3D GetSteering() const;
    USVec2D GetPosition() const;
    USVec2D GetDelta() const;

    void SetDesiredVelocity(USVec3D& _desiredVelocity);
    void SetAcceleration(USVec3D& _acceleration);
    void SetSteering(USVec3D& _steering);
    void SetPosition(USVec2D& _position);
    void SetDelta(USVec2D& _delta);

    USVec3D GetSteering(const USVec3D& _target);
    void DrawDebug();

protected:


private:
};