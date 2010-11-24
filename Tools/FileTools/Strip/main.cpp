/*
-------------------------------------------------------------------------------
    This file is part of FBT (File Binary Tables).
    http://gamekit.googlecode.com/

    Copyright (c) 2010 Charlie C & Erwin Coumans.

-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "fbtBlend.h"
#include "Blender.h"
using namespace Blender;



// Unneeded structures 
static FBTuint32 skipList[] =
{
	fbtCharHashKey("Panel").hash(),
	fbtCharHashKey("ARegion").hash(),
	fbtCharHashKey("ScrArea").hash(),
	fbtCharHashKey("ScrVert").hash(),
	fbtCharHashKey("ScrEdge").hash(),
	fbtCharHashKey("bScreen").hash(),

	// ... others
	0,
};


// This program will read in a normal .blend file, and reflect it back to disk without 
// the structures containted in skipList. 
// This will make the .blend unreadable by blender because of the missing bScreen, ScrVert, ScrEdge structures.
// GameKit does not care whether or not these structures exist, therfore the file can still be read by GameKit
int main(int argc, char** argv)
{
	if (argc < 3)
	{
		fbtPrintf("Usage: %s infile.blend outfile.blend\n", argv[0]);
		return 1;
	}

	char* inFile = argv[argc-2];
	char* outFile = argv[argc-1];

	fbtPrintf("Strip %s to %s...\n", inFile, outFile);

	fbtBlend fp;
	fp.setIgnoreList(skipList);

	if (fp.parse(inFile, fbtFile::PM_COMPRESSED) != fbtFile::FS_OK)
	{
		return 1;
	}

	fp.reflect(outFile);
	fbtPrintf("Done.\n");
	
	return 0;
}