#pragma once

struct Polygon;

class Node
{
public:
    Node(Node* _parent, const USVec2D& _gridPos, Polygon* _polygon, float _gCost, float _hCost);

public:
    Node* parent;

    USVec2D position;
    Polygon* polygon;
    float hCost;
    float gCost;

protected:


private:


public:
    float GetCost() const;


protected:


private:


};