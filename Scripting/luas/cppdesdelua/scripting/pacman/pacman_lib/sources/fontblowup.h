/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    (if your name is missing here, please add it)
*/

#ifndef header_fontblowup
#define header_fontblowup

#if _MSC_VER > 1000
#pragma once
#endif

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class FontBlowUp
{
protected:
	CL_Font font;
	int initial_x;
	int initial_y;
	CL_String text;
	CL_Colorf color;

	float *letters_x;
	float *letters_y;
	float *letters_z;
	float *letters_delta_x;
	float *letters_delta_y;
	float *letters_delta_z;

	void create_letters(CL_GraphicContext &gc);

public:
	FontBlowUp(CL_GraphicContext &gc, const char *text, int x, int y, CL_Font font, CL_Colorf color);
	virtual ~FontBlowUp();

	bool show(CL_GraphicContext &gc, float time_elapsed);
};

#endif
