#include "stdafx.h"
#include "Params.h"
#include "tinyxml.h"

void Params::LoadXML(const char* _filename)
{
    TiXmlDocument doc(_filename);

    if (!doc.LoadFile())
    {
        return;
    }

    TiXmlHandle handleDoc(&doc);
    TiXmlElement* element = handleDoc.FirstChildElement().Element();

    if (!element)
    {
        return;
    }

    TiXmlHandle handleRoot(element);
    TiXmlHandle handleParams = handleRoot.FirstChildElement("params");

    maxLinearVelocity = GetValue("max_linear_velocity", handleParams);
    maxLinearAcceleration = GetValue("max_linear_acceleration", handleParams);
    linearDestRadius = GetValue("linear_dest_radius", handleParams);
    linearArriveRadius = GetValue("linear_arrive_radius", handleParams);
    maxAngularVelocity = GetValue("max_angular_velocity", handleParams);
    maxAngularAcceleration = GetValue("max_angular_acceleration", handleParams);
    angularDestRadius = GetValue("angular_dest_radius", handleParams);
    angularArriveRadius = GetValue("angular_arrive_radius", handleParams);
    lookAhead = GetValue("look_ahead", handleParams);
    timeAhead = GetValue("time_ahead", handleParams);
}

float Params::GetValue(const char* _field, const TiXmlHandle& _handle) const
{
    TiXmlElement* element = _handle.FirstChildElement(_field).Element();

    if (element)
    {
        float x;
        element->Attribute("value", &x);
        return x;
    }

    return -1.f;
}