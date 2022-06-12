#include <stdafx.h>
#include "Node.h"

Node::Node(Node* _parent, const USVec2D& _gridPos, Polygon* _polygon, float _gCost, float _hCost)
    : parent(_parent), position(_gridPos), polygon(_polygon), gCost(_gCost), hCost(_hCost)
{}


float Node::GetCost() const
{
    return gCost + hCost;
}
