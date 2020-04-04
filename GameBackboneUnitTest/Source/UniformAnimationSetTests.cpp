#include "stdafx.h"

#include <GameBackbone/Core/UniformAnimationSet.h>

#include <SFML/System/Vector2.hpp>

#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(UniformAnimationSetTests)

struct ReusableObjects {

	ReusableObjects() :
		frameSize({ 32,32 }),
		uFrame1(0, 0),
		uFrame2(0, 1),
		uFrame3(1, 1),
		frame1(0, 0, 32, 32),
		frame2(0, 32, 32, 32),
		frame3(32, 32, 32, 32),
		uAnim1({ uFrame1, uFrame2, uFrame3 }),
		uAnim2({ uFrame2, uFrame1 }),
		nonUFrame1(0, 0, 64, 32),
		nonUFrame2(0, 32, 64, 32),
		nonUFrame3(32, 0, 32, 64),
		anim1({ nonUFrame1, nonUFrame2, nonUFrame3 }),
		anim2({ nonUFrame2, nonUFrame1 }) {
	}

	sf::Vector2i frameSize;
	sf::Vector2i uFrame1;
	sf::Vector2i uFrame2;
	sf::Vector2i uFrame3;
	sf::IntRect frame1;
	sf::IntRect frame2;
	sf::IntRect frame3;
	UniformAnimation uAnim1;
	UniformAnimation uAnim2;
	sf::IntRect nonUFrame1;
	sf::IntRect nonUFrame2;
	sf::IntRect nonUFrame3;
	Animation anim1;
	Animation anim2;
};


BOOST_AUTO_TEST_SUITE(UniformAnimationSet_CTR)

// Ensure that an UniformAnimationSet constructed with just a frame size, is correct and is empty
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_frame_size_constructor, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize);

	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(animSet.isEmpty());
}

// Ensure that an UniformAnimationSet constructed with an empty vector is empty
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_empty_vector_constructor, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize, std::vector<UniformAnimation>{});
	
	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(animSet.isEmpty());
}

// Ensure that an UniformAnimationSet constructed with an full vector has the right number of animations
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_full_vector_constructor, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize, std::vector<UniformAnimation>{ UniformAnimation{}, UniformAnimation{} });

	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(!animSet.isEmpty());
	BOOST_CHECK(animSet.getSize() == 2);
}

// Ensure that an UniformAnimationSet constructed with an full vector has the right number of animations
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_full_vector_constructor_correct_frames, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize, { uAnim1, uAnim2 });

	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(animSet[0].size() == uAnim1.size());
	BOOST_CHECK(animSet[0][0] == frame1);
	BOOST_CHECK(animSet[0][1] == frame2);
	BOOST_CHECK(animSet[0][2] == frame3);
	BOOST_CHECK(animSet[1].size() == uAnim2.size());
	BOOST_CHECK(animSet[1][0] == frame2);
	BOOST_CHECK(animSet[1][1] == frame1);
}

BOOST_AUTO_TEST_SUITE_END()// End UniformAnimationSet_CTR


BOOST_AUTO_TEST_SUITE(UniformAnimationSet_addAnimation)

// Ensure that an addAnimation with UniformAnimation creates the correct Animations
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_add_to_empty, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize);
	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(animSet.isEmpty());
	animSet.addAnimation(uAnim1);
	animSet.addAnimation(uAnim2);

	// Check the UniformAnimations after adding them.
	BOOST_CHECK(!animSet.isEmpty());
	BOOST_CHECK(animSet[0].size() == uAnim1.size());
	BOOST_CHECK(animSet[0][0] == frame1);
	BOOST_CHECK(animSet[0][1] == frame2);
	BOOST_CHECK(animSet[0][2] == frame3);
	BOOST_CHECK(animSet[1].size() == uAnim2.size());
	BOOST_CHECK(animSet[1][0] == frame2);
	BOOST_CHECK(animSet[1][1] == frame1);
}

