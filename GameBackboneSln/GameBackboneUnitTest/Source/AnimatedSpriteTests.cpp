#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>
#include <string>
#include <thread>

using namespace GB;

// Contains all of the tests for AnimatedSprite
BOOST_AUTO_TEST_SUITE(AnimatedSpriteTests)

/// <summary>
/// Struct to store objects that can be reused for all or nearly all
/// of the unit tests in this file. This struct is meant to be used with fixtures
/// at the unit test level.
/// </summary>
struct ReusableObjects
{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "Textures/testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		//create animation set
		int halfTextureWidth = aSpriteTexture->getSize().x / 2;
		int halfTextureHeight = aSpriteTexture->getSize().y / 2;

		// Create the frames of the animation and store them for later
		animSpriteAnimTextureFrameRects = {
			sf::IntRect(0, 0, halfTextureWidth, halfTextureHeight),
			sf::IntRect(halfTextureWidth, 0, halfTextureWidth, halfTextureHeight),
			sf::IntRect(halfTextureWidth, halfTextureHeight, halfTextureWidth, halfTextureHeight),
			sf::IntRect(0, halfTextureHeight, halfTextureWidth, halfTextureHeight)
		};

		// Create an animation set from the frames
		animSet = std::make_shared<AnimationSet>();
		animSet->addAnimation ({
			animSpriteAnimTextureFrameRects[0],
			animSpriteAnimTextureFrameRects[1],
			animSpriteAnimTextureFrameRects[2],
			animSpriteAnimTextureFrameRects[3]
		});

		//create animatedSprite
		animSpriteWithAnim = new AnimatedSprite(*aSpriteTexture, animSet);
	}

	~ReusableObjects() {

		delete animSpriteWithAnim;
		delete aSpriteTexture;
	}

	AnimatedSprite* animSpriteWithAnim;
	AnimationSet::Ptr animSet;
	sf::Texture* aSpriteTexture;
	std::array<sf::IntRect, 4> animSpriteAnimTextureFrameRects;
};

// Contains all of the tests for AnimatedSprite constructors
BOOST_AUTO_TEST_SUITE(AnimatedSprite_CTRs)

// Tests the AnimatedSprite default constructor
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_default_CTR, ReusableObjects) {
	AnimatedSprite* animSprite = new AnimatedSprite();

	//ensure that everything is set to null or 0
	BOOST_CHECK(!animSprite->isAnimating());
	BOOST_CHECK(animSprite->getCurrentFrame() == 0);
	BOOST_CHECK(animSprite->getAnimationDelay().asMicroseconds() == 0);
	BOOST_CHECK(animSprite->getCurrentAnimationId() == 0);
	BOOST_CHECK(animSprite->getFramesSpentInCurrentAnimation() == 0);

	delete animSprite;
}

// Tests the AnimatedSprite constructor that takes in a texture
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Texture_CTR, ReusableObjects) {
	AnimatedSprite* animSprite = new AnimatedSprite(*aSpriteTexture);

	//ensure that everything is set to null or 0
	BOOST_CHECK(!animSprite->isAnimating());
	BOOST_CHECK(animSprite->getCurrentFrame() == 0);
	BOOST_CHECK(animSprite->getAnimationDelay().asMicroseconds() == 0);
	BOOST_CHECK(animSprite->getCurrentAnimationId() == 0);
	BOOST_CHECK(animSprite->getFramesSpentInCurrentAnimation() == 0);

	//ensure that the texture is correctly set
	BOOST_CHECK(animSprite->getTexture() == aSpriteTexture);

	delete animSprite;
}

// Tests the AnimatedSprite constructor that takes a texture and an AnimationSet
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Texture_and_Animations, ReusableObjects) {

	//ensure that everything is set to null or 0
	BOOST_CHECK(!animSpriteWithAnim->isAnimating());
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	BOOST_CHECK(animSpriteWithAnim->getAnimationDelay().asMicroseconds() == 0);
	BOOST_CHECK(animSpriteWithAnim->getCurrentAnimationId() == 0);
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == 0);

	//ensure that the texture is correctly set
	BOOST_CHECK(animSpriteWithAnim->getTexture() == aSpriteTexture);

	//ensure that the animation has been successfully bound
	animSpriteWithAnim->runAnimation(0);
	//fake sleep
	animSpriteWithAnim->update(3);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == 1);
}

