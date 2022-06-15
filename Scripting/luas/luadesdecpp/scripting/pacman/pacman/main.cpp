#include <pacman_include.hpp>
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int num_coins = 0;
const int platas_para_oro = 5;
const int bronces_para_plata = 4;

const float max_vida = 1.5f;
float vida = max_vida;

int iScorePowerUp = 5000;
int iTimePowerUp = 5;
float fSpeedMultiplier = 2.f;
unsigned char cPowerUpColor[] = { 0, 255, 0 };
int iPointsToBronze = 100;
int iPointsPerCoin = 50;

lua_State* L;

void updateScript()
{
	int error = luaL_loadfile(L, "lua/pacman.lua"); // carga el codigo en la pila
	error |= lua_pcall(L, 0, 0, 0); // ejecuta el codigo
	if (error)
	{
		fprintf(stderr, "%s", lua_tostring(L, -1)); // el mensaje de error esta en la cima de la pila
		lua_pop(L, 1); // quitar el mensaje de error de la pila
	}
}

// Function that call to setColor lua function 
unsigned char* luaSetColor(float& _lives)
{
	unsigned char cColor[] = { 0, 0, 0 };
	lua_getglobal(L, "setColor");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, vida);
		lua_pcall(L, 1, 3, 0);
		if (!lua_isnil(L, -1))
		{
			for (int i = 2; i >= 0; --i)
			{
				cColor[i] = (char)lua_tonumber(L, -1);
				lua_pop(L, 1);
			}
		}
	}
	return cColor;
}

bool pacmanEatenCallback(int& score, bool& muerto)
{ // Pacman ha sido comido por un fantasma
	vida -= 0.5f;
	muerto = vida < 0.0f;

	// Set powerUp color
	unsigned char* pColor = luaSetColor(vida);
	for (int i = 0; i < 3; ++i)
	{
		cPowerUpColor[i] = pColor[i];
	}

	return true;
}

bool coinEatenCallback(int& score)
{ // Pacman se ha comido una moneda
	++num_coins;
	lua_getglobal(L, "pointsPerCoin");
	if (lua_isnumber(L, -1))
	{
		iPointsPerCoin = (int)lua_tonumber(L, -1);
	}
	score = num_coins * iPointsPerCoin;

	return true;
}

bool frameCallback(float time)
{ // Se llama periodicamente cada frame
	// Update script each frame
	updateScript();
	return true;
}

bool ghostEatenCallback(int& score)
{ // Pacman se ha comido un fantasma
	return false;
}

bool powerUpEatenCallback(int& score)
{ // Pacman se ha comido un powerUp
	lua_getglobal(L, "speedMultiplier");
	if (lua_isnumber(L, -1))
	{
		fSpeedMultiplier = (float)lua_tonumber(L, -1);
	}
	setPacmanSpeedMultiplier(fSpeedMultiplier);

	/*lua_getglobal(L, "powerUpColor");
	if (lua_istable(L, -1))
	{
		lua_pushnil(L);
		for (int i = 0; i < 3; ++i)
		{
			lua_next(L, -2);
			cPowerUpColor[i] = (char)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
	}*/
	unsigned char* pColor = luaSetColor(vida);
	for (int i = 0; i < 3; ++i)
	{
		cPowerUpColor[i] = pColor[i];
	}
	setPacmanColor(cPowerUpColor[0], cPowerUpColor[1], cPowerUpColor[2]);

	lua_getglobal(L, "timePowerUp");
	if (lua_isnumber(L, -1))
	{
		iTimePowerUp = (int)lua_tonumber(L, -1);
	}
	setPowerUpTime(iTimePowerUp);

	lua_getglobal(L, "scorePowerUp");
	if (lua_isnumber(L, -1))
	{
		iScorePowerUp = (int)lua_tonumber(L, -1);
	}
	score += iScorePowerUp;

	return true;
}

bool powerUpGone()
{ // El powerUp se ha acabado
	setPacmanColor(255, 0, 0);
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
	lua_getglobal(L, "pointsToBronze");
	if (lua_isnumber(L, -1))
	{
		iPointsToBronze = (int)lua_tonumber(L, -1);
	}
	int iTotalBronzes = score / iPointsToBronze;

	plata = iTotalBronzes / bronces_para_plata;
	bronce = iTotalBronzes % bronces_para_plata;

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
	L = luaL_newstate(); // crea el entorno de lua
	luaL_openlibs(L); // abre las librerias
	updateScript();
	return true;
}

bool EndGame()
{
	lua_close(L); // cierra el entorno
	return true;
}