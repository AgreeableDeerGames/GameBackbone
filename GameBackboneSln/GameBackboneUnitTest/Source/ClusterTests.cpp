#include "stdafx.h"

#include <GameBackbone/Util/Cluster.h>
#include <GameBackbone/Util/SFUtil.h>

#include <SFML/System/Vector2.hpp>

#include <set>

using namespace GB;


// Suite containing all cluster tests.
BOOST_AUTO_TEST_SUITE(Cluster_Tests);

// Suite containing all cluster constructor tests.
BOOST_AUTO_TEST_SUITE(Cluster_CTRs);

// Testing the ctr at initial point (0,0) to make sure there are no intrinsic leaks and that points are correctly set.
BOOST_AUTO_TEST_CASE(Cluster_ZeroPoint_CTR) {

	// Point at (0,0).
	sf::Vector2i testPoint{0,0};

	// Create border points to compare against.
	std::set<sf::Vector2i, Vec2Compare<int>>* testBorderPoints = new std::set<sf::Vector2i, Vec2Compare<int>>;
	testBorderPoints->insert(sf::Vector2i{0, 1});
	testBorderPoints->insert(sf::Vector2i{1, 0});
	testBorderPoints->insert(sf::Vector2i{-1, 0});
	testBorderPoints->insert(sf::Vector2i{0, -1});

	// Cluster created at (0,0).
	Cluster* testCluster = new Cluster(testPoint);

	// Ensure the border points are what they should be.
	BOOST_CHECK( *testCluster->getBorderPointSet() == *testBorderPoints );

	delete testBorderPoints;
	delete testCluster;
}

BOOST_AUTO_TEST_SUITE_END() // End Cluster_CTRs

BOOST_AUTO_TEST_SUITE_END() // End Cluster_Tests