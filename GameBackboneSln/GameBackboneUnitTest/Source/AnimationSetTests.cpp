#include "stdafx.h"

#include <GameBackbone/Core/AnimationSet.h>

#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(AnimationSetTests)

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

BOOST_AUTO_TEST_SUITE_END()// End AnimationSetTests
