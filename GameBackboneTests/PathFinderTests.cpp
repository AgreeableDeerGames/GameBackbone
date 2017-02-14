#include "stdafx.h"
#include "CppUnitTest.h"

#include "../GameBackbone/PathFinder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameBackboneTests
{		
	TEST_CLASS(PathFinderTests)
	{
	public:

		TEST_CLASS_INITIALIZE(TEST_CLASS_INIT) {
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //find all memory leaks
		}

		TEST_METHOD(default_constructor_test)
		{
			Pathfinder pathfinder;
		}

	};
}