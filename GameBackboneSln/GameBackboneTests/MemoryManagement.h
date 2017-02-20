#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "wtypes.h"


#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif

#endif  // _DEBUG

/*

#ifndef MEM_FILE_OUTPUT_BEGIN

#ifdef _DEBUG
#define MEM_FILE_OUTPUT_BEGIN HANDLE hLogFile; \
hLogFile = CreateFile(LPCWSTR("..\\MemRpt\\MemLog.txt"), GENERIC_WRITE, \
	FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, \
	FILE_ATTRIBUTE_NORMAL, NULL); \
_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); \
_CrtSetReportFile(_CRT_WARN, hLogFile); \

#endif // !MEM_FILE_OUTPUT_BEGIN

#else

#define MEM_FILE_OUTPUT_BEGIN

#endif //_Debug


#ifndef MEM_FILE_OUTPUT_END

#ifdef _DEBUG

#define MEM_FILE_OUTPUT_END CloseHandle(hLogFile);

#else

#define MEM_FILE_OUTPUT_END

#endif // _DEBUG


#endif // !MEM_FILE_OUTPUT_END
*/