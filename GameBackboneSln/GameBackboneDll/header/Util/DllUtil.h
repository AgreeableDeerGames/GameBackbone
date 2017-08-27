#pragma once

#include <Util\DebugIncludes.h>

#ifdef _WIN32
	#define libGameBackbone __declspec(dllexport)
	#ifdef debugDefines
		#define libPvtGameBackbone __declspec(dllexport)
	#else
		#define libPvtGameBackbone
	#endif
#else
	#define libGameBackbone
	#define libPvtGameBackbone
#endif // debugDefines
