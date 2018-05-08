#include "stdafx.h"

#include <Util/Point.h>
#include<Util/Cluster.h>

#include <set>

using namespace GB;


// Suite containing all cluster tests.
BOOST_AUTO_TEST_SUITE(Cluster_Tests);

// Suite containing all cluster constructor tests.
BOOST_AUTO_TEST_SUITE(Cluster_CTRs);

// Testing the ctr at initial point (0,0) to make sure there are no intrinsic leaks and that points are correctly set.
BOOST_AUTO_TEST_CASE(Cluster_ZeroPoint_CTR) {

	// Point at (0,0).
	Point2D<int> testPoint{0,0};

	// Create border points to compare against.
	std::set<Point2D<int>>* testBorderPoints = new std::set<Point2D<int>>;
	testBorderPoints->insert(Point2D<int>{0, 1});
	testBorderPoints->insert(Point2D<int>{1, 0});
	testBorderPoints->insert(Point2D<int>{-1, 0});
	testBorderPoints->insert(Point2D<int>{0, -1});

	// Cluster created at (0,0).
	Cluster* testCluster = new Cluster(testPoint);

	// Ensure the border points are what they should be.
	BOOST_CHECK( *testCluster->getBorderPointSet() == *testBorderPoints );

	delete testBorderPoints;
	delete testCluster;
}

BOOST_AUTO_TEST_SUITE_END() // End Cluster_CTRs

BOOST_AUTO_TEST_SUITE_END() // End Cluster_Tests