#include "stdafx.h"

#include <Util\Array2D.h>
#include <Util\FileManager.h>
#include <Backbone\BackboneBaseExceptions.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(FileManager_Tests)

BOOST_AUTO_TEST_SUITE(FileManager_encryptDecryptString)

// Ensure that encryptDecryptString gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_encryptDecryptString_general) {
	FileManager testManager;

	std::string testString = "Test String with Some Form of Stuff...";
	std::string key = "KEY";

	std::string outputString = testManager.encryptDecryptString(testString, key);
	BOOST_CHECK(outputString != testString);
	BOOST_CHECK(outputString.size() == testString.size());

	outputString = testManager.encryptDecryptString(outputString, key);
	BOOST_CHECK(outputString == testString);
}

// Ensure that encryptDecryptString gives correct results given the same key as input string.
BOOST_AUTO_TEST_CASE(FileManager_encryptDecryptString_same_Key) {
	FileManager testManager;

	std::string testString = "Test String with Some Form of Stuff...";
	std::string key = "Test String with Some Form of Stuff...";

	std::string outputString = testManager.encryptDecryptString(testString, key);
	BOOST_CHECK(outputString != testString);
	BOOST_CHECK(outputString.size() == testString.size());

	for (char character : outputString)
	{ 
		BOOST_CHECK(character == '\0');
	}

	outputString = testManager.encryptDecryptString(outputString, key);
	BOOST_CHECK(outputString == testString);
}

// Ensure that encryptDecryptString gives correct results given the same key as input string.
BOOST_AUTO_TEST_CASE(FileManager_encryptDecryptString_slashN) {
	FileManager testManager;

	std::string testString = "SSSSSSSSSSSSSSSSSSSSSSSSSS";
	std::string key = "Y";

	std::string outputString = testManager.encryptDecryptString(testString, key);
	BOOST_CHECK(outputString != testString);
	BOOST_CHECK(outputString.size() == testString.size());

	for (char character : outputString)
	{
		BOOST_CHECK(character == '\n');
	}

	outputString = testManager.encryptDecryptString(outputString, key);
	BOOST_CHECK(outputString == testString);
}



BOOST_AUTO_TEST_SUITE_END() // end FileManager_encryptDecryptString

BOOST_AUTO_TEST_SUITE_END() // end FileManager_Tests