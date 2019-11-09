#include "stdafx.h"

#include <GameBackbone\Util\SFUtil.h>

#include <SFML\Graphics\Sprite.hpp>

using namespace GB;

// Contains all of the tests for SFUtilTests
BOOST_AUTO_TEST_SUITE(SFUtilTests)

// Contains all of the tests for toDrawableVectorTests
BOOST_AUTO_TEST_SUITE(toDrawableVectorTests)

BOOST_AUTO_TEST_CASE(toDrawableVector_Sprite) {
	std::vector<sf::Sprite> spriteList;
	spriteList.push_back(sf::Sprite());

	std::vector<sf::Drawable*> returnVector = toDrawableVector(spriteList);

	BOOST_CHECK_EQUAL(returnVector.size(), spriteList.size());
	for (size_t ii = 0; ii < spriteList.size(); ii++)
	{
		BOOST_CHECK_EQUAL(returnVector.at(ii), &spriteList.at(ii));
	}
}

BOOST_AUTO_TEST_SUITE_END() // end toDrawableVectorTests

// Keep at end of file
BOOST_AUTO_TEST_SUITE_END()