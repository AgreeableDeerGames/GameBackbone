#include "stdafx.h"

#include<Array3D.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(Array3D_Tests)

BOOST_AUTO_TEST_SUITE(Array3D_ctrs)

BOOST_AUTO_TEST_CASE( Array3D_default_ctr_test )  
{

	Array3D<int>* intArray = new Array3D<int>();//sizes of all dimensions should be 100
	int arrayXSize = intArray->getArraySizeX();
	int arrayYSize = intArray->getArraySizeY();
	int arrayZSize = intArray->getArraySizeZ();
	BOOST_CHECK_EQUAL(arrayXSize, 100);
	BOOST_CHECK_EQUAL(arrayYSize, 100);
	BOOST_CHECK_EQUAL(arrayZSize, 100);
	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array3D_one_param_ctr_test) {
	const int arrayDim = 10;
	Array3D<int> intArray(arrayDim); //sizes of all dimensions should be 10
	int arrayXSize = intArray.getArraySizeX();
	int arrayYSize = intArray.getArraySizeY();
	int arrayZSize = intArray.getArraySizeZ();
	BOOST_CHECK_EQUAL(arrayXSize, arrayDim);
	BOOST_CHECK_EQUAL(arrayYSize, arrayDim);
	BOOST_CHECK_EQUAL(arrayZSize, arrayDim);
}

BOOST_AUTO_TEST_CASE(Array3D_three_param_ctr_test) {
	const int arrayDimX = 10;
	const int arrayDimY = 11;
	const int arrayDimZ = 12;
	Array3D<int> intArray(arrayDimX, arrayDimY, arrayDimZ); //sizes of all dimensions should be equivalent to the passed dimensions
	int arrayXSize = intArray.getArraySizeX();
	int arrayYSize = intArray.getArraySizeY();
	int arrayZSize = intArray.getArraySizeZ();
	BOOST_CHECK_EQUAL(arrayXSize, arrayDimX);
	BOOST_CHECK_EQUAL(arrayYSize, arrayDimY);
	BOOST_CHECK_EQUAL(arrayZSize, arrayDimZ);
}

BOOST_AUTO_TEST_SUITE_END() // end Array3D_ctrs

BOOST_AUTO_TEST_SUITE(Array3D_get_set_tests)

BOOST_AUTO_TEST_CASE(Array3D_setValueAt_test_1) {
	Array3D<int> intArray(100);
	const int value = 15;
	int x = 10;
	int y = 15;
	int z = 30;
	intArray.setValueAt(x, y, z, value);
	auto arrayreturn = intArray.getValueAt(x, y, z);
	BOOST_CHECK_EQUAL(value, arrayreturn);
}

BOOST_AUTO_TEST_CASE(Array3D_setValueAt_test_2) {
	Array3D<int> intArray(100);
	int x = 0;
	int y = 0;
	int z = 0;
	const int value = 15;
	intArray.setValueAt(x, y, z, value);
	auto arrayreturn = intArray.getValueAt(x, y, z);
	BOOST_CHECK_EQUAL(value, arrayreturn);
}

BOOST_AUTO_TEST_CASE(Array3D_setValueAt_test_3) {
	Array3D<int> intArray(100);
	int x = 99;
	int y = 99;
	int z = 99;
	const int value = 15;
	intArray.setValueAt(x, y, z, value);
	auto arrayreturn = intArray.getValueAt(x, y, z);
	BOOST_CHECK_EQUAL(value, arrayreturn);
}

BOOST_AUTO_TEST_CASE(Array3D_getValueAt_test_1) {
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
				BOOST_CHECK_EQUAL(foundValue, expectedValue);
			}
		}
	}

}

BOOST_AUTO_TEST_CASE(Array3D_getValueAt_test_2) {
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
				BOOST_CHECK_EQUAL(foundValue, expectedValue);
			}
		}
	}

}

BOOST_AUTO_TEST_SUITE_END() //end Array3D_get_set_tests

BOOST_AUTO_TEST_SUITE_END() //end Array3D_Tests