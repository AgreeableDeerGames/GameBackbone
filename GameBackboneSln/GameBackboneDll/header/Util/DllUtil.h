#pragma once

#include <Util/DebugIncludes.h>

#ifdef _WIN32

	//GAMEBACKBONEDLL_EXPORTS
	#ifdef GAMEBACKBONEDLL_EXPORTS 
		#define libGameBackbone __declspec(dllexport)
	#else
		#define libGameBackbone __declspec(dllimport)
	#endif
	#ifdef debugDefines
		#ifdef GAMEBACKBONEDLL_EXPORTS 
			#define libPvtGameBackbone __declspec(dllexport)
		#else
			#define libPvtGameBackbone __declspec(dllimport)
		#endif
	#else
		#define libPvtGameBackbone
	#endif
#else
	#define libGameBackbone
	#define libPvtGameBackbone
#endif // debugDefines