// Tests the AnimatedSprite constructor that fits the sprite to its frames
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Texture_and_Animations_and_ShouldFitToFrame, ReusableObjects) {
	// build AnimatedSprite with irregular animation
	auto irregularAnimationSet = std::make_shared<AnimationSet>(std::vector<Animation>{Animation{sf::IntRect(0, 0, 1, 1), sf::IntRect(0, 0, 2, 2)}});
	AnimatedSprite animSpriteUpdateWithFrames(*aSpriteTexture, irregularAnimationSet);

	// check that the animated sprite will update its size on initialization
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().width == 1);
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().height == 1);

	// check that the animated sprite will update its size after being updated
	animSpriteUpdateWithFrames.runAnimation(0);
	animSpriteUpdateWithFrames.setAnimationDelay(sf::microseconds(2));
	animSpriteUpdateWithFrames.update(3);
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().width == 2);
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().height == 2);
}

BOOST_AUTO_TEST_SUITE_END() // end AnimatedSprite_CTRs

// Contains all of the tests relating to AnimatedSprite's animations
BOOST_AUTO_TEST_SUITE(AnimatedSprite_Animations)

// test starting an animation with AnimatedSprite::RunAnimation
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Start_Animation, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);

	//running an animation must set the sprite to animating
	BOOST_CHECK(animSpriteWithAnim->isAnimating());

	//ensure that the selected animation is the one that is run
	BOOST_CHECK(animSpriteWithAnim->getCurrentAnimationId() == 0);

	//ensure that running the animation starts the animation at the first frame
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == 0);
}

// Check to see if AnimatedSprite can successfully change frames when animating
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Next_Frame, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(2));
	//fake sleep for 1us longer than the min delay
	animSpriteWithAnim->update(3);

	//The minimum time has elapsed. Ensure the animated sprite is at its second frame.
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == 1);
}

// Check that AnimatedSprite does not change frames before the minimum time has elapsed
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Next_Frame_Not_Enough_Time, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(2));
	// fake sleep for 1us shorter than the min delay
	animSpriteWithAnim->update(1);

	// The minimum time before changing frames has not elapsed. Ensure the frame has not changed
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == 0);
}

// Check that AnimatedSprite changes frames when the elapsed time builds up
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Next_Frame_Buildup, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(10));

	const int LOOP_LENGTH = 10;
	for (int i = 0; i < LOOP_LENGTH; ++i)
	{
		// fake sleep for 1us and then check that the current frame hasn't changed
		animSpriteWithAnim->update(1);
		BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	}
	// fake sleep for 1 more microsecond in order to push the animation just over the edge and transition
	animSpriteWithAnim->update(1);

	// The minimum time before changing frames has not elapsed. Ensure the frame changed
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
}

// Tests that AnimatedSprite loops its animations by default
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Loop_After_End_Default, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(1));

	// update the sprite one frame farther than the length of the animation
	for (int i = 0; i < animSet->at(0).size() + 1; i++)
	{
		// fake sleep for 1ms longer than the min delay
		animSpriteWithAnim->update(2 * i);
	}

	// ensure that the animation has looped
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == animSet->at(0).size());
}

// Test constructing an AnimatedSprite with an empty animation
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Construct_Empty_Animation, ReusableObjects) {

	// create an animation set with two empty animations
	AnimationSet::Ptr animSetEmptyAnim = std::make_shared<AnimationSet>();
	animSetEmptyAnim->addAnimation({});
	animSetEmptyAnim->addAnimation({});

	// ensure that an empty animation can be ran
	BOOST_CHECK_THROW(AnimatedSprite(*aSpriteTexture, animSetEmptyAnim), std::out_of_range);
}

// Test running an empty animation
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Start_Empty_Animation, ReusableObjects) {

	// create an animation set with two empty animations
	AnimationSet::Ptr animSetEmptyAnim = std::make_shared<AnimationSet>();
	animSetEmptyAnim->addAnimation({sf::IntRect()});
	AnimatedSprite emptyAnimSprite(*aSpriteTexture, animSetEmptyAnim);
	animSetEmptyAnim->clearAnimations();

	// ensure that an empty animation can be ran
	BOOST_CHECK_THROW(emptyAnimSprite.runAnimation(1), std::out_of_range);
}

