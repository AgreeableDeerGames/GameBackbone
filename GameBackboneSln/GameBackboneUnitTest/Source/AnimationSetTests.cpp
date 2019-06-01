#include "stdafx.h"

#include <GameBackbone/Core/AnimationSet.h>

#include <SFML/System/Vector2.hpp>

#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(AnimationSetTests)

struct ReusableObjects {

	ReusableObjects() :
		frame1(0, 0, 1, 1),
		frame2(0, 1, 1, 1),
		frame3(1, 1, 2, 2),
		anim1({frame1, frame2, frame3}),
		anim2({frame2, frame1}) {
	}

	sf::IntRect frame1;
	sf::IntRect frame2;
	sf::IntRect frame3;
	Animation anim1;
	Animation anim2;
};


// Ensure that a default constructed animation set is empty
BOOST_AUTO_TEST_CASE(AnimationSet_default_constructor)
{
    AnimationSet animSet;
    BOOST_CHECK(animSet.isEmpty());
}

// Ensure that a animation set constructed with an empty vector is empty
BOOST_AUTO_TEST_CASE(AnimationSet_empty_vector_constructor)
{
    AnimationSet animSet(std::vector<Animation>{});
    BOOST_CHECK(animSet.isEmpty());
}

// Ensure that a animation set constructed with an full vector has the right number of animations
BOOST_AUTO_TEST_CASE(AnimationSet_full_vector_constructor)
{
    AnimationSet animSet(std::vector{Animation{}, Animation{}});
    BOOST_CHECK(!animSet.isEmpty());
	BOOST_CHECK(animSet.getSize() == 2);
}

// Ensure that a animation set constructed with an full vector has the right number of animations
BOOST_FIXTURE_TEST_CASE(AnimationSet_full_vector_constructor_correct_frames, ReusableObjects)
{
	AnimationSet animSet({anim1, anim2});
	BOOST_CHECK(animSet[0].size() == anim1.size());
	BOOST_CHECK(animSet[0][0] == frame1);
	BOOST_CHECK(animSet[0][1] == frame2);
	BOOST_CHECK(animSet[0][2] == frame3);
	BOOST_CHECK(animSet[1].size() == anim2.size());
	BOOST_CHECK(animSet[1][0] == frame2);
	BOOST_CHECK(animSet[1][1] == frame1);
}

// Ensure that [] gets the right animation
BOOST_FIXTURE_TEST_CASE(AnimationSet_operator_square_bracket_returns_correct_animation, ReusableObjects)
{
	AnimationSet animSet({anim1, anim2});
	BOOST_CHECK(animSet[0].size() == anim1.size());
	BOOST_CHECK(animSet[0][0] == frame1);
	BOOST_CHECK(animSet[0][1] == frame2);
	BOOST_CHECK(animSet[0][2] == frame3);
	BOOST_CHECK(animSet[1].size() == anim2.size());
	BOOST_CHECK(animSet[1][0] == frame2);
	BOOST_CHECK(animSet[1][1] == frame1);
}

// Ensure that at gets the right animation

// Ensure that at throws if out of bound 

// Ensure that eraseAnimation remove correct animation

// Ensure that eraseAnimations remove correct animations

// Ensure that clear animations removes all animations

// Ensure that iterators are usable with std algorithms



BOOST_AUTO_TEST_SUITE_END()// End AnimationSetTests