// Ensure that an addAnimation can take both UniformAnimation and Animation and has correct frames
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_add_nonuniform_at_end, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize);
	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(animSet.isEmpty());

	// Add some UniformAnimations
	animSet.addAnimation(uAnim1);
	animSet.addAnimation(uAnim2);

	// Check the UniformAnimations after adding them.
	BOOST_CHECK(!animSet.isEmpty());
	BOOST_CHECK(animSet[0].size() == uAnim1.size());
	BOOST_CHECK(animSet[0][0] == frame1);
	BOOST_CHECK(animSet[0][1] == frame2);
	BOOST_CHECK(animSet[0][2] == frame3);
	BOOST_CHECK(animSet[1].size() == uAnim2.size());
	BOOST_CHECK(animSet[1][0] == frame2);
	BOOST_CHECK(animSet[1][1] == frame1);

	// Add some Animations
	animSet.addAnimation(anim1);
	animSet.addAnimation(anim2);

	// Check the original UniformAnimations' frames to ensure they are not changed.
	BOOST_CHECK(animSet[0][0] == frame1);
	BOOST_CHECK(animSet[0][1] == frame2);
	BOOST_CHECK(animSet[0][2] == frame3);
	BOOST_CHECK(animSet[1][0] == frame2);
	BOOST_CHECK(animSet[1][1] == frame1);

	// Check the newly added Animations.
	BOOST_CHECK(animSet[2].size() == anim1.size());
	BOOST_CHECK(animSet[2][0] == nonUFrame1);
	BOOST_CHECK(animSet[2][1] == nonUFrame2);
	BOOST_CHECK(animSet[2][2] == nonUFrame3);
	BOOST_CHECK(animSet[3].size() == anim2.size());
	BOOST_CHECK(animSet[3][0] == nonUFrame2);
	BOOST_CHECK(animSet[3][1] == nonUFrame1);
}

// Ensure that an addAnimation can take both UniformAnimation and Animation and has correct frames
BOOST_FIXTURE_TEST_CASE(UniformAnimationSet_add_nonuniform_in_middle, ReusableObjects)
{
	UniformAnimationSet animSet(frameSize);
	BOOST_CHECK(animSet.getDefaultFrameSize() == frameSize);
	BOOST_CHECK(animSet.isEmpty());

	// Add some Animations
	animSet.addAnimation(anim1);
	animSet.addAnimation(anim2);

	// Check the newly added Animations.
	BOOST_CHECK(animSet[0].size() == anim1.size());
	BOOST_CHECK(animSet[0][0] == nonUFrame1);
	BOOST_CHECK(animSet[0][1] == nonUFrame2);
	BOOST_CHECK(animSet[0][2] == nonUFrame3);
	BOOST_CHECK(animSet[1].size() == anim2.size());
	BOOST_CHECK(animSet[1][0] == nonUFrame2);
	BOOST_CHECK(animSet[1][1] == nonUFrame1);

	// Add some UniformAnimations
	animSet.addAnimation(uAnim1);
	animSet.addAnimation(uAnim2);

	// Check the original Animations' frames to ensure they are not changed.
	BOOST_CHECK(animSet[0].size() == anim1.size());
	BOOST_CHECK(animSet[0][0] == nonUFrame1);
	BOOST_CHECK(animSet[0][1] == nonUFrame2);
	BOOST_CHECK(animSet[0][2] == nonUFrame3);
	BOOST_CHECK(animSet[1].size() == anim2.size());
	BOOST_CHECK(animSet[1][0] == nonUFrame2);
	BOOST_CHECK(animSet[1][1] == nonUFrame1);

	// Check the UniformAnimations after adding them.
	BOOST_CHECK(animSet[2][0] == frame1);
	BOOST_CHECK(animSet[2][1] == frame2);
	BOOST_CHECK(animSet[2][2] == frame3);
	BOOST_CHECK(animSet[3][0] == frame2);
	BOOST_CHECK(animSet[3][1] == frame1);
}

BOOST_AUTO_TEST_SUITE_END()// End UniformAnimationSet_addAnimation


BOOST_AUTO_TEST_SUITE_END()// End UniformAnimationSetTests
