#pragma once

class Character;

class SeekSteering
{
public:
    SeekSteering(Character* _character);

public:


protected:


private:
    Character* character;
    USVec3D target;
    USVec3D desiredVelocity;
    USVec3D acceleration;
    USVec2D position;
    USVec2D delta;

public:
    void SetTarget(const USVec3D& _target);
    void SetVelocity(USVec3D& _velocity);
    void SetAcceleration(USVec3D& _acceleration);
    void SetPosition(USVec2D& _position);
    void SetDelta(USVec2D& _delta);

    USVec3D GetTarget() const;
    USVec3D GetVelocity() const;
    USVec3D GetAcceleration() const;
    USVec3D GetSteering();
    USVec2D GetPosition() const;
    USVec2D GetDelta() const;

    void DrawDebug();

protected:


private:


};