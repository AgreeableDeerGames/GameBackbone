#include "stdafx.h"

#include <Backbone/AnimatedSprite.h>
#include <Backbone/CompoundSprite.h>
#include <Backbone/RelativeRotationSprite.h>
#include <Backbone/BackboneBaseExceptions.h>

#include <SFML/Graphics.hpp>

#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(RelativeRotionSpriteTests)

struct ReusableObjects{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "../Textures/testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		sprite1 = new sf::Sprite(*aSpriteTexture);
		sprite2 = new sf::Sprite(*aSpriteTexture);
		spriteVector.push_back(sprite1);
		spriteVector.push_back(sprite2);

		sf::Vector2u textureDim = aSpriteTexture->getSize();
		std::vector<std::vector<unsigned int>> aSpriteAnims;
		std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
		aSpriteAnims.push_back(aSpriteAnim1);
		animSet1 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);
		animSet2 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

		animSpriteWithAnim1 = new AnimatedSprite(*aSpriteTexture, animSet1);
		animSpriteWithAnim2 = new AnimatedSprite(*aSpriteTexture, animSet2);
		animSpriteVector.push_back(animSpriteWithAnim1);
		animSpriteVector.push_back(animSpriteWithAnim2);

		combinedVector.push_back(sprite1);
		combinedVector.push_back(sprite2);
		combinedVector.push_back(animSpriteWithAnim1);
		combinedVector.push_back(animSpriteWithAnim2);
	}
	~ReusableObjects() {
		delete aSpriteTexture;
		delete animSet1;
		delete animSet2;
		delete animSpriteWithAnim1;
		delete animSpriteWithAnim2;
		delete sprite1;
		delete sprite2;
	}

	AnimatedSprite* animSpriteWithAnim1;
	AnimatedSprite* animSpriteWithAnim2;
	AnimationSet* animSet1;
	AnimationSet* animSet2;
	sf::Texture* aSpriteTexture;
	sf::Sprite* sprite1;
	sf::Sprite* sprite2;
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animSpriteVector;
	std::vector<sf::Sprite*> combinedVector;
	const sf::Vector2f rrSpritePos{ 3,3 };
	std::vector<sf::Vector2f> initialOffsets{ sf::Vector2f(10,0), sf::Vector2f(0,10), sf::Vector2f(10,0), sf::Vector2f(0,10) };
};

