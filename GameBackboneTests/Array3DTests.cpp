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
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //find all memory leaks
		}

		TEST_METHOD(default_constructor_test)
		{
			Array3D<int>* intArray = new Array3D<int>();//sizes of all dimensions should be 100
			int arrayXSize = intArray->getArraySizeX();
			int arrayYSize = intArray->getArraySizeY();
			int arrayZSize = intArray->getArraySizeZ();
			Assert::AreEqual(arrayXSize, 100, L"Array X size", LINE_INFO());
			Assert::AreEqual(arrayYSize, 100, L"Array Y size", LINE_INFO());
			Assert::AreEqual(arrayZSize, 100, L"Array Z size", LINE_INFO());
			delete intArray;
		}

		TEST_METHOD(one_param_constructor_test) {
			const int arrayDim = 10;
			Array3D<int> intArray(arrayDim); //sizes of all dimensions should be 10
			int arrayXSize = intArray.getArraySizeX();
			int arrayYSize = intArray.getArraySizeY();
			int arrayZSize = intArray.getArraySizeZ();
			Assert::AreEqual(arrayXSize, arrayDim, L"Array X size", LINE_INFO());
			Assert::AreEqual(arrayYSize, arrayDim, L"Array Y size", LINE_INFO());
			Assert::AreEqual(arrayZSize, arrayDim, L"Array Z size", LINE_INFO());
		}

		TEST_METHOD(three_param_constructor_test) {
			const int arrayDimX = 10;
			const int arrayDimY = 11;
			const int arrayDimZ = 12;
			Array3D<int> intArray(arrayDimX, arrayDimY, arrayDimZ); //sizes of all dimensions should be equivalent to the passed dimensions
			int arrayXSize = intArray.getArraySizeX();
			int arrayYSize = intArray.getArraySizeY();
			int arrayZSize = intArray.getArraySizeZ();
			Assert::AreEqual(arrayXSize, arrayDimX, L"Array X size", LINE_INFO());
			Assert::AreEqual(arrayYSize, arrayDimY, L"Array Y size", LINE_INFO());
			Assert::AreEqual(arrayZSize, arrayDimZ, L"Array Z size", LINE_INFO());
		}

		TEST_METHOD(setValueAt_test_1) {
			Array3D<int> intArray(100);
			const int value = 15;
			int x = 10;
			int y = 15;
			int z = 30;
			intArray.setValueAt(x,y,z, value);
			auto arrayreturn = intArray.getValueAt(x, y, z);
			Assert::AreEqual(value, arrayreturn);
		}

		TEST_METHOD(setValueAt_test_2) {
			Array3D<int> intArray(100);
			int x = 0;
			int y = 0;
			int z = 0;
			const int value = 15;
			intArray.setValueAt(x, y, z, value);
			auto arrayreturn = intArray.getValueAt(x, y, z);
			Assert::AreEqual(value, arrayreturn);
		}
		TEST_METHOD(setValueAt_test_3) {
			Array3D<int> intArray(100);
			int x = 99;
			int y = 99;
			int z = 99;
			const int value = 15;
			intArray.setValueAt(x, y, z, value);
			auto arrayreturn = intArray.getValueAt(x, y, z);
			Assert::AreEqual(value, arrayreturn);
		}
		TEST_METHOD(getValueAt_test_1) {
			const size_t dimensionSize = 10;

			Array3D<int> intArray(dimensionSize);

			for (size_t i = 0; i < dimensionSize; i++) {
				for (size_t j = 0; j < dimensionSize; ++j) {
					for (size_t k = 0; k < dimensionSize; k++) {
						intArray.setValueAt(i, j, k, i + dimensionSize * j + dimensionSize * dimensionSize + k);
					}
				}
			}
			for (size_t i = 0; i < dimensionSize; i++) {
				for (size_t j = 0; j < dimensionSize; ++j) {
					for (size_t k = 0; k < dimensionSize; k++) {
						const int expectedValue = i + dimensionSize * j + dimensionSize * dimensionSize + k;
						const int foundValue = intArray.getValueAt(i, j, k);
						Assert::AreEqual(foundValue, expectedValue);
					}
				}
			}

		}
		TEST_METHOD(getValueAt_test_2) {
			const size_t dimensionSize = 10;

			Array3D<int> intArray(dimensionSize);

			for (size_t i = 0; i < dimensionSize; i++) {
				for (size_t j = 0; j < dimensionSize; ++j) {
					for (size_t k = 0; k < dimensionSize; k++) {
						intArray.setValueAt(i, j, k, i + dimensionSize * j + dimensionSize * dimensionSize + k);
					}
				}
			}
			for (size_t i = 0; i < dimensionSize; i++) {
				for (size_t j = 0; j < dimensionSize; ++j) {
					for (size_t k = 0; k < dimensionSize; k++) {
						const int expectedValue = i + dimensionSize * j + dimensionSize * dimensionSize + k;
						const int foundValue = intArray.getValueAt(sf::Vector3i(i, j, k));
						Assert::AreEqual(foundValue, expectedValue);
					}
				}
			}

		}


	};
}