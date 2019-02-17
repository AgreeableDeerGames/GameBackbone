#include "stdafx.h"

#include <GameBackbone/Core/AnimationSet.h>

#include <vector>

using namespace GB;

/// <summary>
/// Struct to store generic animations that can be used for
/// multiple test cases
/// </summary>
struct ReusableGenericAnimations {
	ReusableGenericAnimations() {
		numericAnimations->push_back(anim1);
		numericAnimations->push_back(anim2);
	}

	FrameIndexAnimation anim1 = { 0, 1, 2, 3 };
	FrameIndexAnimation anim2 = { 3, 2, 1, 0 };
	FrameIndexAnimationVectorPtr numericAnimations = std::make_shared<FrameIndexAnimationVector>();

};

// Contains all tests for AnimationSet
BOOST_AUTO_TEST_SUITE(AnimationSet_Tests)

// All the ctrs for AnimationSet
BOOST_AUTO_TEST_SUITE(AnimationSet_CTRs)


// Test the ctr for AnimationSet that includes the dimensions of the animation texture
// and the frames for each animation
BOOST_FIXTURE_TEST_CASE(AnimationSet_Texture_Size_CTR, ReusableGenericAnimations) {
	AnimationSet* animSet = new AnimationSet(numericAnimations, {100, 100}, {2, 2});

	// Ensure that animations have been produced
	BOOST_CHECK(!animSet->getAnimations()->empty());

	// Check that produced animations are logical
	auto rectAnims = animSet->getAnimations();

	sf::IntRect rect0(0, 0, 50, 50);
	sf::IntRect rect1(50, 0, 50, 50);
	sf::IntRect rect2(0, 50, 50, 50);
	sf::IntRect rect3(50, 50, 50, 50);

		// Check the first animation
	BOOST_CHECK((*rectAnims)[0][0] == rect0);
	BOOST_CHECK((*rectAnims)[0][1] == rect1);
	BOOST_CHECK((*rectAnims)[0][2] == rect2);
	BOOST_CHECK((*rectAnims)[0][3] == rect3);

		// Check the second animation
	BOOST_CHECK((*rectAnims)[1][0] == rect3);
	BOOST_CHECK((*rectAnims)[1][1] == rect2);
	BOOST_CHECK((*rectAnims)[1][2] == rect1);
	BOOST_CHECK((*rectAnims)[1][3] == rect0);

	delete animSet;
}

BOOST_AUTO_TEST_SUITE_END() // end AnimationSet_CTRs


BOOST_AUTO_TEST_SUITE(AnimationSet_Actions)

// Test that framesToRects produces the correct rectangles for a 2 by 2 sprite sheet
BOOST_FIXTURE_TEST_CASE(AnimationSet_framesToRects_2x2_test, ReusableGenericAnimations) {
	AnimationSet* animSet = new AnimationSet(numericAnimations, {100, 100}, {2, 2});

	sf::IntRect rect0(0, 0, 50, 50);
	sf::IntRect rect1(50, 0, 50, 50);
	sf::IntRect rect2(0, 50, 50, 50);
	sf::IntRect rect3(50, 50, 50, 50);

	// Check that produced animations are logical
	auto rectAnims = animSet->getAnimations();

	// Check the first animation
	BOOST_CHECK((*rectAnims)[0][0] == rect0);
	BOOST_CHECK((*rectAnims)[0][1] == rect1);
	BOOST_CHECK((*rectAnims)[0][2] == rect2);
	BOOST_CHECK((*rectAnims)[0][3] == rect3);

	// Check the second animation
	BOOST_CHECK((*rectAnims)[1][0] == rect3);
	BOOST_CHECK((*rectAnims)[1][1] == rect2);
	BOOST_CHECK((*rectAnims)[1][2] == rect1);
	BOOST_CHECK((*rectAnims)[1][3] == rect0);

	delete animSet;
}

// Test that framesToRects produces the correct rectangles for a 1 by 2 sprite sheet
BOOST_AUTO_TEST_CASE(AnimationSet_framesToRects_1x2_test) {

	FrameIndexAnimation anim1 = { 0, 1 };
	FrameIndexAnimation anim2 = { 1, 0 };
	auto numericAnimations = std::make_shared<FrameIndexAnimationVector>();
	numericAnimations->push_back(anim1);
	numericAnimations->push_back(anim2);

	AnimationSet* animSet = new AnimationSet(numericAnimations, {100, 100}, {1, 2});

	//check that produced animations are logical
	auto rectAnims = animSet->getAnimations();

	sf::IntRect rect0(0, 0, 50, 100);
	sf::IntRect rect1(50, 0, 50, 100);

	//check the first animation
	BOOST_CHECK((*rectAnims)[0][0] == rect0);
	BOOST_CHECK((*rectAnims)[0][1] == rect1);

	//check the second animation
	BOOST_CHECK((*rectAnims)[1][0] == rect1);
	BOOST_CHECK((*rectAnims)[1][1] == rect0);

	delete animSet;
}

// Test that framesToRects produces the correct rectangles for a 1 by 1 sprite sheet
BOOST_AUTO_TEST_CASE(AnimationSet_framesToRects_1x1_test) {

	FrameIndexAnimation anim1 = { 0 };
	auto numericAnimations = std::make_shared<FrameIndexAnimationVector>();
	numericAnimations->push_back(anim1);

	AnimationSet* animSet = new AnimationSet(numericAnimations, {100, 100}, {1, 1});

	//check that produced animations are logical
	auto rectAnims = animSet->getAnimations();

	sf::IntRect rect0(0, 0, 100, 100);

	//check the first animation
	BOOST_CHECK((*rectAnims)[0][0] == rect0);

	delete animSet;
}

BOOST_AUTO_TEST_SUITE_END() // end AnimationSet_actions

BOOST_AUTO_TEST_SUITE_END() // end AnimationSet_Tests