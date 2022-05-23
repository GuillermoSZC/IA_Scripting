#pragma once



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
