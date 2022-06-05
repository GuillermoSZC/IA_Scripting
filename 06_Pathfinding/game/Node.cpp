#include <stdafx.h>
#include "Node.h"

Node::Node(Node* _parent, const USVec2D& _gridPos, float _gCost, float _hCost)
    : parent(_parent), position(_gridPos), gCost(_gCost), hCost(_hCost)
{}

Node::Node(const Node*& _other)
    : parent(_other->parent), position(_other->position), gCost(_other->gCost), hCost(_other->hCost)
{}

float Node::GetCost() const
{
    return gCost + hCost;
}