// Test running an animation with one frame
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Run_Animation_Single_Frame_Loop_After_End, ReusableObjects) {
	AnimationSet::Ptr animSetSingleFrameAnim = std::make_shared<AnimationSet>();
	animSetSingleFrameAnim->addAnimation({sf::IntRect()});
	AnimatedSprite singleFrameAnimSprite(*aSpriteTexture, animSetSingleFrameAnim);

	singleFrameAnimSprite.setAnimationDelay(sf::microseconds(1));

	// Play the animation
	singleFrameAnimSprite.runAnimation(0, GB::ANIMATION_LOOP);
	const int LOOP_LENGTH = 100;
	for (int i = 0; i < LOOP_LENGTH; ++i)
	{
		// fake sleep for 1us longer than the min delay
		singleFrameAnimSprite.update(2 * i);

		// ensure that the frame is always 0
		BOOST_CHECK(singleFrameAnimSprite.getCurrentFrame() == 0);
		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(singleFrameAnimSprite.getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the frame is always 0
	BOOST_CHECK(singleFrameAnimSprite.getCurrentFrame() == 0);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(singleFrameAnimSprite.getFramesSpentInCurrentAnimation() == LOOP_LENGTH - 1);
}

// Test running an animation with one frame and reversing directions
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Run_Animation_Single_Frame_Reverse_After_End, ReusableObjects) {
	AnimationSet::Ptr animSetSingleFrameAnim = std::make_shared<AnimationSet>();
	animSetSingleFrameAnim->addAnimation({sf::IntRect()});
	animSetSingleFrameAnim->addAnimation({sf::IntRect()});
	AnimatedSprite singleFrameAnimSprite(*aSpriteTexture, animSetSingleFrameAnim);

	singleFrameAnimSprite.setAnimationDelay(sf::microseconds(1));

	// Play the animation
	singleFrameAnimSprite.runAnimation(0, GB::ANIMATION_REVERSE);
	const int LOOP_LENGTH = 100;
	for (int i = 0; i < LOOP_LENGTH; ++i)
	{
		// fake sleep for 1us longer than the min delay
		singleFrameAnimSprite.update(2 * i);

		// ensure that the frame is always 0
		BOOST_CHECK(singleFrameAnimSprite.getCurrentFrame() == 0);
		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(singleFrameAnimSprite.getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the frame is always 0
	BOOST_CHECK(singleFrameAnimSprite.getCurrentFrame() == 0);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(singleFrameAnimSprite.getFramesSpentInCurrentAnimation() == LOOP_LENGTH - 1);
}

// Test running an animation with one frame and stopping
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Run_Animation_Single_Frame_Stop_After_End, ReusableObjects) {
	AnimationSet::Ptr animSetSingleFrameAnim = std::make_shared<AnimationSet>();
	animSetSingleFrameAnim->addAnimation({sf::IntRect()});
	animSetSingleFrameAnim->addAnimation({sf::IntRect()});
	AnimatedSprite singleFrameAnimSprite(*aSpriteTexture, animSetSingleFrameAnim);

	singleFrameAnimSprite.setAnimationDelay(sf::microseconds(1));

	// Play the animation
	singleFrameAnimSprite.runAnimation(0, GB::ANIMATION_STOP);
	const int LOOP_LENGTH = 100;
	for (int i = 0; i < LOOP_LENGTH; ++i)
	{
		// fake sleep for 1us longer than the min delay
		singleFrameAnimSprite.update(2 * i);
		// ensure that the frame is always 0
		BOOST_CHECK(singleFrameAnimSprite.getCurrentFrame() == 0);
		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(singleFrameAnimSprite.getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the frame is always 0
	BOOST_CHECK(singleFrameAnimSprite.getCurrentFrame() == 0);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(singleFrameAnimSprite.getFramesSpentInCurrentAnimation() == LOOP_LENGTH - 1);
}

// Tests AnimatedSprite looping its animations
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Loop_After_End, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0, ANIMATION_LOOP);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(1));

	// update the sprite one frame farther than the length of the animation
	for (int i = 0; i < animSet->at(0).size() + 1; i++)
	{
		//fake sleep for 1us longer than the min delay
		animSpriteWithAnim->update(2 * i);

		// ensure that the frame increments with each loop
		BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == i % animSet->at(0).size());
		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the animation has looped
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 0);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == animSet->at(0).size());
}

// Tests AnimatedSprite reversing its animations
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Reverse_After_End, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0, ANIMATION_REVERSE);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(1));

	// update the sprite one frame farther than the length of the animation
	for (int i = 0; i < animSet->at(0).size() + 1; i++)
	{
		// fake sleep for 1us longer than the min delay
		animSpriteWithAnim->update(2 * i);

		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the animation has looped
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 2);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == animSet->at(0).size());
}

// Tests AnimatedSprite reversing its animations
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Reverse_After_Begin, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0, ANIMATION_REVERSE);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(1));

	// update the sprite one frame farther than the length of the animation
	for (int i = 0; i < animSet->at(0).size()*2; i++)
	{
		// fake sleep for 1us longer than the min delay
		animSpriteWithAnim->update(2 * i);

		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the animation has looped
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
	// ensure the framesSpentInCurrentAnimation increment up
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == animSet->at(0).size() * 2 - 1);
}

