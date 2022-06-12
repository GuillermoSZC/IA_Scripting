#pragma once

class TiXmlHandle;

struct Params
{
    float maxLinearVelocity;
    float maxLinearAcceleration;
    float linearDestRadius;
    float linearArriveRadius;

    float maxAngularVelocity;
    float maxAngularAcceleration;
    float angularDestRadius;
    float angularArriveRadius;

    float lookAhead;
    float timeAhead;

    void LoadXML(const char* _filename);
private:
    float GetValue(const char* _field, const TiXmlHandle& _handle) const;
};