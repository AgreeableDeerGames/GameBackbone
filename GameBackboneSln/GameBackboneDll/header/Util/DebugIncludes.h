#pragma once

#include <iostream>

#define debugDefines

#ifdef debugDefines

#define debugPrint(x) std::cout<<x<<std::endl

#else

#define debugPrint(x) 

#endif // debugDefines
