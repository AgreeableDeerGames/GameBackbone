// GameBackboneLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GameBackboneLib.h"


// This is an example of an exported variable
GAMEBACKBONELIB_API int nGameBackboneLib=0;

// This is an example of an exported function.
GAMEBACKBONELIB_API int fnGameBackboneLib(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see GameBackboneLib.h for the class definition
CGameBackboneLib::CGameBackboneLib()
{
    return;
}
