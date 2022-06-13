#pragma once

struct Link;
struct Polygon;

namespace Utilities
{
    bool PointInsidePolygon(const Polygon& _polygon, const USVec2D& _point);
    USVec2D GetCenter(const Polygon& _polygon);
}

struct Polygon
{
    std::vector<USVec2D> vertex;
    std::vector<Link> links;

    USVec2D GetCenter() const;
    bool IsInside(const USVec2D& _point) const;
    USVec2D GetMiddlePoint(const Link& _link) const;
};

struct Link
{
    Polygon* polygon;
    int32_t start;
    int32_t end;
};

class Navmesh
{
public:
    Navmesh() = default;
    ~Navmesh();

public:


protected:


private:
    std::vector<Polygon*> polygonsVector;
    Polygon* startPolygon;
    Polygon* endPolygon;

public:
    static Navmesh* LoadNavmesh(const char* _fileName);

    const Polygon* GetPolygon(const USVec2D& _position) const;
    Polygon* GetPolygon(const USVec2D& _position);

    bool StartPolygon(const USVec2D& _position);
    bool EndPolygon(const USVec2D& _position);

    const Polygon* GetStartPolygon() const;
    const Polygon* GetEndPolygon() const;

    void DrawDebug() const;

protected:


private:


};