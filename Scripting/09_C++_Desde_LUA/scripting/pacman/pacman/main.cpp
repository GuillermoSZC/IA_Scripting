#include <pacman_include.hpp>
#include "lualib.h"
#include "lauxlib.h"

int num_coins = 0;
const int platas_para_oro = 2;
const int bronces_para_plata = 10;

const float max_vida = 1.5f;
float vida = max_vida;

unsigned char powerUpCol[] = { 0,0,0 };
int pointsPerCoin = 0;
int pointsToBronzeMedal = 0;
int scorePerPowerUp = 0;
int powerUpTime = 0;
int powerUpSpeedMult = 0.f;
int bronzeCoins = 0;

lua_State* luaState = nullptr;

void LoadScriptLUA()
{
    int stack = luaL_loadfile(luaState, "lua/pacman.lua");
    stack |= lua_pcall(luaState, 0, 0, 0);

    if (stack)
    {
        lua_pop(luaState, 1);
    }
}

unsigned char* GetLuaColor(float& _value)
{
    unsigned char color[] = { 0,0,0 };

    lua_getglobal(luaState, "SetColor");

    if (lua_isfunction(luaState, -1))
    {
        lua_pushnumber(luaState, vida);
        lua_pcall(luaState, 1, 3, 0);

        if (!lua_isnil(luaState, -1))
        {
            for (int i = 2; i >= 0; --i)
            {
                color[i] = (char)lua_tonumber(luaState, -1);
                lua_pop(luaState, 1);
            }
        }
    }

    return color;
}

bool pacmanEatenCallback(int& score, bool& muerto)
{ // Pacman ha sido comido por un fantasma
    vida -= 0.5f;
    muerto = vida < 0.0f;

    unsigned char* powerUpColor = GetLuaColor(vida);

    for (int i = 0; i < 3; ++i)
    {
        powerUpCol[i] = powerUpColor[i];
    }

    return true;
}

bool coinEatenCallback(int& score)
{ // Pacman se ha comido una moneda
    ++num_coins;

    lua_getglobal(luaState, "pointsPerCoin");

    if (lua_isnumber(luaState, -1))
    {
        pointsPerCoin = (int)lua_tonumber(luaState, -1);
    }

    score = num_coins * pointsPerCoin;

    return true;
}

bool frameCallback(float time)
{ // Se llama periodicamente cada frame

    LoadScriptLUA();

    return false;
}

bool ghostEatenCallback(int& score)
{ // Pacman se ha comido un fantasma
    return false;
}

bool powerUpEatenCallback(int& score)
{ // Pacman se ha comido un powerUp
    
    lua_getglobal(luaState, "powerUpSpeedMult");

    if (lua_isnumber(luaState, -1))
    {
        powerUpSpeedMult = (float)lua_tonumber(luaState, -1);
    }
    setPacmanSpeedMultiplier(powerUpSpeedMult);

    unsigned char* color = GetLuaColor(vida);
    for (int i = 0; i < 3; ++i)
    {
        powerUpCol[i] = color[i];
    }
    setPacmanColor(powerUpCol[0], powerUpCol[1], powerUpCol[2]);
    
    lua_getglobal(luaState, "powerUpTime");
    if (lua_isnumber(luaState, -1))
    {
        powerUpTime = (int)lua_tonumber(luaState, -1);
    }
    setPowerUpTime(powerUpTime);

    lua_getglobal(luaState, "scorePerPowerUp");
    if (lua_isnumber(luaState, -1))
    {
        scorePerPowerUp = (int)lua_tonumber(luaState, -1);
    }
    score += scorePerPowerUp;

    return true;
}

bool powerUpGone()
{ // El powerUp se ha acabado
    setPacmanColor(181, 34, 34);
    setPacmanSpeedMultiplier(1.0f);
    return true;
}

bool pacmanRestarted(int& score)
{
    score = 0;
    num_coins = 0;
    vida = max_vida;

    return true;
}

bool computeMedals(int& oro, int& plata, int& bronce, int score)
{
    lua_getglobal(luaState, "pointsToBronzeMedal");
    if (lua_isnumber(luaState, -1))
    {
        pointsToBronzeMedal = (int)lua_tonumber(luaState, -1);
    }
    bronzeCoins = score / pointsToBronzeMedal;
    
    plata = bronzeCoins / bronces_para_plata;
    bronce = bronzeCoins % bronces_para_plata;

    oro = plata / platas_para_oro;
    plata = plata % platas_para_oro;

    return true;
}

bool getLives(float& vidas)
{
    vidas = vida;
    return true;
}

bool setImmuneCallback()
{
    return true;
}

bool removeImmuneCallback()
{
    return true;
}

bool InitGame()
{
    luaState = luaL_newstate();
    luaL_openlibs(luaState);
    LoadScriptLUA();

    return true;
}

bool EndGame()
{
    lua_close(luaState);

    return true;
}