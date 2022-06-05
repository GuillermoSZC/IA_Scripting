#pragma once

class Grid
{
public:
    Grid() = default;

public:


protected:


private:
    std::vector<float> map;
    USVec2D size;

public:
    float GetCost(uint32_t _index) const;
    float GetCost(uint32_t _row, uint32_t _col) const;
    float GetCost(const USVec2D& _location) const;
    USVec2D GetSize() const;
    USVec2D GetRectSize() const;

    static Grid* LoadMap(const char* _fileName, const char* _codeFile);
    void DrawDebug() const;    
    bool PositionIsValid(const USVec2D& _position) const;
    USVec2D LocationWorldToGrid(const USVec2D& _location) const;
    USVec2D LocationGridToWorld(const USVec2D& _location) const;

protected:


private:


};