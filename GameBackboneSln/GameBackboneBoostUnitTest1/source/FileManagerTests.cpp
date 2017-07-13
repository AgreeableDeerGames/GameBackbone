#include "stdafx.h"

#include <Util\Array2D.h>
#include <Util\FileManager.h>
#include <Backbone\BackboneBaseExceptions.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(FileManager_Tests)

BOOST_AUTO_TEST_SUITE(FileManager_encryptDecryptString)

// Ensure that encryptDecryptString gives correct results.
BOOST_AUTO_TEST_CASE(FileManager_encryptDecryptString_tsv_test) {
	FileManager testManager;


	std::string testString = "Test String with Some Form of Stuff...";
	std::string key = "KEY";


	testString = testManager.encryptDecryptString(testString, key);
	std::cout << testString << "\n";

	testString = testManager.encryptDecryptString(testString, key);
	std::cout << testString << "\n";

}



BOOST_AUTO_TEST_SUITE_END() // end FileManager_encryptDecryptString

BOOST_AUTO_TEST_SUITE_END() // end FileManager_Tests