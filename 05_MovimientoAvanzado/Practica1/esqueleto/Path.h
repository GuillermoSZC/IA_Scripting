#pragma once

class Path
{
public:
    struct  Point
    {
        size_t index {0};
        USVec2D point {};
    };

public:


protected:


private:
    std::vector<USVec2D> path;

public:
    void LoadXML(const char* _fileName);

    Point GetNearestPoint(const USVec2D& _point) const;
    USVec2D GetNextPoint(const Point& _point, float _dist) const;

    void DrawDebug();
    
protected:


private:


};