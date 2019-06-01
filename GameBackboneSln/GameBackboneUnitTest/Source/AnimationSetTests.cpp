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
		anim2({frame2, frame1}),
		fixtureAnimSet({anim1, anim2}) {
		
	}

	sf::IntRect frame1;
	sf::IntRect frame2;
	sf::IntRect frame3;
	Animation anim1;
	Animation anim2;
	AnimationSet fixtureAnimSet;
};

BOOST_AUTO_TEST_SUITE(AnimationSet_constructors)

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

BOOST_AUTO_TEST_SUITE_END() // AnimationSet_constructors

BOOST_AUTO_TEST_SUITE(AnimationSet_getters)

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
BOOST_FIXTURE_TEST_CASE(AnimationSet_at_returns_correct_animation, ReusableObjects)
{
	AnimationSet animSet({anim1, anim2});
	BOOST_CHECK(animSet.at(0).size() == anim1.size());
	BOOST_CHECK(animSet.at(0)[0] == frame1);
	BOOST_CHECK(animSet.at(0)[1] == frame2);
	BOOST_CHECK(animSet.at(0)[2] == frame3);
	BOOST_CHECK(animSet.at(1).size() == anim2.size());
	BOOST_CHECK(animSet.at(1)[0] == frame2);
	BOOST_CHECK(animSet.at(1)[1] == frame1);
}

