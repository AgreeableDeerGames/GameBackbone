// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _WIN32
    #include "targetver.h"
#endif

#include <stdio.h>

//Adding required boost header
#include <boost/test/unit_test.hpp>
#include <string>

const std::string TestFileLocation = R"(TestFiles/)";