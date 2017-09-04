#include "stdafx.h"

#include <Util\Point.h>
#include<Util\ClusterGreenhouse.h>

#include <set>

using namespace GB;


// Suite containing all cluster tests.
BOOST_AUTO_TEST_SUITE(ClusterGreenhouse_Tests);

// Suite containing all cluster constructor tests.
BOOST_AUTO_TEST_SUITE(ClusterGreenhouse_CTRs);

// Testing the ctr with dimensions 0 by 0 to make sure there are no intrinsic leaks.
BOOST_AUTO_TEST_CASE(ClusterGreenhouse_ZeroDimensions_CTR) {

	// Dimensions of 0 by 0.
	Point2D<int> testPoint{ 0,0 };

	// ClusterGreenhouse created with dimensions 0,0.
	ClusterGreenhouse* testCluster = new ClusterGreenhouse(testPoint);

	delete testCluster;
}

BOOST_AUTO_TEST_SUITE_END() // End ClusterGreenhouse_CTRs

BOOST_AUTO_TEST_SUITE_END() //End ClusterGreenhouse_Tests