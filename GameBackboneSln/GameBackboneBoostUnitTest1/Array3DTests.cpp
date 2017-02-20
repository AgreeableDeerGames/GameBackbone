#include "stdafx.h"

#include<Array3D.h>


BOOST_AUTO_TEST_CASE( default_ctr_test )  
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


