#include "stdafx.h"
#include "RandGen.h"

using namespace GB;

BOOST_AUTO_TEST_SUITE(RandGen_Tests)

BOOST_AUTO_TEST_SUITE(RandGen_ctrs)

BOOST_AUTO_TEST_CASE(RandGen_default_ctr_test) {

	RandGen* testRandGen = new RandGen();

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist();
	BOOST_CHECK(output >= 0 && output < 1);

	delete testRandGen;
}

BOOST_AUTO_TEST_CASE(RandGen_seed_ctr_test) {
	RandGen* testRandGen = new RandGen("TestString");

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen->getSeed());

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist();
	BOOST_CHECK(output >= 0 && output < 1);

	delete testRandGen;
}

BOOST_AUTO_TEST_CASE(RandGen_minmax_ctr_test) {
	RandGen* testRandGen = new RandGen(3, 4);

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist();
	BOOST_CHECK(output >= 3 && output < 4);

	delete testRandGen;
}

BOOST_AUTO_TEST_CASE(RandGen_seedminmax_ctr_test) {
	RandGen* testRandGen = new RandGen("TestString", 3, 4);


	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen->getSeed());

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist();
	BOOST_CHECK(output >= 3 && output < 4);

	delete testRandGen;
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_ctrs


BOOST_AUTO_TEST_SUITE(RandGen_setter)

BOOST_AUTO_TEST_CASE(RandGen_SetSeed_test) {

	RandGen* testRandGen = new RandGen();
	testRandGen->setSeed("TestString");

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist();
	BOOST_CHECK(output >= 0 && output < 1);

	//Ensure that the seed is what we set;
	BOOST_CHECK_EQUAL("TestString", testRandGen->getSeed());

	delete testRandGen;
}

BOOST_AUTO_TEST_CASE(RandGen_SetUniDistributor_test) {

	RandGen* testRandGen = new RandGen();
	testRandGen->setUniDistributor(3, 4);

	// Ensure that the Distributor has been set up correctly
	double output = testRandGen->uniDist();
	BOOST_CHECK(output >= 3 && output < 4);

	delete testRandGen;
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_setter


BOOST_AUTO_TEST_SUITE(RandGen_Generator)

BOOST_AUTO_TEST_CASE(RandGen_same_Seed_test) {

	RandGen* testRandGen1 = new RandGen("TestString");
	RandGen* testRandGen2 = new RandGen("TestString");

	// Ensure that the outputs for the same seed are the same
	double output1 = testRandGen1->uniDist();
	double output2 = testRandGen2->uniDist();
	BOOST_CHECK(output1 == output2);

	delete testRandGen1;
	delete testRandGen2;
}

BOOST_AUTO_TEST_CASE(RandGen_different_Seed_test) {

	RandGen* testRandGen1 = new RandGen("TestString1");
	RandGen* testRandGen2 = new RandGen("TestString2");

	// Ensure that the outputs for the same seed are the same
	double output1 = testRandGen1->uniDist();
	double output2 = testRandGen2->uniDist();
	BOOST_CHECK(output1 != output2);

	delete testRandGen1;
	delete testRandGen2;
}

BOOST_AUTO_TEST_SUITE_END() // end RandGen_Generator

BOOST_AUTO_TEST_SUITE_END() // end RandGen_Tests