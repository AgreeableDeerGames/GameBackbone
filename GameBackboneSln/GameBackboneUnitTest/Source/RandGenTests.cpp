#include "stdafx.h"

#include <GameBackbone/Util/RandGen.h>

using namespace GB;

BOOST_AUTO_TEST_SUITE(RandGen_Tests)

BOOST_AUTO_TEST_SUITE(RandGen_CTRs)

BOOST_AUTO_TEST_CASE(RandGen_default_CTR_test) {

	RandGen* testRandGen = new RandGen();

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);

	delete testRandGen;
}

BOOST_AUTO_TEST_CASE(RandGen_seed_CTR_test) {
	std::string* seedString = new std::string("TestString");
	RandGen* testRandGen = new RandGen(seedString);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen->getSeed());

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);

	delete seedString;
	delete testRandGen;
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_CTRs


BOOST_AUTO_TEST_SUITE(RandGen_setter)

BOOST_AUTO_TEST_CASE(RandGen_SetSeed_test) {
	std::string* seedString = new std::string("TestString");

	RandGen* testRandGen = new RandGen();
	testRandGen->setSeed(seedString);

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist(0, 1);
	BOOST_CHECK(output >= 0 && output < 1);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen->getSeed());

	delete seedString;
	delete testRandGen;
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_setter


BOOST_AUTO_TEST_SUITE(RandGen_Generator)

BOOST_AUTO_TEST_CASE(RandGen_same_Seed_test) {
	std::string* seedString = new std::string("TestString");

	RandGen* testRandGen1 = new RandGen(seedString);
	RandGen* testRandGen2 = new RandGen(seedString);

	// Ensure that the outputs for the same seed are the same
	double output1 = testRandGen1->uniDist(0, 1);
	double output2 = testRandGen2->uniDist(0, 1);
	BOOST_CHECK(output1 == output2);

	delete seedString;
	delete testRandGen1;
	delete testRandGen2;
}

BOOST_AUTO_TEST_CASE(RandGen_different_Seed_test) {
	std::string* seedString1 = new std::string("TestString1");
	std::string* seedString2 = new std::string("TestString2");

	RandGen* testRandGen1 = new RandGen(seedString1);
	RandGen* testRandGen2 = new RandGen(seedString2);

	// Ensure that the outputs for the same seed are the same
	double output1 = testRandGen1->uniDist(0, 1);
	double output2 = testRandGen2->uniDist(0, 1);
	BOOST_CHECK(output1 != output2);

	delete seedString1;
	delete seedString2;
	delete testRandGen1;
	delete testRandGen2;
}

BOOST_AUTO_TEST_CASE(RandGen_uniDist) {
	RandGen* testRandGen = new RandGen();

	int min = 0;
	int max = 1;
	for (unsigned int ii = 0; ii < 10; ++ii)
	{
		// Ensure that the outputs for the same seed are the same
		double output = testRandGen->uniDist(min, max);
		BOOST_CHECK(min <= output && output < max);
		min = min + 1;
		max = max + 4;
	}

	delete testRandGen;
}

BOOST_AUTO_TEST_CASE(RandGen_uniDist_toInt) {
	RandGen* testRandGen = new RandGen();

	int min = 0;
	int max = 1;
	for (unsigned int ii = 0; ii < 10; ++ii)
	{
		// Ensure that the outputs for the same seed are the same
		int output = (int)testRandGen->uniDist(min, max);
		BOOST_CHECK(min <= output && output < max);
		min = min + 1;
		max = max + 4;
	}

	delete testRandGen;
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_Generator

BOOST_AUTO_TEST_SUITE_END() // end RandGen_Tests