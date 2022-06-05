#include <stdafx.h>
#include "Grid.h"

#pragma region GETTERS
float Grid::GetCost(uint32_t _index) const
{
    return map.at(_index);
}

float Grid::GetCost(uint32_t _row, uint32_t _col) const
{
    const uint32_t aux = _row * static_cast<uint32_t>(size.mX) + _col;

    if (aux > map.size())
    {
        return -1.f;
    }

    return GetCost(aux);
}

float Grid::GetCost(const USVec2D& _location) const
{
    return GetCost(static_cast<uint32_t>(_location.mY), static_cast<uint32_t>(_location.mX));
}

USVec2D Grid::GetSize() const
{
    return size;
}

USVec2D Grid::GetRectSize() const
{
    return USVec2D(static_cast<float>(MOAIGfxDevice::Get().GetWidth()) / size.mX, static_cast<float>(MOAIGfxDevice::Get().GetHeight()) / size.mY);
}
#pragma endregion

Grid* Grid::LoadMap(const char* _fileName, const char* _codeFile)
{
    if (!_fileName || !_codeFile)
    {
        return nullptr;
    }

    auto auxGrid = new Grid();

    std::map<char, float> code;
    {
        std::ifstream streamCode;
        streamCode.open(_codeFile);

        if (!streamCode.is_open())
        {
            streamCode.close();
            return nullptr;
        }

        std::string line;

        while (std::getline(streamCode, line))
        {
            const size_t index = line.find(':');
            if (index == std::string::npos)
            {
                streamCode.close();
                return nullptr;
            }

            code.insert(std::make_pair(line.at(0), std::stof(line.substr(index + 1))));
        }
        streamCode.close();
    }

    {
        std::ifstream streamMap;
        streamMap.open(_fileName);

        if (!streamMap.is_open())
        {
            streamMap.close();
            return nullptr;
        }

        std::string line;
        int x = 0, y = 0;

        while (std::getline(streamMap, line))
        {
            ++y;
            if (x == 0)
            {
                x = line.size();
            }

            for (char it : line)
            {
                float cost = code.at(it);
                auxGrid->map.push_back(cost);
            }
        }
        streamMap.close();

        auxGrid->size = USVec2D(static_cast<float>(x), static_cast<float>(y));
    }

    return auxGrid;
}

void Grid::DrawDebug() const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();
    float widthHalf = 0.f, heightHalf = 0.f;
    USVec2D rectSize;
    USRect rectangle;

    widthHalf = static_cast<float>(device.GetWidth()) * 0.5f;
    heightHalf = static_cast<float>(device.GetHeight()) * 0.5f;
    rectSize = USVec2D(static_cast<float>(device.GetWidth()) / size.mX, static_cast<float>(device.GetHeight()) / size.mY);

    for (int32_t row = 0; row < static_cast<int32_t>(size.mY); ++row)
    {
        for (int32_t column = 0; column < static_cast<int32_t>(size.mX); ++column)
        {
            rectangle.mXMin = static_cast<float>(column) * rectSize.mX - widthHalf;
            rectangle.mXMax = rectangle.mXMin + rectSize.mX;
            rectangle.mYMin = static_cast<float>(row) * rectSize.mY - heightHalf;
            rectangle.mYMax = rectangle.mYMin + rectSize.mY;

            const auto aux = static_cast<int32_t>(GetCost(row, column));

            device.SetPenColor(0.25f, 0.05f, 0.05f, 1.f);
            if (aux == -1)
            {
                MOAIDraw::DrawRectFill(rectangle);
            }
            else
            {
                device.SetPenColor(0.55f, 0.25f - aux * 0.01f, 0.05f, 0.1f);
                MOAIDraw::DrawRectFill(rectangle);
                device.SetPenColor(0.f, 0.f, 0.f, 1.f);
                MOAIDraw::DrawRectOutline(rectangle);
            }
        }
    }
}

bool Grid::PositionIsValid(const USVec2D& _position) const
{
    return _position.mX >= 0.f && _position.mX < size.mX&& _position.mY >= 0.f && _position.mY < size.mY;
}

USVec2D Grid::LocationWorldToGrid(const USVec2D& _location) const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    const float widthHalf = static_cast<float>(device.GetWidth()) * 0.5f;
    const float heightHalf = static_cast<float>(device.GetHeight()) * 0.5f;
    const USVec2D locFromScreenCorner = _location + USVec2D(widthHalf, heightHalf);
    USVec2D rectSize = GetRectSize();
    USVec2D gridLoc(floorf(locFromScreenCorner.mX / rectSize.mX), floorf(locFromScreenCorner.mY / rectSize.mY));

    return gridLoc;
}

USVec2D Grid::LocationGridToWorld(const USVec2D& _location) const
{
    MOAIGfxDevice& device = MOAIGfxDevice::Get();

    const float widthHalf = static_cast<float>(device.GetWidth()) * 0.5f;
    const float heightHalf = static_cast<float>(device.GetHeight()) * 0.5f;

    USVec2D rectSize = GetRectSize();
    USVec2D screenLoc(rectSize.mX * _location.mX, rectSize.mY * _location.mY);
    USVec2D worldLoc = screenLoc - USVec2D(widthHalf, heightHalf);

    return worldLoc;

}
