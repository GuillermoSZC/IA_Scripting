#include <pacman_include.hpp>
#include "pacman.h"

int num_coins = 0;
const int platas_para_oro = 2;
const int bronces_para_plata = 10;

const float max_vida = 1.5f;
float vida = max_vida;

int bronzeCoins = 0;
lua_State* luaState = nullptr;
Pacman* pacman = nullptr;

void LoadScriptLUA()
{
    int stack = luaL_loadfile(luaState, "lua/pacman.lua");
    stack |= lua_pcall(luaState, 0, 0, 0);

    if (stack)
    {
        lua_pop(luaState, 1);
    }
}
void SetLuaColor(float& _value)
{
    unsigned char color[] = { 0,0,0 };

    lua_getglobal(luaState, "SetColor");

    if (lua_isfunction(luaState, -1))
    {
        lua_pushnumber(luaState, vida);
        lua_pcall(luaState, 1, 0, 0);
    }
}

bool pacmanEatenCallback(int& score, bool& muerto)
{ // Pacman ha sido comido por un fantasma
    vida -= 0.5f;
    muerto = vida < 0.0f;

    SetLuaColor(vida);

    return true;
}

bool coinEatenCallback(int& score)
{ // Pacman se ha comido una moneda
    ++num_coins;
    score = num_coins * pacman->GetPointsPerCoin();

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

    setPacmanSpeedMultiplier(pacman->GetPowerUpSpeedMult());

    unsigned char* color = pacman->GetPowerUpColor();
    setPacmanColor(color[0], color[1], color[2]);

    setPowerUpTime(pacman->GetPowerUpTime());

    score += pacman->GetScorePerPowerUp();

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
    vida = pacman->GetMaxLife();

    return true;
}

bool computeMedals(int& oro, int& plata, int& bronce, int score)
{

    bronzeCoins = score / pacman->GetPointsToBronzeMedal();

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

    pacman = new Pacman();
    pacman->RegisterLuaFunctions(luaState);

    LoadScriptLUA();

    vida = pacman->GetMaxLife();

    return true;
}

bool EndGame()
{
    lua_close(luaState);

    return true;
}