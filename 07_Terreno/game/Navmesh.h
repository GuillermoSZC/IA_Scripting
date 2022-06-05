#pragma once

struct Link;

struct Polygon
{
    std::vector<USVec2D> vertex;
    std::vector<Link> links;
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

public:
    static Navmesh* LoadNavmesh(const char* _fileName);
    void DrawDebug() const;

protected:


private:


};