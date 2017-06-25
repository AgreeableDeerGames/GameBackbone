#pragma once
#include <Util\stdafx.h>

#include <iostream>

#define debugDefines

#ifdef debugDefines

#define debugPrint(x) std::cout<<x<<std::endl

#else

#define debugPrint(x) 

#endif // debugDefines
