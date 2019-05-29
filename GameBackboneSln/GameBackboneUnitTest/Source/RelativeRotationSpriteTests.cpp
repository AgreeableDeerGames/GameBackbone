#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/CompoundSprite.h>
#include <GameBackbone/Core/RelativeRotationSprite.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

using namespace GB;

BOOST_AUTO_TEST_SUITE(RelativeRotationSpriteTests)

struct ReusableObjects{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "Textures/testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		sprite1 = sf::Sprite(*aSpriteTexture);
		sprite1.setPosition(10, 0);
		sprite2 = sf::Sprite(*aSpriteTexture);
		sprite2.setPosition(0, 10);
		spriteVector.push_back(sprite1);
		spriteVector.push_back(sprite2);

		auto aSpriteAnims = std::make_shared<FrameIndexAnimationVector>();
		std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
		aSpriteAnims->push_back(aSpriteAnim1);
		animSet1 = new AnimationSet(aSpriteAnims, *aSpriteTexture, {2, 2});
		animSet2 = new AnimationSet(aSpriteAnims, *aSpriteTexture, {2, 2});

		animSpriteWithAnim1 = AnimatedSprite(*aSpriteTexture, animSet1);
		animSpriteWithAnim1.setPosition(10, 0);
		animSpriteWithAnim2 = AnimatedSprite(*aSpriteTexture, animSet2);
		animSpriteWithAnim2.setPosition(0, 10);
		animSpriteVector.push_back(animSpriteWithAnim1);
		animSpriteVector.push_back(animSpriteWithAnim2);
	}

	void applyPredicateToRRSprites(RelativeRotationSprite& rr, std::function<void(sf::Sprite&)> f) {
		for (std::size_t i = 0; i < rr.getSpriteComponentCount(); ++i) {
			f(rr.getSpriteComponent(i));
		}
	}

	void applyPredicateToRRAnimSprites(RelativeRotationSprite& rr, std::function<void(sf::Sprite&)> f) {
		for (std::size_t i = 0; i < rr.getAnimatedComponentCount(); ++i) {
			f(rr.getAnimatedComponent(i));
		}
	}

	~ReusableObjects() {
		delete aSpriteTexture;
		delete animSet1;
		delete animSet2;
	}

	AnimatedSprite animSpriteWithAnim1;
	AnimatedSprite animSpriteWithAnim2;
	AnimationSet* animSet1;
	AnimationSet* animSet2;
	sf::Texture* aSpriteTexture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animSpriteVector;
	const sf::Vector2f rrSpritePos{ 3,3 };
	std::vector<sf::Vector2f> initialOffsets{ sf::Vector2f(10,0), sf::Vector2f(0,10), sf::Vector2f(10,0), sf::Vector2f(0,10) };
	std::vector<sf::Vector2f> spriteOffsets{ sf::Vector2f(10,0), sf::Vector2f(0,10) };
};

BOOST_AUTO_TEST_SUITE(RelativeRotationSprite_CTR)

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_default_CTR, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	// Ensure that the components are empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == true );

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_SingleSpriteVector_CTR, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == false );


	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	applyPredicateToRRSprites(*rrSprite, [this, rrSprite] (sf::Sprite& component) mutable {

		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	});

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_PositionOnly_CTR, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(rrSpritePos);

	// Ensure that the components are empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == true );

	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_SingleSpriteVector_Position_CTR, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, rrSpritePos);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x);
		BOOST_CHECK(component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 7 && component.getOrigin().y == -3) || (component.getOrigin().x == -3 && component.getOrigin().y == 7));
	});

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_SingleSpriteVector_RelativeOffsets_CTR, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, spriteOffsets);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	});

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_SingleSpriteVector_RelativeOffsets_Position_CTR, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, spriteOffsets, rrSpritePos);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	});

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_TwoSpriteVectors_CTR, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 2 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	auto predicate = [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_TwoSpriteVectors_Position_CTR, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, rrSpritePos);

	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 2 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to (3, 3)
	BOOST_CHECK(rrSprite->getPosition().x == 3 && rrSprite->getPosition().y == 3);

	auto predicate = [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 7 && component.getOrigin().y == -3) || (component.getOrigin().x == -3 && component.getOrigin().y == 7));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_TwoSpriteVectors_RelativeOffsets_CTR, ReusableObjects) {


	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets);

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 2 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to (0, 0)
	BOOST_CHECK(rrSprite->getPosition().x == 0 && rrSprite->getPosition().y == 0);

	auto predicate = [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_TwoSpriteVectors_RelativeOffsets_Position_CTR, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets, rrSpritePos);

	// Ensure that the position was set to rrSpritePos
	BOOST_CHECK(rrSprite->getPosition().x == rrSpritePos.x && rrSprite->getPosition().y == rrSpritePos.y);

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 2 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	// Ensure that the position was set to (3, 3)
	BOOST_CHECK(rrSprite->getPosition().x == 3 && rrSprite->getPosition().y == 3);

	auto predicate = [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

// Test that the RelativeRotationSprite is safe to construct with empty component vectors.
BOOST_AUTO_TEST_CASE(RelativeRotationSprite_TwoSpriteVectors_Empty_CTR) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animatedSpriteVector;
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animatedSpriteVector);

	// Ensure that the components are empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 0 );
	BOOST_CHECK(rrSprite->isEmpty() == true );

	delete rrSprite;
}

