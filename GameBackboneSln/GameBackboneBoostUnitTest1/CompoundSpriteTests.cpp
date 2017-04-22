#include "stdafx.h"

#include <CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <string>

struct ReusableObjects
{
	ReusableObjects()
	{
		
	}
	~ReusableObjects()
	{

	}
};
BOOST_FIXTURE_TEST_SUITE(CompoundSpriteTests, ReusableObjects)

BOOST_AUTO_TEST_CASE(CompoundSprite_default_ctr) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getSfSprites() == nullptr);
	BOOST_CHECK(compoundSprite->getaAnimatedSprites() == nullptr);

	delete compoundSprite;
}

BOOST_AUTO_TEST_CASE(CompoundSprite_addAnimatedSprite_ctr) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	for (int i = 0; i < spriteVector.size(); i++){
		BOOST_CHECK(compoundSprite->getSfSprites()->at(i) == spriteVector[i]);
	}

	for (int i = 0; i < emptyAnimatedSpriteVector.size(); i++) {
		BOOST_CHECK(compoundSprite->getaAnimatedSprites()->at(i) == emptyAnimatedSpriteVector[i]);
	}

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END()