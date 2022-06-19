#pragma once

#include "../sources/precomp.h"
#include "../sources/program.h"

#include <ClanLib/application.h>

CL_ClanApplication app(&Program::main);

extern void setPacmanSpeedMultiplier(float speed);
extern void setPacmanColor(unsigned char r = 181, unsigned char g = 34, unsigned char b = 34, unsigned char a = 255);
extern void setPowerUpTime(int seconds);