// Test that Error::RelativeRotationSprite_MismatchedSizes throws when the vector sizes are not equal
BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_TwoSpriteVectors_RelativeOffsets_Mismatched_CTR, ReusableObjects) {
	initialOffsets.pop_back();

	// Ensure that RelativeRotationSprite throws an error when the components have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets), std::invalid_argument);

	initialOffsets.push_back(sf::Vector2f(10, 0));
	initialOffsets.push_back(sf::Vector2f(10, 0));

	// Ensure that RelativeRotationSprite throws an error when the offsets have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets), std::invalid_argument);
}

// Test that Error::RelativeRotationSprite_MismatchedSizes throws when the vector sizes are not equal
BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_OneSpriteVectors_RelativeOffsets_Mismatched_CTR, ReusableObjects) {
	initialOffsets.pop_back();

	// Ensure that RelativeRotationSprite throws an error when the components have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(spriteVector, initialOffsets), std::invalid_argument);

	initialOffsets.push_back(sf::Vector2f(10, 0));
	initialOffsets.push_back(sf::Vector2f(10, 0));

	// Ensure that RelativeRotationSprite throws an error when the offsets have more elements
	BOOST_CHECK_THROW(RelativeRotationSprite(spriteVector, initialOffsets), std::invalid_argument);
}


BOOST_AUTO_TEST_SUITE_END() // END RelativeRotationSprite_CTR


BOOST_AUTO_TEST_SUITE(RelativeRotationSprite_add)

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_addComponent, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	// Add all of the sprites without RelativeOffsets.
	for (sf::Sprite& comp : spriteVector)
	{
		rrSprite->addComponent(comp);
	}
	for (AnimatedSprite& comp : animSpriteVector)
	{
		rrSprite->addComponent(comp);
	}

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 2 );
	BOOST_CHECK(rrSprite->isEmpty() == false );
	
	auto predicate = [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_addComponent_RelativeOffset, ReusableObjects) {
	RelativeRotationSprite* rrSprite = new RelativeRotationSprite();

	// Add all of the sprites with RelativeOffsets.
	for (std::size_t ii = 0; ii < spriteVector.size(); ++ii)
	{
		rrSprite->addComponent(spriteVector[ii], initialOffsets[ii]);
	}
	for (std::size_t ii = 0; ii < animSpriteVector.size(); ++ii)
	{
		rrSprite->addComponent(animSpriteVector[ii], initialOffsets[ii + spriteVector.size()]);
	}

	// Ensure that the components are not empty
	BOOST_CHECK(rrSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(rrSprite->getAnimatedComponentCount() == 2 );
	BOOST_CHECK(rrSprite->isEmpty() == false );

	auto predicate = [this, rrSprite] (sf::Sprite& component) mutable {
		BOOST_CHECK(component.getPosition().x == rrSprite->getPosition().x && component.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((component.getOrigin().x == 10 && component.getOrigin().y == 0) || (component.getOrigin().x == 0 && component.getOrigin().y == 10));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END RelativeRotationSprite_add

BOOST_AUTO_TEST_SUITE(RelativeRotationSprite_operations)

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_scale_TwoInputs, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets);

	float scaleFactor = 2.0f;

	rrSprite->scale(scaleFactor, scaleFactor);

	auto predicate = [this, rrSprite, &scaleFactor] (auto& comp) mutable {
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp.getPosition().x == rrSprite->getPosition().x && comp.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp.getOrigin().x == 10 * scaleFactor && comp.getOrigin().y == 0 * scaleFactor) || (comp.getOrigin().x == 0 * scaleFactor && comp.getOrigin().y == 10 * scaleFactor));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_FIXTURE_TEST_CASE(RelativeRotationSprite_scale_OneInput, ReusableObjects) {

	RelativeRotationSprite* rrSprite = new RelativeRotationSprite(spriteVector, animSpriteVector, initialOffsets);

	sf::Vector2f scaleFactor = { 2.0f, 2.0f };

	rrSprite->scale(scaleFactor);

	auto predicate = [this, rrSprite, &scaleFactor] (auto& comp) mutable {
		// Ensure that the position is the same position as the rrSprite and the origin was set using the offsets
		BOOST_CHECK(comp.getPosition().x == rrSprite->getPosition().x && comp.getPosition().y == rrSprite->getPosition().y);
		BOOST_CHECK((comp.getOrigin().x == 10 * scaleFactor.x && comp.getOrigin().y == 0 * scaleFactor.y) 
			|| (comp.getOrigin().x == 0 * scaleFactor.x && comp.getOrigin().y == 10 * scaleFactor.y));
	};

	// ensure the position and origin of the components is correct
	applyPredicateToRRSprites(*rrSprite, predicate);

	// ensure the position and origin of the components is correct
	applyPredicateToRRAnimSprites(*rrSprite, predicate);

	delete rrSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END RelativeRotationSprite_operations


BOOST_AUTO_TEST_SUITE_END() // END RelativeRotationSpriteTests