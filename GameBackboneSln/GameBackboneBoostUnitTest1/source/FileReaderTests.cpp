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
		
		outputStringTsv = "fruit\tred\tyellow\tblue\napple\t255\t0\t0\norange\t255\t255\t0\nbanana\t0\t255\t0\nplantain\t0\t255\t255";
		outputStringCsv = "fruit,red,yellow,blue\napple,255,0,0\norange,255,255,0\nbanana,0,255,0\nplantain,0,255,255";
		outputStringFunnyTxt = "#@<bann0ana=;@KPet0q";
		outputStringFunnyTxt[7] = '\0';
		outputStringFunnyTxt[18] = '\0';
		nullTxt = "000";
		nullTxt[0] = nullTxt[1] = nullTxt[2] = '\0';
	}
	~ReusableObjects() {
	}

	Array2D<std::string> outputArray;
	std::string outputStringTsv;
	std::string outputStringCsv;
	std::string outputStringFunnyTxt;
	std::string nullTxt;
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
BOOST_FIXTURE_TEST_CASE(FileReader_readFile_BadFile_test, ReusableObjects) {

	FileReader testReader;

	// Ensure that readFile throws an exception if the file doesn't exist.
	BOOST_CHECK_THROW(testReader.readFile(R"(..\NOTAREALFILE.txt)", 3, 3, '\t'), Error::FileReader_BadFile);
}

BOOST_AUTO_TEST_SUITE_END() // end FileReader_readFile

BOOST_AUTO_TEST_SUITE(FileReader_readFileBinaryInput)

// Ensure that readFileBinaryInput with a .tsv file gives correct results
BOOST_FIXTURE_TEST_CASE(FileReader_readFileBinaryInput_tsv_test, ReusableObjects) {

	FileReader testReader;
	std::string testFile = testReader.readFileBinaryInput(R"(..\TestInFile.tsv)");

	// Ensure that the output string is what is in the file.
	BOOST_CHECK(testFile == outputStringTsv);
}

// Ensure that readFileBinaryInput with a .csv file gives correct results
BOOST_FIXTURE_TEST_CASE(FileReader_readFileBinaryInput_csv_test, ReusableObjects) {

	FileReader testReader;
	std::string testFile = testReader.readFileBinaryInput(R"(..\TestInFile.csv)");

	// Ensure that the output string is what is in the file.
	BOOST_CHECK(testFile == outputStringCsv);
}

// Ensure that readFileBinaryInput with a .txt file gives correct results
BOOST_FIXTURE_TEST_CASE(FileReader_readFileBinaryInput_txt_test, ReusableObjects) {

	FileReader testReader;
	std::string testFile = testReader.readFileBinaryInput(R"(..\FunnyCharacters.txt)");

	// Ensure that the output string is what is in the file.
	BOOST_CHECK(testFile == outputStringFunnyTxt);
}

// Ensure that readFileBinaryInput with a .txt file gives correct results
BOOST_FIXTURE_TEST_CASE(FileReader_readFileBinaryInput_nulltxt_test, ReusableObjects) {

	FileReader testReader;
	std::string testFile = testReader.readFileBinaryInput(R"(..\null.txt)");

	// Ensure that the output string is what is in the file.
	BOOST_CHECK(testFile == nullTxt);
}

// Ensure that readFileInputBinary throws an exception if the file doesn't exist.
BOOST_FIXTURE_TEST_CASE(FileReader_readFileBinaryInput_BadFile_test, ReusableObjects) {

	FileReader testReader;

	// Ensure that readFile throws an exception if the file doesn't exist.
	BOOST_CHECK_THROW(testReader.readFileBinaryInput(R"(..\NOTAREALFILE.txt)"), Error::FileReader_BadFile);
}

BOOST_AUTO_TEST_SUITE_END() // end FileReader_readFileBinaryInput

BOOST_AUTO_TEST_SUITE_END() // end FileReader_Tests