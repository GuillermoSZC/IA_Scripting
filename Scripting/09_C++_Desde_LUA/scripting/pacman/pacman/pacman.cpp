#include "pacman.h"

float Pacman::maxLife;
float Pacman::life;
unsigned char* Pacman::powerUpColor;
int Pacman::powerUpTime;
float Pacman::powerUpSpeedMult;
int Pacman::scorePerPowerUp;
int Pacman::pointsPerCoin;
int Pacman::pointsToBronzeMedal;

Pacman::Pacman()
{
    maxLife = 0.f;
    life = maxLife;
    
    powerUpColor = new unsigned char[3];
    powerUpColor[0] = 181;
    powerUpColor[1] = 34;
    powerUpColor[2] = 34;
    powerUpTime = 0;
    powerUpSpeedMult = 0.f;
    scorePerPowerUp = 0;
    
    pointsPerCoin = 0;
    pointsToBronzeMedal = 0;
}

Pacman::~Pacman()
{
    delete[] powerUpColor;
}

#pragma region GETTERS_AND_SETTERS
float Pacman::GetMaxLife() const
{
    return maxLife;
}

float Pacman::GetLife() const
{
    return life;
}

unsigned char* Pacman::GetPowerUpColor() const
{
    return powerUpColor;
}

int Pacman::GetPowerUpTime() const
{
    return powerUpTime;
}

float Pacman::GetPowerUpSpeedMult() const
{
    return powerUpSpeedMult;
}

int Pacman::GetScorePerPowerUp() const
{
    return scorePerPowerUp;
}

int Pacman::GetPointsPerCoin() const
{
    return pointsPerCoin;
}

int Pacman::GetPointsToBronzeMedal() const
{
    return pointsToBronzeMedal;
}

int Pacman::SetMaxLife(lua_State* _luaState)
{
    maxLife = (float)lua_tonumber(_luaState, 1);

    return 0;
}

int Pacman::SetLife(lua_State* _luaState)
{
    life = (float)lua_tonumber(_luaState, 1);

    return 0;
}

int Pacman::SetPowerUpColor(lua_State* _luaState)
{
    powerUpColor[0] = (char)lua_tonumber(_luaState, 1);
    powerUpColor[1] = (char)lua_tonumber(_luaState, 2);
    powerUpColor[2] = (char)lua_tonumber(_luaState, 3);

    return 0;
}

int Pacman::SetPowerUpTime(lua_State* _luaState)
{
    powerUpTime = lua_tointeger(_luaState, 1);

    return 0;
}

int Pacman::SetPowerUpSpeedMult(lua_State* _luaState)
{
    powerUpSpeedMult = (float)lua_tonumber(_luaState, 1);

    return 0;
}

int Pacman::SetScorePerPowerUp(lua_State* _luaState)
{
    scorePerPowerUp = lua_tointeger(_luaState, 1);

    return 0;
}

int Pacman::SetPointsPerCoin(lua_State* _luaState)
{
    pointsPerCoin = lua_tointeger(_luaState, 1);

    return 0;
}

int Pacman::SetPointsToBronzeMedal(lua_State* _luaState)
{
    pointsToBronzeMedal = lua_tointeger(_luaState, 1);

    return 0;
}
#pragma endregion

int Pacman::NewUserDataPacman(lua_State* _luaState)
{
    auto* pacman = (Pacman*)lua_newuserdata(_luaState, sizeof(Pacman));
    luaL_getmetatable(_luaState, "pacman.Metatable");
    lua_setmetatable(_luaState, -2);

    return 1;
}

void Pacman::RegisterLuaFunctions(lua_State* _luaState)
{
    static const struct luaL_Reg pacman_funcs[] =
    {
        { "new", NewUserDataPacman },
        { nullptr, nullptr }
    };

    static const struct luaL_Reg pacman_mtds[] =
    {
        { "SetMaxLife", SetMaxLife },
        { "SetLife", SetLife },
        { "SetPowerUpColor", SetPowerUpColor },
        { "SetPowerUpTime", SetPowerUpTime },
        { "SetPowerUpSpeedMult", SetPowerUpSpeedMult },
        { "SetScorePerPowerUp", SetScorePerPowerUp },
        { "SetPointsPerCoin", SetPointsPerCoin },
        { "SetPointsToBronzeMedal", SetPointsToBronzeMedal },
        {nullptr, nullptr}
    };

    luaL_newmetatable(_luaState, "pacman.Metatable");
    lua_pushvalue(_luaState, -1);
    lua_setfield(_luaState, -2, "__index");
    luaL_register(_luaState, nullptr, pacman_mtds);
    luaL_register(_luaState, "pacman", pacman_funcs);
}