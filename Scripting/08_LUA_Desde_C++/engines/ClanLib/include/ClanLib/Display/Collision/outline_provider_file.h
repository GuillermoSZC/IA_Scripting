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
**    Harry Storbacka
**    Magnus Norddahl
*/

/// \addtogroup clanDisplay_Collision clanDisplay Collision
/// \{

#pragma once

#include "../api_display.h"
#include "outline_provider.h"
#include "../../Core/Text/string_types.h"
#include "../../Core/IOData/virtual_directory.h"

class CL_OutlineProviderFile_Generic;
class CL_InputSourceProvider;

/// \brief File outline provider is used to load precompiled outlines.
///
/// <p>A CL_OutlineProviderFile is used to load precompiled outlines.</p> 
/// \xmlonly !group=Display/Collision! !header=display.h! \endxmlonly
class CL_API_DISPLAY CL_OutlineProviderFile : public CL_OutlineProvider
{
/// \name Construction
/// \{

 public:
	/// \brief Construct a outline provider
	///
	/// \param file = file to load.
	CL_OutlineProviderFile(CL_IODevice &file);

	/// \brief Constructs a OutlineProviderFile
	///
	/// \param fullname = String Ref
	CL_OutlineProviderFile(const CL_StringRef &fullname);

	/// \brief Constructs a OutlineProviderFile
	///
	/// \param filename = String Ref
	/// \param directory = Virtual Directory
	CL_OutlineProviderFile(const CL_StringRef &filename, const CL_VirtualDirectory &directory);
	~CL_OutlineProviderFile();

/// \}
/// \name Attributes
/// \{

 public:
	/// \brief return the countours that make up the outline
	virtual std::vector<CL_Contour> get_contours();

	/// \brief Not used for file provider. Returns -1.
	virtual int get_width();

	/// \brief Not used for file provider. Returns -1.
	virtual int get_height();

/// \}
/// \name Operations
/// \{

public:
	/// \brief Destroys the provider.
	virtual void destroy();

/// \}
/// \name Implementation
/// \{

 private:
	CL_SharedPtr<CL_OutlineProviderFile_Generic> impl;
/// \}
};

/// \}