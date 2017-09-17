#include "stdafx.h"

#include <Util/Array2D.h>
#include <Util/FileManager.h>
#include <Backbone/BackboneBaseExceptions.h>

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

// Ensure that encryptDecryptString gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_encryptDecryptString_EmptyKey) {
	FileManager testManager;

	std::string testString = "Test String with Some Form of Stuff...";
	std::string key = "";

	BOOST_CHECK_THROW(testManager.encryptDecryptString(testString, key), GB::Error::FileManager_EmptyKey);
}

// Ensure that encryptDecryptString gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_encryptDecryptString_EmptyString) {
	FileManager testManager;

	std::string testString = "";
	std::string key = "KEY";

	std::string outputString = testManager.encryptDecryptString(testString, key);
	BOOST_CHECK(outputString == testString);
	BOOST_CHECK(outputString.size() == testString.size());
}


BOOST_AUTO_TEST_SUITE_END() // end FileManager_encryptDecryptString


BOOST_AUTO_TEST_SUITE(FileManager_fileVerification)

// Ensure that getFileSize and getFileHash gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_fileVerification_csv) {
	FileManager testManager;

	std::string filePath = TestFileLocation + "TestInFile.csv";
	std::size_t testFileSize = 90;
	std::size_t testFileHash = 999762491443133160;

	std::size_t outputSize = testManager.getFileSize(filePath);
	BOOST_CHECK(outputSize == testFileSize);

	std::size_t outputHash = testManager.getFileHash(filePath);
	BOOST_CHECK(outputHash == testFileHash);
}

// Ensure that getFileSize and getFileHash gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_fileVerification_tsv) {
	FileManager testManager;

	std::string filePath = TestFileLocation + "TestInFile.tsv";
	std::size_t testFileSize = 90;
	std::size_t testFileHash = 7881321868461860337;

	std::size_t outputSize = testManager.getFileSize(filePath);
	BOOST_CHECK(outputSize == testFileSize);

	std::size_t outputHash = testManager.getFileHash(filePath);
	BOOST_CHECK(outputHash == testFileHash);
}

// Ensure that getFileSize and getFileHash gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_fileVerification_null) {
	FileManager testManager;

	std::string filePath = TestFileLocation + "null.txt";
	std::size_t testFileSize = 3;
	std::size_t testFileHash = 15658191375538532279;

	std::size_t outputSize = testManager.getFileSize(filePath);
	BOOST_CHECK(outputSize == testFileSize);

	std::size_t outputHash = testManager.getFileHash(filePath);
	BOOST_CHECK(outputHash == testFileHash);
}

// Ensure that getFileSize and getFileHash gives correct results given empty strings.
BOOST_AUTO_TEST_CASE(FileManager_fileVerification_EmptyString) {
	FileManager testManager;

	std::string filePath = "";

	std::size_t outputSize = testManager.getFileSize(filePath);
	BOOST_CHECK(outputSize == 0);

	//std::size_t outputHash = testManager.getFileHash(filePath);
	BOOST_CHECK_THROW(testManager.getFileHash(filePath), GB::Error::FileManager_BadFile);
}

BOOST_AUTO_TEST_SUITE_END() // end FileManager_fileVerification


BOOST_AUTO_TEST_SUITE_END() // end FileManager_Tests