// Ensure that at throws if out of bound 
BOOST_FIXTURE_TEST_CASE(AnimationSet_at_throws_when_out_of_bounds, ReusableObjects)
{
	AnimationSet animSet({anim1, anim2});
	BOOST_CHECK_THROW(animSet.at(99).size(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END() // AnimationSet_getters

BOOST_AUTO_TEST_SUITE(AnimationSet_additions)

// Ensure that an AnimationSet can correctly add animations
BOOST_FIXTURE_TEST_CASE(AnimationSet_add_to_empty, ReusableObjects)
{
    AnimationSet animSet;
	// anim sets start as empty
    BOOST_CHECK(animSet.isEmpty());

	// animation set adds a single animation
    animSet.addAnimation(anim1);
    BOOST_CHECK(animSet[0].size() == anim1.size());
    BOOST_CHECK(animSet[0][0] == frame1);
    BOOST_CHECK(animSet[0][1] == frame2);
    BOOST_CHECK(animSet[0][2] == frame3);
    BOOST_CHECK(!animSet.isEmpty());
    BOOST_CHECK(animSet.getSize() == 1);

	// animation adds another animation and still has all of its data
    animSet.addAnimation(anim2);
    BOOST_CHECK(animSet[0].size() == anim1.size());
    BOOST_CHECK(animSet[0][0] == frame1);
    BOOST_CHECK(animSet[0][1] == frame2);
    BOOST_CHECK(animSet[0][2] == frame3);
    BOOST_CHECK(animSet[1].size() == anim2.size());
    BOOST_CHECK(animSet[1][0] == frame2);
    BOOST_CHECK(animSet[1][1] == frame1);
    BOOST_CHECK(animSet.getSize() == 2);
}

BOOST_AUTO_TEST_SUITE_END() // AnimationSet_additions

BOOST_AUTO_TEST_SUITE(AnimationSet_removals)

// Ensure that eraseAnimation remove correct animation
BOOST_FIXTURE_TEST_CASE(AnimationSet_erase_remove_animation, ReusableObjects)
{
	fixtureAnimSet.eraseAnimation(fixtureAnimSet.begin());
	// make sure the remaining animation was the second one
	BOOST_CHECK(fixtureAnimSet[0][0] == frame2);
	BOOST_CHECK(fixtureAnimSet.getSize() == 1);
}

// Ensure that eraseAnimations remove correct animations
BOOST_FIXTURE_TEST_CASE(AnimationSet_erase_remove_multiple_animations, ReusableObjects)
{
	fixtureAnimSet.addAnimation({frame3, frame2, frame1});
	fixtureAnimSet.eraseAnimations(fixtureAnimSet.begin(), fixtureAnimSet.begin() + 2);
	// make sure the remaining animation was the second one
	BOOST_CHECK(fixtureAnimSet[0][0] == frame3);
	BOOST_CHECK(fixtureAnimSet.getSize() == 1);
}

// Ensure that clear animations removes all animations
BOOST_FIXTURE_TEST_CASE(AnimationSet_clear_removes_all_animations, ReusableObjects)
{
	fixtureAnimSet.addAnimation({frame3, frame2, frame1});
	fixtureAnimSet.clearAnimations();
	BOOST_CHECK(fixtureAnimSet.isEmpty());
}

BOOST_AUTO_TEST_SUITE_END() // AnimationSet_removals

BOOST_AUTO_TEST_SUITE(AnimationSet_iterators)

// Ensure forward iterator works
BOOST_FIXTURE_TEST_CASE(AnimationSet_forward_iterator_works_with_algorithms, ReusableObjects)
{
	const AnimationSet constSet = fixtureAnimSet;
	int randomAccessPosition = 0;
	for (auto it = constSet.begin(); it != constSet.end(); ++it) {
		BOOST_CHECK(it->size() == constSet[randomAccessPosition].size());
		randomAccessPosition++;
	}
}

// Ensure forward iterator works in non const environment
BOOST_FIXTURE_TEST_CASE(AnimationSet_non_const_forward_iterator_works_with_algorithms, ReusableObjects)
{
	int randomAccessPosition = 0;
	for (auto it = fixtureAnimSet.begin(); it != fixtureAnimSet.end(); ++it) {
		BOOST_CHECK(it->size() == fixtureAnimSet[randomAccessPosition].size());
		randomAccessPosition++;
	}
}

// Ensure const forward iterator works
BOOST_FIXTURE_TEST_CASE(AnimationSet_const_forward_iterator_works_with_algorithms, ReusableObjects)
{
	const AnimationSet constSet = fixtureAnimSet;
	int randomAccessPosition = 0;
	for (auto it = constSet.cbegin(); it != constSet.cend(); ++it) {
		BOOST_CHECK(it->size() == constSet[randomAccessPosition].size());
		randomAccessPosition++;
	}
}

// Ensure reverse iterator works
BOOST_FIXTURE_TEST_CASE(AnimationSet_reverse_iterator_works_with_algorithms, ReusableObjects)
{
	const AnimationSet constSet = fixtureAnimSet;
	int randomAccessPosition = constSet.getSize() - 1;
	for (auto it = constSet.rbegin(); it != constSet.rend(); ++it) {
		BOOST_CHECK(it->size() == constSet[randomAccessPosition].size());
		randomAccessPosition--;
	}
}

// Ensure reverse iterator works in non const environment
BOOST_FIXTURE_TEST_CASE(AnimationSet_reverse_non_const_forward_iterator_works_with_algorithms, ReusableObjects)
{
	int randomAccessPosition = fixtureAnimSet.getSize() - 1;
	for (auto it = fixtureAnimSet.rbegin(); it != fixtureAnimSet.rend(); ++it) {
		BOOST_CHECK(it->size() == fixtureAnimSet[randomAccessPosition].size());
		randomAccessPosition--;
	}
}

// Ensure const reverse iterator works
BOOST_FIXTURE_TEST_CASE(AnimationSet_const_reverse_iterator_works_with_algorithms, ReusableObjects)
{
	const AnimationSet constSet = fixtureAnimSet;
	int randomAccessPosition = constSet.getSize() - 1;
	for (auto it = constSet.crbegin(); it != constSet.crend(); ++it) {
		BOOST_CHECK(it->size() == constSet[randomAccessPosition].size());
		randomAccessPosition--;
	}
}

BOOST_AUTO_TEST_SUITE_END() // AnimationSet_iterators

BOOST_AUTO_TEST_SUITE_END()// End AnimationSetTests
