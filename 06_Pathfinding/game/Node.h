#pragma once

class Node
{
public:
    Node(Node* _parent, const USVec2D& _gridPos, float _gCost, float _hCost);
    Node(const Node*& _other);

public:
    Node* parent;

    USVec2D position;
    float hCost;
    float gCost;

protected:


private:


public:
    float GetCost() const;


protected:


private:


};