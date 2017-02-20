#include "stdafx.h"

#include <PathFinder.h>

BOOST_AUTO_TEST_CASE(Pathfinder_default_ctr_test) {

	Pathfinder* pathfinder = new Pathfinder();

	NavigationGrid* navGrid = pathfinder->getNavigationGrid();
	BOOST_CHECK(nullptr == navGrid);

	delete pathfinder;
}

BOOST_AUTO_TEST_CASE(Pathfinder_test_test) {
	Pathfinder pathfinder;

	BOOST_CHECK_EQUAL(1, 1);
}