BOOST_AUTO_TEST_SUITE(RelativeRotionSprite_CTR)

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_default_CTR, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	// Ensure that the components are empty
	BOOST_CHECK(rrSprite->getComponents()->empty());
	BOOST_CHECK(rrSprite->getAnimatedSprites()->empty());

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_SingleSpriteVector_CTR, ReusableObjects) {
	sprite1->setPosition({ 10, 0 });
	sprite2->setPosition({ 0, 10 });
	animSpriteWithAnim1->setPosition({ 10, 0 });
	animSpriteWithAnim2->setPosition({ 0, 10 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(combinedVector);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_PositionOnly_CTR, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(rrSpritePos);

	// Ensure that the components are empty
	BOOST_CHECK(rrSprite->getComponents()->empty());
	BOOST_CHECK(rrSprite->getAnimatedSprites()->empty());

	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_SingleSpriteVector_Position_CTR, ReusableObjects) {

	sprite1->setPosition({ 10, 0 });
	sprite2->setPosition({ 0, 10 });
	animSpriteWithAnim1->setPosition({ 10, 0 });
	animSpriteWithAnim2->setPosition({ 0, 10 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(combinedVector, rrSpritePos);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the relative position
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 - rrSpritePos.x && comp->getOrigin().y == 0 - rrSpritePos.y) || (comp->getOrigin().x == 0 - rrSpritePos.x && comp->getOrigin().y == 10 - rrSpritePos.x));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_SingleSpriteVector_RelativeOffsets_CTR, ReusableObjects) {

	sprite1->setPosition({ 0,0 });
	sprite2->setPosition({ 0,0 });
	animSpriteWithAnim1->setPosition({ 0,0 });
	animSpriteWithAnim2->setPosition({ 0,0 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(combinedVector, initialOffsets);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0  && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_SingleSpriteVector_RelativeOffsets_Position_CTR, ReusableObjects) {
	sprite1->setPosition(rrSpritePos);
	sprite2->setPosition(rrSpritePos);
	animSpriteWithAnim1->setPosition(rrSpritePos);
	animSpriteWithAnim2->setPosition(rrSpritePos);
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(combinedVector, initialOffsets, rrSpritePos);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_TwoSpriteVectors_CTR, ReusableObjects) {

	sprite1->setPosition({ 10, 0 });
	sprite2->setPosition({ 0, 10 });
	animSpriteWithAnim1->setPosition({ 10, 0 });
	animSpriteWithAnim2->setPosition({ 0, 10 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the relative position
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_TwoSpriteVectors_Position_CTR, ReusableObjects) {

	sprite1->setPosition({ 10, 0 });
	sprite2->setPosition({ 0, 10 });
	animSpriteWithAnim1->setPosition({ 10, 0 });
	animSpriteWithAnim2->setPosition({ 0, 10 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, rrSpritePos);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the relative position
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 - rrSpritePos.x && comp->getOrigin().y == 0 - rrSpritePos.y) || (comp->getOrigin().x == 0 - rrSpritePos.x && comp->getOrigin().y == 10 - rrSpritePos.x));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_TwoSpriteVectors_RelativeOffsets_CTR, ReusableObjects) {

	sprite1->setPosition({ 0,0 });
	sprite2->setPosition({ 0,0 });
	animSpriteWithAnim1->setPosition({ 0,0 });
	animSpriteWithAnim2->setPosition({ 0,0 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_TwoSpriteVectors_RelativeOffsets_Position_CTR, ReusableObjects) {

	sprite1->setPosition(rrSpritePos);
	sprite2->setPosition(rrSpritePos);
	animSpriteWithAnim1->setPosition(rrSpritePos);
	animSpriteWithAnim2->setPosition(rrSpritePos);
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets, rrSpritePos);

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());


	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// For each Sprite on the RelativeRotationSprite
	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

// Test that the RelativeRotationSprite is safe to construct with empty component vectors.
BOOST_AUTO_TEST_CASE(RelativeRotionSprite_TwoSpriteVectors_Empty_CTR) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animatedSpriteVector);

	//check that the component vectors are empty
	BOOST_CHECK(rrSprite->getAnimatedSprites()->empty());
	BOOST_CHECK(rrSprite->getComponents()->empty());

	delete rrSprite;
}

// Test that Error::RelativeRotationSprite_MismatchedSizes throws when the vector sizes are not equal
BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_TwoSpriteVectors_RelativeOffsets_Mismatched_CTR, ReusableObjects) {
	initialOffsets.pop_back();

	// Ensure that RelativeRotationSprite throws an error when the components have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets), Error::RelativeRotationSprite_MismatchedSizes);

	initialOffsets.push_back(sf::Vector2f(10, 0));
	initialOffsets.push_back(sf::Vector2f(10, 0));

	// Ensure that RelativeRotationSprite throws an error when the offsets have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets), Error::RelativeRotationSprite_MismatchedSizes);
}

// Test that Error::RelativeRotationSprite_MismatchedSizes throws when the vector sizes are not equal
BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_OneSpriteVectors_RelativeOffsets_Mismatched_CTR, ReusableObjects) {
	initialOffsets.pop_back();

	// Ensure that RelativeRotationSprite throws an error when the components have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(combinedVector, initialOffsets), Error::RelativeRotationSprite_MismatchedSizes);

	initialOffsets.push_back(sf::Vector2f(10, 0));
	initialOffsets.push_back(sf::Vector2f(10, 0));

	// Ensure that RelativeRotationSprite throws an error when the offsets have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(combinedVector, initialOffsets), Error::RelativeRotationSprite_MismatchedSizes);
}


BOOST_AUTO_TEST_SUITE_END() // END RelativeRotionSprite_CTR


BOOST_AUTO_TEST_SUITE(RelativeRotionSprite_add)

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_addComponent, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	sprite1->setPosition({ 10, 0 });
	sprite2->setPosition({ 0, 10 });
	animSpriteWithAnim1->setPosition({ 10, 0 });
	animSpriteWithAnim2->setPosition({ 0, 10 });

	// Add all of the sprites without RelativeOffsets.
	for (sf::Sprite* comp : spriteVector)
	{
		rrSprite->addComponent(comp);
	}
	for (AnimatedSprite* comp : animSpriteVector)
	{
		rrSprite->addComponent(comp);
	}

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());

	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_addComponent_RelativeOffset, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	sprite1->setPosition({ 0, 0 });
	sprite2->setPosition({ 0, 0 });
	animSpriteWithAnim1->setPosition({ 0, 0 });
	animSpriteWithAnim2->setPosition({ 0, 0 });

	// Add all of the sprites with RelativeOffsets.
	for (std::size_t ii = 0; ii < spriteVector.size(); ++ii)
	{
		rrSprite->addComponent(spriteVector[ii], initialOffsets[ii]);
	}
	for (std::size_t ii = 0; ii < animSpriteVector.size(); ++ii)
	{
		rrSprite->addComponent(animSpriteVector[ii], initialOffsets[ii + spriteVector.size()]);
	}

	// Ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getComponents()->begin(), rrSprite->getComponents()->end(), combinedVector.begin(), combinedVector.end());

	// Ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(rrSprite->getAnimatedSprites()->begin(), rrSprite->getAnimatedSprites()->end(), animSpriteVector.begin(), animSpriteVector.end());

	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 && comp->getOrigin().y == 0) || (comp->getOrigin().x == 0 && comp->getOrigin().y == 10));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_addComponent_nullptr, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	sprite1->setPosition({ 10, 0 });
	sprite2->setPosition({ 0, 10 });
	animSpriteWithAnim1->setPosition({ 10, 0 });
	animSpriteWithAnim2->setPosition({ 0, 10 });

	// Add all of the sprites without RelativeOffsets.
	for (sf::Sprite* comp : spriteVector)
	{
		comp = nullptr;

		// Ensure that RelativeRotationSprite throws when passing a nullptr
		BOOST_CHECK_THROW(rrSprite->addComponent(comp), Error::Pointer_IllegalNull);
	}
	for (AnimatedSprite* comp : animSpriteVector)
	{
		comp = nullptr;

		// Ensure that RelativeRotationSprite throws when passing a nullptr
		BOOST_CHECK_THROW(rrSprite->addComponent(comp), Error::Pointer_IllegalNull);
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_addComponent_RelativeOffsets_nullptr, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	sprite1->setPosition({ 0, 0 });
	sprite2->setPosition({ 0, 0 });
	animSpriteWithAnim1->setPosition({ 0, 0 });
	animSpriteWithAnim2->setPosition({ 0, 0 });

	// Add all of the sprites without RelativeOffsets.
	for (std::size_t ii = 0; ii < spriteVector.size(); ++ii)
	{
		spriteVector[ii] = nullptr;
		BOOST_CHECK_THROW(rrSprite->addComponent(spriteVector[ii], initialOffsets[ii]), Error::Pointer_IllegalNull);
	}
	for (std::size_t ii = 0; ii < animSpriteVector.size(); ++ii)
	{
		animSpriteVector[ii] = nullptr;
		BOOST_CHECK_THROW(rrSprite->addComponent(animSpriteVector[ii], initialOffsets[ii + spriteVector.size()]), Error::Pointer_IllegalNull);
	}

	delete rrSprite;
}


