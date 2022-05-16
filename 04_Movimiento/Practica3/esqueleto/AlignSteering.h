#pragma once

#define PI 3.14159265359f

class Character;

class AlignSteering
{
public:
    AlignSteering(Character* _character);


public:


protected:


private:
    Character* character;
    float desiredVelocity;
    float steering;
    float maxVelocity;
    float maxAcceleration;
    float targetRotation;
    float arriveRadius;
    float destRadius;

public:
#pragma region GETTERS_AND_SETTERS
    float GetDesiredVelocity() const { return desiredVelocity; }
    float GetSteering() const { return steering; }
    float GetMaxVelocity() const { return maxVelocity; }
    float GetMaxAcceleration() const { return maxAcceleration; }
    float GetTargetRotation() const { return targetRotation; }
    float GetArriveRadius() const { return arriveRadius; }
    float GetDestRadius() const { return destRadius; }

    void SetDesiredVelocity(float val) { desiredVelocity = val; }
    void SetSteering(float val) { steering = val; }
    void SetMaxVelocity(float val) { maxVelocity = val; }
    void SetMaxAcceleration(float val) { maxAcceleration = val; }
    void SetTargetRotation(float val) { targetRotation = val; }
    void SetArriveRadius(float val) { arriveRadius = val; }
    void SetDestRadius(float val) { destRadius = val; }
#pragma endregion

    float GetSteering();
    void DrawDebug();


protected:


private:


};

#pragma region AUX_FUNCTIONS
inline static float RadiansToDegrees(float _angle)
{
    return _angle * 180.f / PI;
}

inline static float DegreesToRadians(float _angle)
{
    return _angle * PI / 180.f;
}

inline static void NormalizeAngle(float& _angle)
{
    if (_angle < -PI || _angle>PI)
    {
        const int round = fmodf(_angle, PI);
        _angle += 2 * PI * round * -1;
    }
}
#pragma endregion