#pragma once

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

class Pacman
{
public:
    Pacman();
    ~Pacman();

public:
    static float maxLife;
    static float life;
    static int scorePerPowerUp;
    static int powerUpTime;
    static float powerUpSpeedMult;
    static unsigned char* powerUpColor;
    static int pointsToBronzeMedal;
    static int pointsPerCoin;

protected:

private:

public:
    static int NewUserDataPacman(lua_State* _luaState);
    void RegisterLuaFunctions(lua_State* _luaState);

#pragma region GETTERS_AND_SETTERS
    float GetMaxLife() const;
    float GetLife() const;
    int GetScorePerPowerUp() const;
    int GetPowerUpTime() const;
    float GetPowerUpSpeedMult() const;
    unsigned char* GetPowerUpColor() const;
    int GetPointsToBronzeMedal() const;
    int GetPointsPerCoin() const;

    static int SetMaxLife(lua_State* _luaState);
    static int SetLife(lua_State* _luaState);
    static int SetScorePerPowerUp(lua_State* _luaState);
    static int SetPowerUpTime(lua_State* _luaState);
    static int SetPowerUpSpeedMult(lua_State* _luaState);
    static int SetPowerUpColor(lua_State* _luaState);
    static int SetPointsToBronzeMedal(lua_State* _luaState);
    static int SetPointsPerCoin(lua_State* _luaState);
#pragma endregion

protected:

private:

};