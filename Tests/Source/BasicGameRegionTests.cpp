#include "stdafx.h"

#include <GameBackbone/Core/BasicGameRegion.h>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

using namespace GB;

namespace
{
	class TestGameRegion : public BasicGameRegion
	{
		void update(sf::Int64 /*elapsedTime*/) override {}
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
		bool handleEvent(sf::Int64 /*elapsedTime*/, const sf::Event& /*event*/) override { return false; };
	};
}

BOOST_AUTO_TEST_SUITE(BasicGameRegionTests)

	BOOST_AUTO_TEST_CASE(BasicGameRegion_nextRegion_starts_as_self)
	{
		TestGameRegion region;
		auto& next = region.getNextRegion();
		BOOST_CHECK(&next == &region);
	}

	BOOST_AUTO_TEST_CASE(BasicGameRegion_nextRegion_transition)
	{
		TestGameRegion region;
		TestGameRegion secondRegion;
		region.setNextRegion(secondRegion);
		auto& next = region.getNextRegion();
		BOOST_CHECK(&next == &secondRegion);
	}

BOOST_AUTO_TEST_SUITE_END() // BasicGameRegionTests


