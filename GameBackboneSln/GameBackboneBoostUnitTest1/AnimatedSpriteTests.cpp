#include "stdafx.h"

#include <AnimatedSprite.h>

#include <SFML/Graphics.hpp>

#include <chrono>
#include <string>
#include <thread>

struct ReusableObjects
{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "..\\..\\Textures\\testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		//create animation set
		sf::Vector2u textureDim = aSpriteTexture->getSize();
		std::vector<std::vector<unsigned int>> aSpriteAnims;
		std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
		aSpriteAnims.push_back(aSpriteAnim1);
		animSet = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

		//create animatedSprite
		animSpriteWithAnim = new AnimatedSprite(*aSpriteTexture, animSet);
	}

	~ReusableObjects() {
		delete animSpriteWithAnim;
		delete animSet;
		delete aSpriteTexture;
	}

	AnimatedSprite* animSpriteWithAnim;
	AnimationSet* animSet;
	sf::Texture* aSpriteTexture;
};

//keep at start of file
BOOST_FIXTURE_TEST_SUITE(AnimatedSpriteTests, ReusableObjects)

BOOST_AUTO_TEST_CASE(AnimatedSprite_default_ctr) {
	AnimatedSprite* animSprite = new AnimatedSprite();

	BOOST_CHECK(!animSprite->isAnimating());
	BOOST_CHECK(animSprite->getCurrentFrame() == 0);
	BOOST_CHECK(animSprite->getAnimationDelay() == 0);
	BOOST_CHECK(animSprite->getCurrentAnimationId() == 0);

	delete animSprite;
}

BOOST_AUTO_TEST_CASE(AnimatedSprite_Texture_ctr) {
	AnimatedSprite* animSprite = new AnimatedSprite(*aSpriteTexture);

	BOOST_CHECK(!animSprite->isAnimating());
	BOOST_CHECK(animSprite->getCurrentFrame() == 0);
	BOOST_CHECK(animSprite->getAnimationDelay() == 0);
	BOOST_CHECK(animSprite->getCurrentAnimationId() == 0);

	delete animSprite;
}

BOOST_AUTO_TEST_CASE(AnimatedSprite_Texture_and_Animations) {
	BOOST_CHECK(!animSpriteWithAnim->isAnimating());
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	BOOST_CHECK(animSpriteWithAnim->getAnimationDelay() == 0);
	BOOST_CHECK(animSpriteWithAnim->getCurrentAnimationId() == 0);
}

BOOST_AUTO_TEST_CASE(AnimatedSprite_Start_Animation) {
	animSpriteWithAnim->runAnimation(0);
	BOOST_CHECK(animSpriteWithAnim->isAnimating());
	BOOST_CHECK(animSpriteWithAnim->getCurrentAnimationId() == 0);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
}

BOOST_AUTO_TEST_CASE(AnimatedSprite_Animation_Next_Frame) {
	animSpriteWithAnim->runAnimation(0);
	BOOST_CHECK(animSpriteWithAnim->isAnimating());
	animSpriteWithAnim->setAnimationDelay(2);
	//fake sleep for 1ms longer than the min delay
	sf::Time timeAfterDelay = sf::milliseconds(3);
	animSpriteWithAnim->update(timeAfterDelay);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
}

BOOST_AUTO_TEST_CASE(AnimatedSprite_Animation_Next_Frame_Not_Enough_Time) {
	animSpriteWithAnim->runAnimation(0);
	BOOST_CHECK(animSpriteWithAnim->isAnimating());
	animSpriteWithAnim->setAnimationDelay(2);
	//fake sleep for 1ms shorter than the min delay
	sf::Time timeAfterDelay = sf::milliseconds(1);
	animSpriteWithAnim->update(timeAfterDelay);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
}

//Keep at end of file
BOOST_AUTO_TEST_SUITE_END()