// Tests AnimatedSprite stopping its animations
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_Animation_Stop_After_End, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0, ANIMATION_STOP);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(1));

	// update the sprite one frame farther than the length of the animation
	for (int i = 0; i < animSet->at(0).size() + 1; i++)
	{
		// fake sleep for 1us longer than the min delay
		animSpriteWithAnim->update(2 * i);

		// ensure the framesSpentInCurrentAnimation increment up
		BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == i);
	}

	// ensure that the animation has looped
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == animSet->at(0).size() - 1);
	// ensure the framesSpentInCurrentAnimation are correct and were not reset
	BOOST_CHECK(animSpriteWithAnim->getFramesSpentInCurrentAnimation() == animSet->at(0).size());
}

// Ensures that animations set with setAnimations can be successfully run
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setAnimations, ReusableObjects) {
	AnimatedSprite* animSprite = new AnimatedSprite(*aSpriteTexture);

	animSprite->setAnimations(animSet);
	animSprite->runAnimation(0);
	animSprite->setAnimationDelay(sf::microseconds(2));
	// fake sleep for 1us longer than the min delay
	animSprite->update(3);

	// This animation has been set with SetAnimations and run.
	// Ensure that the frame has changed after the minimum time has passed
	BOOST_CHECK(animSprite->getCurrentFrame() == 1);
	// ensure the framesSpentInCurrentAnimation are correct
	BOOST_CHECK(animSprite->getFramesSpentInCurrentAnimation() == 1);

	delete animSprite;
}

// Ensures that animations set with setAnimations can be successfully run and that it can update the size of the sprite
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setAnimations_fit_to_frame, ReusableObjects) {
	AnimatedSprite animSpriteUpdateWithFrames = AnimatedSprite(*aSpriteTexture);

	// build AnimatedSprite with irregular animation
	auto irregularAnimationSet = std::make_shared<AnimationSet>(std::vector<Animation>{Animation{sf::IntRect(0, 0, 1, 1), sf::IntRect(0, 0, 2, 2)}});

	// set the animation on the sprite
	animSpriteUpdateWithFrames.setAnimations(irregularAnimationSet);

	// check that the animated sprite will update its size on initialization
	BOOST_CHECK_EQUAL(animSpriteUpdateWithFrames.getLocalBounds().width, 1.0f);
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().height == 1);

	// check that the animated sprite will update its size after being updated
	animSpriteUpdateWithFrames.runAnimation(0);
	animSpriteUpdateWithFrames.setAnimationDelay(sf::microseconds(2));
	animSpriteUpdateWithFrames.update(3);
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().width == 2);
	BOOST_CHECK(animSpriteUpdateWithFrames.getLocalBounds().height == 2);
}

// ensure that the minimum animation delay is stored correctly
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setAnimationDelay, ReusableObjects) {
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(1));
	BOOST_CHECK_EQUAL(animSpriteWithAnim->getAnimationDelay().asMicroseconds(), 1);
}

// ensure that the current frame of an animation can be set and retrieved correctly
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_setCurrentFrame, ReusableObjects) {
	const int newFrame = 3;
	animSpriteWithAnim->runAnimation(0);
	animSpriteWithAnim->setCurrentFrame(newFrame);
	// Ensure that the animation frame member of the animated sprite and the texture being displayed by the
	// sprite have both been updated
	BOOST_CHECK(animSpriteWithAnim->getTextureRect() == animSpriteAnimTextureFrameRects[newFrame]);
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == newFrame);
}

// Tests AnimatedSprite reversing its animations
BOOST_FIXTURE_TEST_CASE(AnimatedSprite_multiple_updates_require_time_to_pass, ReusableObjects) {
	animSpriteWithAnim->runAnimation(0, ANIMATION_REVERSE);
	animSpriteWithAnim->setAnimationDelay(sf::microseconds(10));

	// fake sleep long enough for the next frame
	animSpriteWithAnim->update(11);

	// ensure that the animation is on frame 1
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);

	// fake sleep, but not enough for the next frame
	animSpriteWithAnim->update(5);

	// Ensure that the frame has not changed
	BOOST_CHECK(animSpriteWithAnim->getCurrentFrame() == 1);
}


BOOST_AUTO_TEST_SUITE_END() // end AnimatedSprite_Animations

// Keep at end of file
BOOST_AUTO_TEST_SUITE_END()