BOOST_AUTO_TEST_SUITE_END() // END RelativeRotionSprite_add




BOOST_AUTO_TEST_SUITE(RelativeRotionSprite_operations)

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_scale_TwoInputs, ReusableObjects) {
	sprite1->setPosition({ 0, 0 });
	sprite2->setPosition({ 0, 0 });
	animSpriteWithAnim1->setPosition({ 0, 0 });
	animSpriteWithAnim2->setPosition({ 0, 0 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(combinedVector, initialOffsets);

	float scaleFactor = 2.0f;

	rrSprite->scale(scaleFactor, scaleFactor);

	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 * scaleFactor && comp->getOrigin().y == 0 * scaleFactor) || (comp->getOrigin().x == 0 * scaleFactor && comp->getOrigin().y == 10 * scaleFactor));
	}

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotionSprite_scale_OneInput, ReusableObjects) {
	sprite1->setPosition({ 0, 0 });
	sprite2->setPosition({ 0, 0 });
	animSpriteWithAnim1->setPosition({ 0, 0 });
	animSpriteWithAnim2->setPosition({ 0, 0 });
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(combinedVector, initialOffsets);

	sf::Vector2f scaleFactor = { 2.0f, 2.0f };

	rrSprite->scale(scaleFactor);

	for (sf::Sprite* comp : *(rrSprite->getComponents()))
	{
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp->getPosition().x == rrSprite->getPosition().x && comp->getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp->getOrigin().x == 10 * scaleFactor.x && comp->getOrigin().y == 0 * scaleFactor.y) 
			|| (comp->getOrigin().x == 0 * scaleFactor.x && comp->getOrigin().y == 10 * scaleFactor.y));
	}

	delete rrSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END RelativeRotionSprite_operations


BOOST_AUTO_TEST_SUITE_END() // END RelativeRotionSpriteTests