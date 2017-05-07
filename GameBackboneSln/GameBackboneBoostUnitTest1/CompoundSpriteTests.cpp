#include "stdafx.h"

#include <AnimatedSprite.h>

#include <CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <string>

struct ReusableObjects
{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "..\\..\\Textures\\testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		sprite = new sf::Sprite(*aSpriteTexture);

		sf::Vector2u textureDim = aSpriteTexture->getSize();
		std::vector<std::vector<unsigned int>> aSpriteAnims;
		std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
		aSpriteAnims.push_back(aSpriteAnim1);
		animSet1 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);
		animSet2 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

		animSpriteWithAnim1 = new AnimatedSprite(*aSpriteTexture, animSet1);
		animSpriteWithAnim2 = new AnimatedSprite(*aSpriteTexture, animSet2);
	}
	~ReusableObjects() {
		delete aSpriteTexture;
		delete animSet1;
		delete animSet2;
		delete aSpriteTexture;
		delete animSpriteWithAnim1;
		delete animSpriteWithAnim2;
	}

	AnimatedSprite* animSpriteWithAnim1;
	AnimatedSprite* animSpriteWithAnim2;
	AnimationSet* animSet1;
	AnimationSet* animSet2;
	sf::Texture* aSpriteTexture;
	sf::Sprite* sprite;
};
BOOST_FIXTURE_TEST_SUITE(CompoundSpriteTests, ReusableObjects)

BOOST_AUTO_TEST_SUITE(CompoundSprite_ctr)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_default_ctr, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getSfSprites() == nullptr);
	BOOST_CHECK(compoundSprite->getaAnimatedSprites() == nullptr);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addAnimatedSprite_ctr, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	for (int i = 0; i < spriteVector.size(); i++) {
		BOOST_CHECK(compoundSprite->getSfSprites()->at(i) == spriteVector[i]);
	}

	for (int i = 0; i < emptyAnimatedSpriteVector.size(); i++) {
		BOOST_CHECK(compoundSprite->getaAnimatedSprites()->at(i) == emptyAnimatedSpriteVector[i]);
	}

	delete compoundSprite;
}
BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_ctr

BOOST_FIXTURE_TEST_SUITE(CompoundSprite_getter, ReusableObjects)

BOOST_AUTO_TEST_CASE(CompoundSprite_getSfSprites_Populated_Input_Vectors) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);
	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	BOOST_CHECK(compoundSprite->getSfSprites()->size() == 1);
	BOOST_CHECK(compoundSprite->getSfSprites()->at(0) == sprite);

	delete compoundSprite;
}

BOOST_AUTO_TEST_CASE(CompoundSprite_getSfSprites_Empty_Input_Vectors) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	BOOST_CHECK(compoundSprite->getSfSprites()->empty());
	
	delete compoundSprite;
}

BOOST_AUTO_TEST_CASE(CompoundSprite_getSfSprites_Defualt_Constructor) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getSfSprites()->empty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_CASE(CompoundSprite_getaAnimatedSprites_Empty_Input_Vectors) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	BOOST_CHECK(compoundSprite->getaAnimatedSprites()->empty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_CASE(CompoundSprite_getaAnimatedSprites_Defualt_Constructor) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getaAnimatedSprites()->empty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_getter

BOOST_AUTO_TEST_SUITE_END() // END CompoundSpriteTests