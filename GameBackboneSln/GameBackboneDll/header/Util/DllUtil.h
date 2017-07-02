#pragma once

#include <Util\DebugIncludes.h>

#define libGameBackbone __declspec(dllexport)

#ifdef debugDefines
#define libPvtGameBackbone __declspec(dllexport)
#else
#define libPvtGameBackbone
#endif // debugDefines
