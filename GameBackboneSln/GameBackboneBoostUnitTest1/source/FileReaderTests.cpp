#include "stdafx.h"

#include <Backbone\BackboneBaseExceptions.h>
#include <Util\Array2D.h>
#include <Util\FileReader.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(FileReader_Tests)

struct ReusableObjects
{
	ReusableObjects() {
		outputArray = Array2D<std::string>(5, 4);
		outputArray[0][0] = "fruit";
		outputArray[0][1] = "red";
		outputArray[0][2] = "yellow";
		outputArray[0][3] = "blue";
		outputArray[1][0] = "apple";
		outputArray[1][1] = "255";
		outputArray[1][2] = "0";
		outputArray[1][3] = "0";
		outputArray[2][0] = "orange";
		outputArray[2][1] = "255";
		outputArray[2][2] = "255";
		outputArray[2][3] = "0";
		outputArray[3][0] = "banana";
		outputArray[3][1] = "0";
		outputArray[3][2] = "255";
		outputArray[3][3] = "0";
		outputArray[4][0] = "plantain";
		outputArray[4][1] = "0";
		outputArray[4][2] = "255";
		outputArray[4][3] = "255";
	}
	~ReusableObjects() {
	}

	Array2D<std::string> outputArray;
};

BOOST_AUTO_TEST_SUITE(FileReader_readFile)

// Ensure that readFile with a .tsv file gives correct results.
BOOST_FIXTURE_TEST_CASE(FileReader_readFile_tsv_test, ReusableObjects) {

	FileReader testReader;
	Array2D<std::string> testFile = testReader.readFile(R"(..\TestInFile.tsv)", 5, 4, '\t');

	// Ensure that the output array is what is in the file.
	for (int ii = 0; ii < 5; ++ii) {
		for (int jj = 0; jj < 4; ++jj) {
			BOOST_CHECK(testFile[ii][jj] == outputArray[ii][jj]);
		}
	}
}

// Ensure that readFile with a .csv file gives correct results.
BOOST_FIXTURE_TEST_CASE(FileReader_readFile_csv_test, ReusableObjects) {

	FileReader testReader;
	Array2D<std::string> testFile = testReader.readFile(R"(..\TestInFile.csv)", 5, 4, ',');

	// Ensure that the output array is what is in the file.
	for (int ii = 0; ii < 5; ++ii) {
		for (int jj = 0; jj < 4; ++jj) {
			BOOST_CHECK(testFile[ii][jj] == outputArray[ii][jj]);
		}
	}
}

// Ensure that readFile with a size that is smaller than the file gives correct results.
BOOST_FIXTURE_TEST_CASE(FileReader_readFile_tsv_partial_test, ReusableObjects) {

	FileReader testReader;
	Array2D<std::string> testFile = testReader.readFile(R"(..\TestInFile.tsv)", 3, 3, '\t');

	// Ensure that the output array is what is in the file.
	for (int ii = 0; ii < 3; ++ii) {
		for (int jj = 0; jj < 3; ++jj) {
			BOOST_CHECK(testFile[ii][jj] == outputArray[ii][jj]);
		}
	}
}

// Ensure that readFile throws an exception if the file doesn't exist.
BOOST_FIXTURE_TEST_CASE(FileReader_BadFile_test, ReusableObjects) {

	FileReader testReader;

	// Ensure that readFile throws an exception if the file doesn't exist.
	BOOST_CHECK_THROW(testReader.readFile(R"(..\NOTAREALFILE.txt)", 3, 3, '\t'), Error::FileReader_BadFile);
}

BOOST_AUTO_TEST_SUITE_END() // end FileReader_readFile

BOOST_AUTO_TEST_SUITE_END() // end FileReader_Tests