#include "stdafx.h"

#include <AnimatedSprite.h>
#include <BackboneBaseExceptions.h>

#include <SFML/Graphics.hpp>

#include <chrono>
#include <string>
#include <thread>

using namespace GB;

/// <summary>
/// Struct to store objects that can be reused for all or nearly all 
/// of the unit tests in this file. This struct is meant to be used with fixtures
/// at the unit test level.
/// </summary>
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

//Contains all of the tests for AnimatedSprite
BOOST_AUTO_TEST_SUITE(AnimatedSpriteTests)

//Contains all of the tests for AnimatedSprite constructors
BOOST_AUTO_TEST_SUITE(AnimatedSprite_ctrs)

//Tests the AnimatedSprite default constructor
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_default_ctr, ReusableObjects) {
	AnimatedSprite* animSprite = new AnimatedSprite();

	//ensure that everything is set to null or 0
	BOOST_CHECK(!animSprite->isAnimating());
	BOOST_CHECK(animSprite->getCurrentFrame() == 0);
	BOOST_CHECK(animSprite->getAnimationDelay() == 0);
	BOOST_CHECK(animSprite->getCurrentAnimationId() == 0);

	delete animSprite;
}

//Tests the AnimatedSprite constructor that takes in a texture
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Texture_ctr, ReusableObjects) {
	AnimatedSprite* animSprite = new AnimatedSprite(*aSpriteTexture);

	//ensure that everything is set to null or 0
	BOOST_CHECK(!animSprite->isAnimating());
	BOOST_CHECK(animSprite->getCurrentFrame() == 0);
	BOOST_CHECK(animSprite->getAnimationDelay() == 0);
	BOOST_CHECK(animSprite->getCurrentAnimationId() == 0);

	//ensure that the texture is correctly set
	BOOST_CHECK(animSprite->getTexture() == aSpriteTexture);

	delete animSprite;
}

//Tests the AnimatedSprite constructor that takes a texture and an AnimationSet
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Texture_and_Animations, ReusableObjects) {

	//ensure that everything is set to null or 0
	BOOST_CHECK(!animSpriteWithAnim->isAnimating());
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	BOOST_CHECK(animSpriteWithAnim->getAnimationDelay() == 0);
	BOOST_CHECK(animSpriteWithAnim->getCurrentAnimationId() == 0);

	//ensure that the texture is correctly set
	BOOST_CHECK(animSpriteWithAnim->getTexture() == aSpriteTexture);

	//ensure that the animation has been successfully bound
	animSpriteWithAnim->runAnimation(0);
	//fake sleep
	sf::Time timeAfterDelay = sf::milliseconds(3);
	animSpriteWithAnim->update(timeAfterDelay);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
}

BOOST_AUTO_TEST_SUITE_END() //end AnimatedSprite_ctrs

//Contains all of the tests relating to AnimatedSprite's animations
BOOST_AUTO_TEST_SUITE(AnimatedSprite_Animations)

//test starting an animation with AnimatedSprite::RunAnimation
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Start_Animation, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);

	//running an animation must set the sprite to animating
	BOOST_CHECK(animSpriteWithAnim->isAnimating());

	//ensure that the selected animation is the one that is run
	BOOST_CHECK(animSpriteWithAnim->getCurrentAnimationId() == 0);

	//ensure that running the animation starts the animation at the first frame
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
}

//Check to see if AnimatedSprite can successfully change frames when animating
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Next_Frame, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(2);
	//fake sleep for 1ms longer than the min delay
	sf::Time timeAfterDelay = sf::milliseconds(3);
	animSpriteWithAnim->update(timeAfterDelay);

	//The minimum time has elapsed. Ensure the animated sprite is at its second frame.
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
}

//Check that AnimatedSprite does not change frames before the minimum time has elapsed
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Next_Frame_Not_Enough_Time, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(2);
	//fake sleep for 1ms shorter than the min delay
	sf::Time timeAfterDelay = sf::milliseconds(1);
	animSpriteWithAnim->update(timeAfterDelay);

	//The minimum time before changing frames has not elapsed. Ensure the frame has not changed
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
}

//Tests that AnimatedSprite loops its animations
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Loop_After_End, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(1);

	//update the sprite one frame farther than the length of the animation
	for (int i = 0; i < animSet->getAnimations()->at(0).size() + 1; i++)
	{
		//fake sleep for 1ms longer than the min delay
		sf::Time timeAfterDelay = sf::milliseconds(2 * i);
		animSpriteWithAnim->update(timeAfterDelay);
	}

	//ensure that the animation has looped
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
}

//Test running an empty animation
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Start_Empty_Animation, ReusableObjects) {
	std::vector<unsigned int> singleFrameAnim = {0};
	std::vector<unsigned int> emptyAnim;
	std::vector<std::vector<unsigned int>> animVector = {singleFrameAnim, emptyAnim};
	AnimationSet animSetEmptyAnim(animVector, 1, 1, 1, 1);
	AnimatedSprite emptyAnimSprite(*aSpriteTexture, &animSetEmptyAnim);

	//ensure that an empty animation can be ran
	BOOST_CHECK_THROW(emptyAnimSprite.runAnimation(1), AnimatedSprite_EmptyAnimation);
}

//Ensures that animations set with setAnimations can be successfully run
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setAnimations, ReusableObjects) {
	AnimatedSprite* animSprite = new AnimatedSprite(*aSpriteTexture);

	animSprite->setAnimations(animSet);
	animSprite->runAnimation(0);
	animSprite->setAnimationDelay(2);
	//fake sleep for 1ms longer than the min delay
	sf::Time timeAfterDelay = sf::milliseconds(3);
	animSprite->update(timeAfterDelay);

	//This animation has been set with SetAnimations and run.
	//Ensure that the frame has changed after the minimum time has passed 
	BOOST_CHECK(animSprite->getCurrentFrame() == 1);

	delete animSprite;
}

//ensure that the minimum animation delay is stored correctly
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setAnimationDelay, ReusableObjects) {
	animSpriteWithAnim->setAnimationDelay(1);
	BOOST_CHECK_EQUAL(animSpriteWithAnim->getAnimationDelay(), 1);
}

//ensure that the current frame of an animation can be set and retrieved correctly
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setCurrentFrame, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setCurrentFrame(3);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 3);
}


BOOST_AUTO_TEST_SUITE_END() //end AnimatedSprite_Animations

//Keep at end of file
BOOST_AUTO_TEST_SUITE_END()