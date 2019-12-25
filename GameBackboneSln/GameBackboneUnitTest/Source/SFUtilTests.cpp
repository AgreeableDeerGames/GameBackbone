#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Util/SFUtil.h>
#include <GameBackbone/Util/TransformIterator.h>

#include <SFML/Graphics/Sprite.hpp>

#include <type_traits>

using namespace GB;

// Contains all of the tests for SFUtilTests
BOOST_AUTO_TEST_SUITE(SFUtilTests)

// Contains all of the tests for toDrawableVectorTests
BOOST_AUTO_TEST_SUITE(toDrawableVectorTests)

BOOST_AUTO_TEST_CASE(IteratorAdapter_Constructor)
{
	std::vector<sf::Sprite> sprites(20, sf::Sprite{});
	auto lambda = [](const auto& input) -> sf::Drawable* { return (sf::Drawable*) & (*input); };

	TransformIterator adapter
	(
		sprites.begin(),
		lambda
	);

	bool eqCmp = adapter == sprites.end();
	bool neqCmp = adapter != sprites.end();

	TransformIterator incrementTransformIt
	(
		sprites.begin(),
		lambda
	);
	++incrementTransformIt;
	incrementTransformIt++;

	TransformIterator decrementTransformIt
	(
		sprites.begin() + 5,
		lambda
	);
	--decrementTransformIt;
	decrementTransformIt--;

	TransformIterator randomAccessTransformIt
	(
		sprites.begin() + 5,
		lambda
	);
	randomAccessTransformIt += 4;
	randomAccessTransformIt -= 4;
	randomAccessTransformIt + 4;
	randomAccessTransformIt - 4;
	randomAccessTransformIt - 4;
	randomAccessTransformIt[4];
	4 + randomAccessTransformIt;


	sf::Drawable* output = *adapter;
	decltype(sprites.begin()) origTypeIterator = (decltype(sprites.begin()))adapter;

	bool compareTwoAdapters = adapter == randomAccessTransformIt;
	bool compareAdapterWithOrig = adapter == sprites.begin();
	bool falseCompareAdapterWithOrig = adapter != sprites.begin();

	constexpr bool value = std::is_same_v<std::random_access_iterator_tag, std::iterator_traits<decltype(decrementTransformIt)::WrappedIteratorType>::iterator_category >;
	int val = 0;

}

/*
 * SFINAE types for checking if toDrawableVector can be 
 * called on a specific type
 */

//template <class, class = std::void_t<> >
//struct CanConvertToDrawableVector : std::false_type {};
//
//template <class Iterator>
//struct CanConvertToDrawableVector <
//	Iterator,
//	std::void_t<
//		decltype(toDrawableVector(std::declval<Iterator>()))
//	> 
//> : std::true_type {};
//
//template <class Iterator>
//inline constexpr bool CanConvertToDrawableVector_v = CanConvertToDrawableVector<Iterator>::value;
//
//BOOST_AUTO_TEST_CASE(toDrawableVector_CanCompileSpriteVector)
//{
//	BOOST_CHECK(CanConvertToDrawableVector_v<std::vector<sf::Sprite>>);
//}
//
//BOOST_AUTO_TEST_CASE(toDrawableVector_CanCompileSpritePointerVector)
//{
//	BOOST_CHECK(CanConvertToDrawableVector_v<std::vector<sf::Sprite*>>);
//}
//
//BOOST_AUTO_TEST_CASE(toDrawableVector_CannotCompileConstSpritePointerVector)
//{
//	BOOST_CHECK(!CanConvertToDrawableVector_v<std::vector<const sf::Sprite*>>);
//}
//
//BOOST_AUTO_TEST_CASE(toDrawableVector_CannotCompileTransformableVector)
//{
//	BOOST_CHECK(!CanConvertToDrawableVector_v<std::vector<sf::Transformable>>);
//}
//
//BOOST_AUTO_TEST_CASE(toDrawableVector_CannotCompileTransformablePointerVector)
//{
//	BOOST_CHECK(!CanConvertToDrawableVector_v<std::vector<sf::Transformable*>>);
//}

BOOST_AUTO_TEST_SUITE_END() // end toDrawableVectorTests

// Keep at end of file
BOOST_AUTO_TEST_SUITE_END()