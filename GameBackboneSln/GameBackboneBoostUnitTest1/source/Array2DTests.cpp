#include <Util/Array2D.h>

#include <boost/test/unit_test.hpp>

using namespace GB;

BOOST_AUTO_TEST_SUITE(Array2D_Tests)

BOOST_AUTO_TEST_SUITE(Array2D_ctrs)

BOOST_AUTO_TEST_CASE(Array2D_default_ctr) {
	Array2D<int>* intArray = new Array2D<int>();//sizes of all dimensions should be 100

	int arrayXSize = intArray->getArraySizeX();
	int arrayYSize = intArray->getArraySizeY();

	BOOST_CHECK_EQUAL(arrayXSize, 100);
	BOOST_CHECK_EQUAL(arrayYSize, 100);

	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array2D_one_param_ctr) {
	const int arrayDim = 10;
	Array2D<int>* intArray = new Array2D<int>(arrayDim);//sizes of all dimensions should be 10

	int arrayXSize = intArray->getArraySizeX();
	int arrayYSize = intArray->getArraySizeY();

	BOOST_CHECK_EQUAL(arrayXSize, arrayDim);
	BOOST_CHECK_EQUAL(arrayYSize, arrayDim);

	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array2D_all_dim_ctr) {
	const int arrayDimX = 10;
	const int arrayDimY = 20;

	Array2D<int>* intArray = new Array2D<int>(arrayDimX, arrayDimY);// x should be 10, y should be 20

	int arrayXSize = intArray->getArraySizeX();
	int arrayYSize = intArray->getArraySizeY();

	BOOST_CHECK_EQUAL(arrayXSize, arrayDimX);
	BOOST_CHECK_EQUAL(arrayYSize, arrayDimY);

	delete intArray;
}

BOOST_AUTO_TEST_SUITE_END() // end Array2D_ctrs

BOOST_AUTO_TEST_SUITE(Array2D_Accessors)

BOOST_AUTO_TEST_CASE(Array2D_at_1) {
	Array2D<int>* intArray = new Array2D<int>();//sizes of all dimensions should be 100

												//init all values to 0

	intArray->initAllValues(0);

	const int x = 10;
	const int y = 10;
	const int val = 1;

	intArray->at(x, y) = val;
	int returnVal = intArray->at(x, y);

	BOOST_CHECK_EQUAL(val, returnVal);

	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array2D_at_2) {
	Array2D<int>* intArray = new Array2D<int>();//sizes of all dimensions should be 100

												//set values
	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			intArray->at(i, j) = i*j + i;
		}
	}
	//check values
	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			int returnVal = intArray->at(i, j);
			BOOST_CHECK_EQUAL(i*j + i, returnVal);
		}
	}

	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array2D_initAllValues) {
	Array2D<int>* intArray = new Array2D<int>();//sizes of all dimensions should be 100

	const int initVal = 0;

	intArray->initAllValues(initVal);

	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			int returnVal = intArray->at(i, j);
			BOOST_CHECK_EQUAL(returnVal, initVal);
		}
	}

	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array2D_operatorParen_get_set) {
	Array2D<int>* intArray = new Array2D<int>();//sizes of all dimensions should be 100

												//set values
	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			(*intArray)(i, j) = i*j + i;
		}
	}
	//check values
	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			int returnVal = (*intArray)(i, j);
			BOOST_CHECK_EQUAL(i*j + i, returnVal);
		}
	}

	delete intArray;
}

BOOST_AUTO_TEST_CASE(Array2D_operatorSqare_get_set) {
	Array2D<int>* intArray = new Array2D<int>();//sizes of all dimensions should be 100

												//set values
	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			(*intArray)[i][j] = i*j + i;
		}
	}
	//check values
	for (unsigned int i = 0; i < intArray->getArraySizeX(); ++i) {
		for (unsigned int j = 0; j < intArray->getArraySizeY(); ++j) {
			int returnVal = (*intArray)[i][j];
			BOOST_CHECK_EQUAL(i*j + i, returnVal);
		}
	}

	delete intArray;
}

BOOST_AUTO_TEST_SUITE_END() // end Array2D_Accessors

BOOST_AUTO_TEST_SUITE_END() // end Array3D_Tests