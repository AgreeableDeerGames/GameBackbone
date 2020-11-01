#include "stdafx.h"

#include <GameBackbone/Util/RandGen.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(RandGen_Tests)

BOOST_AUTO_TEST_SUITE(RandGen_CTRs)

BOOST_AUTO_TEST_CASE(RandGen_default_CTR_test) {

	RandGen testRandGen;

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen.uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);
}

BOOST_AUTO_TEST_CASE(RandGen_seed_CTR_test) {
	std::string seedString = "TestString";
	RandGen testRandGen(seedString);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen.getSeed());

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen.uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);
}

BOOST_AUTO_TEST_CASE(RandGen_copy_CTR_test) {
	std::string seedString = std::string("TestString");
	RandGen testRandGen(seedString);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen.getSeed());

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen.uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);

	// Copy
	RandGen copyRandGen(testRandGen);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", copyRandGen.getSeed());

	// Ensure that the Distributor has been set up correctly
	double copyOutput = copyRandGen.uniDist(0, 1);
	BOOST_CHECK(copyOutput >= 0 && copyOutput < 1);
}

BOOST_AUTO_TEST_CASE(RandGen_move_CTR_test) {
	std::string seedString = std::string("TestString");
	RandGen testRandGen(seedString);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen.getSeed());

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen.uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);

	// Copy
	RandGen copyRandGen(std::move(testRandGen));

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", copyRandGen.getSeed());

	// Ensure that the Distributor has been set up correctly
	double copyOutput = copyRandGen.uniDist(0, 1);
	BOOST_CHECK(copyOutput >= 0 && copyOutput < 1);
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_CTRs


BOOST_AUTO_TEST_SUITE(RandGen_setter)

BOOST_AUTO_TEST_CASE(RandGen_SetSeed_test) {
	std::string seedString("TestString");

	RandGen testRandGen;
	testRandGen.setSeed(seedString);

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen.uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen.getSeed());
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_setter


BOOST_AUTO_TEST_SUITE(RandGen_Generator)

BOOST_AUTO_TEST_CASE(RandGen_same_Seed_test) {
	std::string seedString("TestString");

	RandGen testRandGen1(seedString);
	RandGen testRandGen2(seedString);

	// Ensure that the outputs for the same seed are the same
	double output1 = testRandGen1.uniDist(0, 1);
	double output2 = testRandGen2.uniDist(0, 1);
	BOOST_CHECK(output1 == output2);
}

BOOST_AUTO_TEST_CASE(RandGen_different_Seed_test) {
	std::string seedString1("TestString1");
	std::string seedString2("TestString2");

	RandGen testRandGen1(seedString1);
	RandGen testRandGen2(seedString2);

	// Ensure that the outputs for the same seed are the same
	double output1 = testRandGen1.uniDist(0, 1);
	double output2 = testRandGen2.uniDist(0, 1);
	BOOST_CHECK(output1 != output2);
}

BOOST_AUTO_TEST_CASE(RandGen_uniDist) {
	RandGen testRandGen;

	int min = 0;
	int max = 1;
	for (unsigned int ii = 0; ii < 10; ++ii)
	{
		// Ensure that the outputs for the same seed are the same
		double output = testRandGen.uniDist(min, max);
		BOOST_CHECK(min <= output && output < max);
		min = min + 1;
		max = max + 4;
	}
}

BOOST_AUTO_TEST_CASE(RandGen_uniDist_toInt) {
	RandGen testRandGen;

	int min = 0;
	int max = 1;
	for (unsigned int ii = 0; ii < 10; ++ii)
	{
		// Ensure that the outputs for the same seed are the same
		int output = (int)testRandGen.uniDist(min, max);
		BOOST_CHECK(min <= output && output < max);
		min = min + 1;
		max = max + 4;
	}
}

BOOST_AUTO_TEST_CASE(RandGen_uniDist_bad_range) {
	RandGen testRandGen;

	int min = 1;
	int max = 0;

	// Ensure that the outputs for the same seed are the same
	BOOST_CHECK_THROW(testRandGen.uniDist(min, max), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_Generator

BOOST_AUTO_TEST_SUITE_END() // end RandGen_Tests