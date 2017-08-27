#include "stdafx.h"

#include <Backbone\BackboneBaseExceptions.h>
#include <Util\Array2D.h>
#include <Util\FileWriter.h>

using namespace GB;

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

BOOST_AUTO_TEST_SUITE(FileWriter_Tests)

BOOST_AUTO_TEST_SUITE(FileWriter_writeStringTests)

BOOST_FIXTURE_TEST_CASE(FileWriter_writeString, ReusableObjects) {

	FileWriter testWriter;
	testWriter.writeString("ba\nna\nna", TestFileLocation + "banana.bin");

	BOOST_CHECK(true == true);
}

BOOST_AUTO_TEST_SUITE_END() //end FileReader_writeStringTests

BOOST_AUTO_TEST_SUITE(FileWriter_createWriteStringTests)

BOOST_FIXTURE_TEST_CASE(FileWriter_createWriteString, ReusableObjects) {
	//Initialize all the necessary data
	FileWriter testWriter;
	ReusableObjects currentReusableObject = ReusableObjects();
	std::string outputString = "";

	//pass outputString into createWritableString
	testWriter.createWritableString(&currentReusableObject.outputArray, ',', &outputString);

	//write outputString into banana.bin
	testWriter.writeString(outputString, TestFileLocation + "banana.bin");

	BOOST_CHECK(true == true);
}

BOOST_AUTO_TEST_SUITE_END() //end FileWriter_createWriteStringTests

BOOST_AUTO_TEST_SUITE_END() // end FileWriter_Tests