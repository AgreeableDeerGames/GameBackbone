#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Util/SFUtil.h>

#include <SFML/Graphics/Sprite.hpp>

#include <type_traits>

using namespace GB;

// Contains all of the tests for SFUtilTests
BOOST_AUTO_TEST_SUITE(SFUtilTests)

// Contains all of the tests for toDrawableVectorTests
BOOST_AUTO_TEST_SUITE(toDrawableVectorTests)

BOOST_AUTO_TEST_CASE(toDrawableVector_Sprite) {
	std::vector<sf::Sprite> spriteList;
	spriteList.emplace_back(sf::Sprite{});

	std::vector<sf::Drawable*> returnVector = toDrawableVector(spriteList);

	BOOST_CHECK_EQUAL(returnVector.size(), spriteList.size());
	for (size_t ii = 0; ii < spriteList.size(); ii++)
	{
		BOOST_CHECK_EQUAL(returnVector.at(ii), &spriteList.at(ii));
	}
}

BOOST_AUTO_TEST_CASE(toDrawableVector_AnimatedSprite) {
	std::vector<AnimatedSprite> spriteList;
	spriteList.emplace_back(AnimatedSprite{});

	std::vector<sf::Drawable*> returnVector = toDrawableVector(spriteList);

	BOOST_CHECK_EQUAL(returnVector.size(), spriteList.size());
	for (size_t ii = 0; ii < spriteList.size(); ii++)
	{
		BOOST_CHECK_EQUAL(returnVector.at(ii), &spriteList.at(ii));
	}
}

BOOST_AUTO_TEST_CASE(toDrawableVector_SpritePointer) {
	sf::Sprite sprite;
	std::vector<sf::Sprite*> spriteList;
	spriteList.emplace_back(&sprite);

	std::vector<sf::Drawable*> returnVector = toDrawableVector(spriteList);

	BOOST_CHECK_EQUAL(returnVector.size(), spriteList.size());
	for (size_t ii = 0; ii < spriteList.size(); ii++)
	{
		BOOST_CHECK_EQUAL(returnVector.at(ii), spriteList.at(ii));
	}
}

BOOST_AUTO_TEST_CASE(toDrawableVector_AnimatedSpritePointer) {
	AnimatedSprite sprite;
	std::vector<AnimatedSprite*> spriteList;
	spriteList.emplace_back(&sprite);

	std::vector<sf::Drawable*> returnVector = toDrawableVector(spriteList);

	BOOST_CHECK_EQUAL(returnVector.size(), spriteList.size());
	for (size_t ii = 0; ii < spriteList.size(); ii++)
	{
		BOOST_CHECK_EQUAL(returnVector.at(ii), spriteList.at(ii));
	}
}

BOOST_AUTO_TEST_CASE(IteratorAdapter_Constructor)
{
	std::vector<sf::Sprite> sprites;
	// IteratorAdapter<decltype(sprites.begin()), sf::Drawable*, std::function<sf::Drawable*&(const decltype(sprites.begin())&)>> adapter(sprites.begin());
	// IteratorAdapter adaptor(sprites.begin(), [](const decltype(sprites.begin())& it) {return (sf::Drawable*) & (*it); });
}

/*
 * SFINAE types for checking if toDrawableVector can be 
 * called on a specific type
 */

template <class, class = std::void_t<> >
struct CanConvertToDrawableVector : std::false_type {};

template <class Iterator>
struct CanConvertToDrawableVector <
	Iterator,
	std::void_t<
		decltype(toDrawableVector(std::declval<Iterator>()))
	> 
> : std::true_type {};

template <class Iterator>
inline constexpr bool CanConvertToDrawableVector_v = CanConvertToDrawableVector<Iterator>::value;

BOOST_AUTO_TEST_CASE(toDrawableVector_CanCompileSpriteVector)
{
	BOOST_CHECK(CanConvertToDrawableVector_v<std::vector<sf::Sprite>>);
}

BOOST_AUTO_TEST_CASE(toDrawableVector_CanCompileSpritePointerVector)
{
	BOOST_CHECK(CanConvertToDrawableVector_v<std::vector<sf::Sprite*>>);
}

BOOST_AUTO_TEST_CASE(toDrawableVector_CannotCompileConstSpritePointerVector)
{
	BOOST_CHECK(!CanConvertToDrawableVector_v<std::vector<const sf::Sprite*>>);
}

BOOST_AUTO_TEST_CASE(toDrawableVector_CannotCompileTransformableVector)
{
	BOOST_CHECK(!CanConvertToDrawableVector_v<std::vector<sf::Transformable>>);
}

BOOST_AUTO_TEST_CASE(toDrawableVector_CannotCompileTransformablePointerVector)
{
	BOOST_CHECK(!CanConvertToDrawableVector_v<std::vector<sf::Transformable*>>);
}

BOOST_AUTO_TEST_SUITE_END() // end toDrawableVectorTests

// Keep at end of file
BOOST_AUTO_TEST_SUITE_END()