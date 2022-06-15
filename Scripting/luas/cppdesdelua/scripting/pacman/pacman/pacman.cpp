#include "pacman.h"

float Pacman::m_fMaxLife;
float Pacman::m_fLife;
int Pacman::m_iScorePowerUp;
int Pacman::m_iTimePowerUp;
float Pacman::m_fSpeedMultiplier;
unsigned char* Pacman::m_cPowerUpColor;
int Pacman::m_iPointsToBronze;
int Pacman::m_iPointsPerCoin;

Pacman::Pacman()
{
	m_fMaxLife = 1.5f;
	m_fLife = m_fMaxLife;
	m_iScorePowerUp = 5000;
	m_iTimePowerUp = 5;
	m_fSpeedMultiplier = 1.5f;
	m_iPointsToBronze = 100;
	m_iPointsPerCoin = 50;
	m_cPowerUpColor = new unsigned char[3];
	m_cPowerUpColor[0] = 255;
	m_cPowerUpColor[1] = 255;
	m_cPowerUpColor[2] = 255;
}

Pacman::~Pacman()
{
	delete m_cPowerUpColor;
}



float Pacman::GetMaxLife() const
{
	return m_fMaxLife;
}

float Pacman::GetLife() const
{
	return m_fLife;
}

int Pacman::GetScorePowerUp() const
{
	return m_iScorePowerUp;
}

int Pacman::GetTimePowerUp() const
{
	return m_iTimePowerUp;
}

float Pacman::GetSpeedMultiplier() const
{
	return m_fSpeedMultiplier;
}

unsigned char* Pacman::GetPowerUpColor() const
{
	return m_cPowerUpColor;
}

int Pacman::GetPointsToBronze() const
{
	return m_iPointsToBronze;
}

int Pacman::GetPointsPerCoin() const
{
	return m_iPointsPerCoin;
}

int Pacman::NewPacman(lua_State* L)
{
	Pacman* pPacman = (Pacman*)lua_newuserdata(L, sizeof(Pacman));
	luaL_getmetatable(L, "pacman.Metatable");
	lua_setmetatable(L, -2);
	return 1; // The value is on the stack, we return it
}

int Pacman::SetMaxLife(lua_State* L)
{
	m_fMaxLife = (float)lua_tonumber(L, 1);
	return 0;
}

int Pacman::SetLife(lua_State* L)
{
	m_fLife = (float)lua_tonumber(L, 1);
	return 0;
}

int Pacman::SetScorePowerUp(lua_State* L)
{
	m_iScorePowerUp = lua_tointeger(L, 1);
	return 0;
}

int Pacman::SetTimePowerUp(lua_State* L)
{
	m_iTimePowerUp = lua_tointeger(L, 1);
	return 0;
}

int Pacman::SetSpeedMultiplier(lua_State* L)
{
	m_fSpeedMultiplier = (float)lua_tonumber(L, 1);
	return 0;
}

int Pacman::SetPowerUpColor(lua_State* L)
{
	m_cPowerUpColor[0] = (char)lua_tonumber(L, 1);
	m_cPowerUpColor[1] = (char)lua_tonumber(L, 2);
	m_cPowerUpColor[2] = (char)lua_tonumber(L, 3);
	return 0;
}

int Pacman::SetPointsToBronze(lua_State* L)
{
	m_iPointsToBronze = lua_tointeger(L, 1);
	return 0;
}

int Pacman::SetPointsPerCoin(lua_State* L)
{
	m_iPointsPerCoin = lua_tointeger(L, 1);
	return 0;
}

void Pacman::RegisterLuaFunctions(lua_State* L)
{
	// Functions (e.g., myPacman = pacman.new())
	static const struct luaL_Reg pacman_funcs[] =
	{
		{ "new", NewPacman },
		{ NULL, NULL }
	};

	// Methods (e.g., myPacman.setMaxLife(2))
	static const struct luaL_Reg pacman_mtds[] =
	{
		{ "setMaxLife", SetMaxLife },
		{ "setLife", SetLife },
		{ "setScorePowerUp", SetScorePowerUp },
		{ "setTimePowerUp", SetTimePowerUp },
		{ "setSpeedMultiplier", SetSpeedMultiplier },
		{ "setPowerUpColor", SetPowerUpColor },
		{ "setPointsToBronze", SetPointsToBronze },
		{ "setPointsPerCoin", SetPointsPerCoin },
		{NULL, NULL}
	};

	luaL_newmetatable(L, "pacman.Metatable");
	// Assign metatable to __index
	lua_pushvalue(L, -1); // Duplicate metatable
	lua_setfield(L, -2, "__index");
	// use top of stack as table
	luaL_register(L, NULL, pacman_mtds);
	luaL_register(L, "pacman", pacman_funcs);
}

