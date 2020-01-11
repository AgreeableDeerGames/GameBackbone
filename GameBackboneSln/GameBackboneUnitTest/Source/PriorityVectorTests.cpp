#include "stdafx.h"

#include <GameBackbone/Util/PriorityVector.h>


using namespace GB;

BOOST_AUTO_TEST_SUITE(PriorityVector_Tests)

BOOST_AUTO_TEST_SUITE(PriorityVector_CTRs)

BOOST_AUTO_TEST_CASE(PriorityVector_default_CTR) {
	PriorityVector<int> priorityVector;

	BOOST_CHECK(priorityVector.empty() == true);
	BOOST_CHECK(priorityVector.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END() // end PriorityVector_CTRs


BOOST_AUTO_TEST_SUITE(PriorityVector_Modifiers)

BOOST_AUTO_TEST_CASE(PriorityVector_push_back) {
	PriorityVector<int> priorityVector;
	
	//priorityVector.push_back(1);

	BOOST_CHECK(priorityVector.empty() == false);
	BOOST_CHECK(priorityVector.size() == 1);
}

BOOST_AUTO_TEST_SUITE_END() // end PriorityVector_Modifiers

BOOST_AUTO_TEST_SUITE_END() // end PriorityVector_Tests