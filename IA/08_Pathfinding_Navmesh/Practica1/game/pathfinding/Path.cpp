#include <stdafx.h>
#include <tinyxml.h>
#include "Path.h"



void Path::AddPoint(const USVec2D& _point)
{
    path.push_back(_point);
}

bool Path::EmptyPath() const
{
    return path.empty();
}

void Path::Clear()
{
    path.clear();
}

Path::Point Path::GetNearestPoint(const USVec2D& _point) const
{
    Point nearestPoint;
    float minDist = -1.f;
    USVec2D pathPoint;

    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        const USVec2D begin = path.at(i);
        const USVec2D end = path.at(i + 1);
        const float denominator = (end.mX - begin.mX) * (end.mX - begin.mX) + (end.mY - begin.mY) * (end.mY - begin.mY);

        if (denominator != 0.f)
        {
            const float aux = ((_point.mX - begin.mX) * (end.mX - begin.mX) + (_point.mY - begin.mY) * (end.mY - begin.mY)) / denominator;

            if (aux < 0.f)
            {
                pathPoint = begin;
            }
            else if (aux > 1.f)
            {
                pathPoint = end;
            }
            else
            {
                pathPoint = { begin.mX + aux * (end.mX - begin.mX), begin.mY + aux * (end.mY - begin.mY) };
            }

            const float dist = pathPoint.DistSqrd(_point);

            if (minDist < 0.f || dist < minDist)
            {
                minDist = dist;
                nearestPoint.point = pathPoint;
                nearestPoint.index = i;
            }
        }
    }

    return nearestPoint;
}

USVec2D Path::GetNextPoint(const Point& _point, float _dist) const
{
    auto iter = path.begin() + _point.index;
    USVec2D direction = *(iter + 1) - *iter;
    direction.NormSafe();
    USVec2D nextPoint = _point.point + direction * _dist;

    if ((nextPoint - *iter).LengthSquared() > (*(iter + 1) - *iter).LengthSquared() && iter + 2 != path.end())
    {
        float rest = _dist - (*(iter + 1) - _point.point).Length();
        direction = *(iter + 2) - *(iter + 1);
        direction.NormSafe();
        nextPoint = *(iter + 1) + direction * rest;
    }
    else if (iter + 2 == path.end())
    {
        nextPoint = *(iter + 1);
    }

    return nextPoint;
}

void Path::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    if (!path.empty())
    {
        device.SetPenColor(1.f, 0.f, 0.f, 1.f);
        device.SetPenWidth(5.f);
        for (int32_t i = 0; i < path.size() - 1; ++i)
        {
            MOAIDraw::DrawLine(path.at(i), path.at(i + 1));
        }
        device.SetPenWidth(2.5f);
    }
}
