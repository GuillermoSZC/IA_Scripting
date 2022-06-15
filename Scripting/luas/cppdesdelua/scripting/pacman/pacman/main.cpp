#include <pacman_include.hpp>
#include <stdio.h>
#include "pacman.h"

int num_coins = 0;
const int platas_para_oro = 5;
const int bronces_para_plata = 4;
float vida = 0.f;

lua_State* L;
Pacman* pPacman;

void updateScript()
{
	int error = luaL_loadfile(L, "lua/pacman.lua"); // load the code on the stack
	error |= lua_pcall(L, 0, 0, 0); // Execute code
	if (error)
	{
		fprintf(stderr, "%s", lua_tostring(L, -1)); // the error message is at the top of the stack
		lua_pop(L, 1); // remove the error message from the stack
	}
}

// Function that call to setColor lua function 
void luaSetColor(float& _lives)
{
	unsigned char cColor[] = { 0, 0, 0 };
	lua_getglobal(L, "setColor");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, vida);
		lua_pcall(L, 1, 0, 0);
	}
}

bool pacmanEatenCallback(int& score, bool& muerto)
{ // Pacman has been eaten by a ghost
	vida -= 0.5f;
	muerto = vida < 0.0f;

	// Set powerUp color
	luaSetColor(vida);

	return true;
}

bool coinEatenCallback(int& score)
{ // Pacman has eaten a coin
	++num_coins;
	score = num_coins * pPacman->GetPointsPerCoin();

	return true;
}

bool frameCallback(float time)
{ // Every frame is called periodically
	// Update script each frame
	updateScript();
	return true;
}

bool ghostEatenCallback(int& score)
{ // Pacman se ha comido un fantasma
	return false;
}

bool powerUpEatenCallback(int& score)
{ // Pacman has eaten a ghost
	setPacmanSpeedMultiplier(pPacman->GetSpeedMultiplier());

	luaSetColor(vida);
	unsigned char* pColor = pPacman->GetPowerUpColor();
	setPacmanColor(pColor[0], pColor[1], pColor[2]);

	setPowerUpTime(pPacman->GetTimePowerUp());

	score += pPacman->GetScorePowerUp();

	return true;
}

bool powerUpGone()
{ // The powerUp is over
	setPacmanColor(255, 0, 0);
	setPacmanSpeedMultiplier(1.0f);
	return true;
}

bool pacmanRestarted(int& score)
{
	score = 0;
	num_coins = 0;
	vida = pPacman->GetMaxLife();

	return true;
}

bool computeMedals(int& oro, int& plata, int& bronce, int score)
{
	int iTotalBronzes = score / pPacman->GetPointsToBronze();

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
	L = luaL_newstate(); // create the lua environment
	luaL_openlibs(L); // open the libraries

	// Create Pacman instance and register lua functions
	pPacman = new Pacman();
	pPacman->RegisterLuaFunctions(L);

	updateScript();

	vida = pPacman->GetMaxLife();

	return true;
}

bool EndGame()
{
	lua_close(L); // close the lua environment
	return true;
}