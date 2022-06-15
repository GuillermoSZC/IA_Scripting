#pragma once

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

class Pacman
{
public:
	Pacman();
	~Pacman();

	static int NewPacman(lua_State* L);

	// Getters
	float GetMaxLife() const;
	float GetLife() const;
	int GetScorePowerUp() const;
	int GetTimePowerUp() const;
	float GetSpeedMultiplier() const;
	unsigned char* GetPowerUpColor() const;
	int GetPointsToBronze() const;
	int GetPointsPerCoin() const;
	
	// Setters to call from Lua
	static int SetMaxLife(lua_State* L);
	static int SetLife(lua_State* L);
	static int SetScorePowerUp(lua_State* L);
	static int SetTimePowerUp(lua_State* L);
	static int SetSpeedMultiplier(lua_State* L);
	static int SetPowerUpColor(lua_State* L);
	static int SetPointsToBronze(lua_State* L);
	static int SetPointsPerCoin(lua_State* L);

	void RegisterLuaFunctions(lua_State* L);

	// Static members
	static float m_fMaxLife;
	static float m_fLife;
	static int m_iScorePowerUp;
	static int m_iTimePowerUp;
	static float m_fSpeedMultiplier;
	static unsigned char* m_cPowerUpColor;
	static int m_iPointsToBronze;
	static int m_iPointsPerCoin;
};