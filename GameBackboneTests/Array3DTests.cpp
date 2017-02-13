#include "stdafx.h"
#include "CppUnitTest.h"
#include "../GameBackbone/Array3D.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameBackboneTests
{		
	TEST_CLASS(Array3D_Test)
	{
	public:
		
		TEST_CLASS_INITIALIZE(TEST_CLASS_INIT) {
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}

		TEST_METHOD(default_constructor_test)
		{
			Array3D<int>* intArray = new Array3D<int>();
			int arrayXSize = intArray->getArraySizeX();
			int arrayYSize = intArray->getArraySizeY();
			int arrayZSize = intArray->getArraySizeZ();
			Assert::AreEqual(arrayXSize, 100, L"Array X size", LINE_INFO());
			Assert::AreEqual(arrayYSize, 100, L"Array Y size", LINE_INFO());
			Assert::AreEqual(arrayZSize, 100, L"Array Z size", LINE_INFO());
			delete intArray;
		}
	};
}