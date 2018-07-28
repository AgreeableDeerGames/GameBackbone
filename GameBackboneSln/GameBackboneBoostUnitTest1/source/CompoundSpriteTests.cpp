#include "stdafx.h"

#include <Backbone/AnimatedSprite.h>
#include <Backbone/BackboneBaseExceptions.h>
#include <Backbone/CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <string>

using namespace GB;


BOOST_AUTO_TEST_SUITE(CompoundSpriteTests)

struct ReusableObjects
{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "Textures/testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		sprite = new sf::Sprite(*aSpriteTexture);

		sf::Vector2u textureDim = aSpriteTexture->getSize();
		std::vector<std::vector<unsigned int>> aSpriteAnims;
		std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
		aSpriteAnims.push_back(aSpriteAnim1);
		animSet1 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);
		animSet2 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

		animSpriteWithAnim1 = new AnimatedSprite(*aSpriteTexture, animSet1);
		animSpriteWithAnim2 = new AnimatedSprite(*aSpriteTexture, animSet2);
	}
	~ReusableObjects() {

		delete aSpriteTexture;
		delete animSet1;
		delete animSet2;
		delete animSpriteWithAnim1;
		delete animSpriteWithAnim2;
		delete sprite;

	}

	AnimatedSprite* animSpriteWithAnim1;
	AnimatedSprite* animSpriteWithAnim2;
	AnimationSet* animSet1;
	AnimationSet* animSet2;
	sf::Texture* aSpriteTexture;
	sf::Sprite* sprite;
};

struct ReusableObjectsForOperations {

	ReusableObjectsForOperations() {

		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "Textures/testSprite.png";
		aSpriteTexture->loadFromFile(testTexturePath);

		sprite = new sf::Sprite(*aSpriteTexture);
		sprite->setPosition(10, 0);
		sprite2 = new sf::Sprite(*aSpriteTexture);
		sprite2->setPosition(0, 10);

		sf::Vector2u textureDim = aSpriteTexture->getSize();
		std::vector<std::vector<unsigned int>> aSpriteAnims;
		std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
		aSpriteAnims.push_back(aSpriteAnim1);
		animSet1 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);
		animSet2 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

		animSpriteWithAnim1 = new AnimatedSprite(*aSpriteTexture, animSet1);
		animSpriteWithAnim2 = new AnimatedSprite(*aSpriteTexture, animSet2);

		compoundSprite = new CompoundSprite({ sprite, sprite2 }, { animSpriteWithAnim1, animSpriteWithAnim2 });

	}

	~ReusableObjectsForOperations() {
		delete aSpriteTexture;
		delete animSet1;
		delete animSet2;
		delete animSpriteWithAnim1;
		delete animSpriteWithAnim2;
		delete sprite;
		delete sprite2;
		delete compoundSprite;
	}

	AnimatedSprite* animSpriteWithAnim1;
	AnimatedSprite* animSpriteWithAnim2;
	AnimationSet* animSet1;
	AnimationSet* animSet2;
	sf::Texture* aSpriteTexture;
	sf::Sprite* sprite;
	sf::Sprite* sprite2;
	CompoundSprite* compoundSprite;

};

BOOST_AUTO_TEST_SUITE(CompoundSprite_CTR)

// Test that the default constructor initializes values to empty and (0,0)
BOOST_FIXTURE_TEST_CASE(CompoundSprite_default_CTR, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getComponents()->empty());
	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());
	BOOST_CHECK(compoundSprite->getPosition().x == 0 && compoundSprite->getPosition().y == 0);

	delete compoundSprite;
}

// Test that constructing a compound sprite with a single sprite input vector correctly sets its components and position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Single_Sprite_Vector_CTR, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector{ sprite, animSpriteWithAnim1, animSpriteWithAnim2 };
	std::vector<AnimatedSprite*> animatedSpriteVector{ animSpriteWithAnim1, animSpriteWithAnim2 };
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector);

	// ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(compoundSprite->getComponents()->begin(), compoundSprite->getComponents()->end(), spriteVector.begin(), spriteVector.end());

	// ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(compoundSprite->getAnimatedSprites()->begin(), compoundSprite->getAnimatedSprites()->end(), animatedSpriteVector.begin(), animatedSpriteVector.end());

	// ensure that the position of the compound sprite is set correctly
	BOOST_CHECK(compoundSprite->getPosition().x == 0 && compoundSprite->getPosition().y == 0);

	delete compoundSprite;
}


// Test that constructing a compound sprite with a single sprite input vector correctly sets its components and position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Single_Sprite_Vector_setPosition_CTR, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector{ sprite, animSpriteWithAnim1, animSpriteWithAnim2 };
	std::vector<AnimatedSprite*> animatedSpriteVector{ animSpriteWithAnim1, animSpriteWithAnim2 };
	const sf::Vector2f compoundSpritePos{ 3,3 };

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, compoundSpritePos);

	// ensure that all of the passed components are identified as component sprites
	BOOST_CHECK_EQUAL_COLLECTIONS(compoundSprite->getComponents()->begin(), compoundSprite->getComponents()->end(), spriteVector.begin(), spriteVector.end());

	// ensure that the animated sprites from the input vector are correctly identified
	BOOST_CHECK_EQUAL_COLLECTIONS(compoundSprite->getAnimatedSprites()->begin(), compoundSprite->getAnimatedSprites()->end(), animatedSpriteVector.begin(), animatedSpriteVector.end());

	// check that the position is correctly assigned.
	BOOST_CHECK(compoundSprite->getPosition().x == compoundSpritePos.x && compoundSprite->getPosition().y == compoundSpritePos.y);


	delete compoundSprite;
}

// Test that constructing the CompundSprite with its components correctly sets the components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Sprite_And_AnimatedSprite_Vectors_CTR, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector{sprite};
	std::vector<AnimatedSprite*> animatedSpriteVector{animSpriteWithAnim1, animSpriteWithAnim2};

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	//check that the internal vectors have the correct values
	BOOST_CHECK(!compoundSprite->getComponents()->empty());
	for (unsigned int i = 0; i < spriteVector.size(); ++i) {
		BOOST_CHECK(compoundSprite->getComponents()->at(i) == spriteVector[i]);
	}
	BOOST_CHECK(!compoundSprite->getAnimatedSprites()->empty());
	for (unsigned int i = 0; i < animatedSpriteVector.size(); ++i) {
		BOOST_CHECK(compoundSprite->getAnimatedSprites()->at(i) == animatedSpriteVector[i]);
	}

	// check that the initial position is set correctly.
	BOOST_CHECK(compoundSprite->getPosition().x == 0 && compoundSprite->getPosition().y == 0);

	delete compoundSprite;
}

// Test that the CompoundSprite is safe to construct with empty component vectors.
BOOST_AUTO_TEST_CASE(CompoundSprite_Empty_Component_Vector_CTR) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	//check that the component vectors are empty
	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());
	BOOST_CHECK(compoundSprite->getComponents()->empty());


	delete compoundSprite;
}

// Test that CompoundSprite gets its components and position correctly set.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Sprite_And_AnimatedSprite_Vectors_setPosition_CTR, ReusableObjects) {
	std::vector<sf::Sprite*> sprites{sprite};
	std::vector<AnimatedSprite*> animSprites{animSpriteWithAnim1, animSpriteWithAnim2};
	const sf::Vector2f compoundSpritePos{ 3,3 };

	CompoundSprite* compoundSprite = new CompoundSprite(sprites, animSprites, compoundSpritePos);

	// check that the components of the sprite are correctly assigned.
	std::vector<sf::Sprite*> combinedSpriteVector;
	combinedSpriteVector.insert(combinedSpriteVector.end(), sprites.begin(), sprites.end());
	combinedSpriteVector.insert(combinedSpriteVector.end(), animSprites.begin(), animSprites.end());

	// check that both sprites and animated sprites are stored in the components vector, and that they are in the correct order
	BOOST_CHECK_EQUAL_COLLECTIONS(compoundSprite->getComponents()->begin(), compoundSprite->getComponents()->end(), combinedSpriteVector.begin(), combinedSpriteVector.end());

	// check that the animated sprite components were correctly found
	BOOST_CHECK_EQUAL_COLLECTIONS(compoundSprite->getAnimatedSprites()->begin(), compoundSprite->getAnimatedSprites()->end(), animSprites.begin(), animSprites.end());

	// check that the position is correctly assigned.
	BOOST_CHECK(compoundSprite->getPosition().x == compoundSpritePos.x && compoundSprite->getPosition().y == compoundSpritePos.y);

	delete compoundSprite;
}

// Test that CompoundSprite correctly sets its position.
BOOST_AUTO_TEST_CASE(CompoundSprite_setPosition_CTR) {
	const sf::Vector2f compoundSpritePos{ 3,3 };

	CompoundSprite* compoundSprite = new CompoundSprite(compoundSpritePos);

	BOOST_CHECK(compoundSprite->getPosition().x == compoundSpritePos.x && compoundSprite->getPosition().y == compoundSpritePos.y);
	BOOST_CHECK(compoundSprite->getComponents()->empty());
	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());

	delete compoundSprite;
}


BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_CTR

BOOST_AUTO_TEST_SUITE(CompoundSprite_getter)

// Test that CompoundSprite correctly adds all sprites and animated sprites to its components vector
BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Populated_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);
	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	// ensure that both sprites and animated sprites are added
	BOOST_CHECK(compoundSprite->getComponents()->size() == 2);
	BOOST_CHECK(compoundSprite->getComponents()->at(0) == sprite);
	BOOST_CHECK(compoundSprite->getComponents()->at(1) == animSpriteWithAnim1);

	delete compoundSprite;
}

// Test that CompoundSprite correctly gets sprites when only the sprites vector is populated
BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Populated_Sprite_Vector, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	// check that the sprite from the input vector was correctly added
	BOOST_CHECK(compoundSprite->getComponents()->size() == 1);
	BOOST_CHECK(compoundSprite->getComponents()->at(0) == sprite);

	delete compoundSprite;
}

// Test that CompoundSprite correctly gets sprites when only the animated sprites vector was populated on construction
BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Populated_Animated_Vector, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	animatedSpriteVector.push_back(animSpriteWithAnim1);
	animatedSpriteVector.push_back(animSpriteWithAnim2);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	// check that the correct number of components is found
	BOOST_CHECK(compoundSprite->getComponents()->size() == 2);

	// check that the added components are correct
	BOOST_CHECK(compoundSprite->getComponents()->at(0) == animSpriteWithAnim1);
	BOOST_CHECK(compoundSprite->getComponents()->at(1) == animSpriteWithAnim2);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Empty_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	BOOST_CHECK(compoundSprite->getComponents()->empty());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_default_CTR, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getComponents()->empty());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getAnimatedSprites_Populated_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);
	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	BOOST_CHECK(compoundSprite->getAnimatedSprites()->size() == 1);
	BOOST_CHECK(compoundSprite->getAnimatedSprites()->at(0) == animSpriteWithAnim1);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getAnimatedSprites_Populated_Sprite_Vector, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	BOOST_CHECK(compoundSprite->getAnimatedSprites()->size() == 0);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getAnimatedSprites_Populated_Animated_Vector, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	BOOST_CHECK(compoundSprite->getAnimatedSprites()->size() == 1);
	BOOST_CHECK(compoundSprite->getAnimatedSprites()->at(0) == animSpriteWithAnim1);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getAnimatedSprites_Empty_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getAnimatedSprites_default_CTR, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_getter


BOOST_AUTO_TEST_SUITE(CompoundSprite_add)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(sprite);
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getComponents();

	auto it = std::find(spriteVector->begin(), spriteVector->end(), sprite);
	BOOST_CHECK(it != spriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(animSpriteWithAnim1);
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	auto it = std::find(animatedSpriteVector->begin(), animatedSpriteVector->end(), animSpriteWithAnim1);
	BOOST_CHECK(it != animatedSpriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_nullptr, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	delete sprite;
	sprite = nullptr;
	delete animSpriteWithAnim1;
	animSpriteWithAnim1 = nullptr;

	// Ensure that CompoundSprite throws when passing a nullptr
	BOOST_CHECK_THROW(compoundSprite->addComponent(sprite), Error::Pointer_IllegalNull);
	BOOST_CHECK_THROW(compoundSprite->addComponent(animSpriteWithAnim1), Error::Pointer_IllegalNull);

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_add


BOOST_AUTO_TEST_SUITE(CompoundSprite_remove)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(sprite);
	compoundSprite->removeComponent(sprite);
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getComponents();

	BOOST_CHECK(spriteVector->empty());

	auto it = std::find(spriteVector->begin(), spriteVector->end(), sprite);
	BOOST_CHECK(it == spriteVector->end());

	delete compoundSprite;
}

// Test that when removing an animated sprite the correct sprite is removed.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_AnimatedSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(animSpriteWithAnim1);
	compoundSprite->addComponent(animSpriteWithAnim2);
	compoundSprite->removeComponent(animSpriteWithAnim1);
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getComponents();

	//Ensure that the compound sprite correctly removed the selected sprite
	BOOST_CHECK(animatedSpriteVector->size() == 1);
	BOOST_CHECK(spriteVector->size() == 1);
	BOOST_CHECK(spriteVector->at(0) == animSpriteWithAnim2);

	delete compoundSprite;
}

// Test that removing a sprite that was never in the compound sprite has no impact on the sprite
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(animSpriteWithAnim1);
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();
	
	compoundSprite->removeComponent(sprite);

	// ensure that the state of the sprite is the same as before the removal
	BOOST_CHECK(animatedSpriteVector->size() == 1);
	BOOST_CHECK(compoundSprite->getComponents()->size() == 1);
	BOOST_CHECK(compoundSprite->getComponents()->at(0) == animSpriteWithAnim1);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(sprite);
	compoundSprite->addComponent(animSpriteWithAnim1);
	compoundSprite->addComponent(animSpriteWithAnim2);

	compoundSprite->clearComponents();
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getComponents();
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	BOOST_CHECK(spriteVector->empty());
	BOOST_CHECK(animatedSpriteVector->empty());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->clearComponents();
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getComponents();
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	BOOST_CHECK(spriteVector->empty());
	BOOST_CHECK(animatedSpriteVector->empty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_remove


BOOST_AUTO_TEST_SUITE(CompoundSprite_operations)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_update, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();
	for (unsigned int i = 0; i < animatedSpriteVector->size(); ++i) {
		animatedSpriteVector->at(i)->runAnimation(0);
	}

	compoundSprite->update(sf::milliseconds(2));

	for (unsigned int i = 0; i < animatedSpriteVector->size(); ++i) {
		BOOST_CHECK(animatedSpriteVector->at(i)->getCurrentFrame() == 1);
	}

	delete compoundSprite;
}

BOOST_AUTO_TEST_CASE(CompoundSprite_scale) {
	//for some reason cant use reusable objects. recreate them here.
	sf::Texture* aSpriteTexture = new sf::Texture();
	std::string testTexturePath = "Textures/testSprite.png";
	aSpriteTexture->loadFromFile(testTexturePath);
	sf::Vector2u textureDim = aSpriteTexture->getSize();
	std::vector<std::vector<unsigned int>> aSpriteAnims;
	std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
	aSpriteAnims.push_back(aSpriteAnim1);
	AnimationSet* animSet1 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);
	AnimationSet* animSet2 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

	AnimatedSprite* animSpriteWithAnim1 = new AnimatedSprite(*aSpriteTexture, animSet1);
	AnimatedSprite* animSpriteWithAnim2 = new AnimatedSprite(*aSpriteTexture, animSet2);

	//create compound sprite
	sf::Sprite* sfSprite = new sf::Sprite(*aSpriteTexture);
	std::vector<sf::Sprite*> spriteVec = { sfSprite };
	std::vector<AnimatedSprite*> animSpriteVec = { animSpriteWithAnim1, animSpriteWithAnim2 };
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVec, animSpriteVec);
	const float X_SCALE_FACTOR = 0.1f;
	const float Y_SCALE_FACTOR = 0.2f;

	compoundSprite->scale(X_SCALE_FACTOR, Y_SCALE_FACTOR);

	//ensure all sprites got the correct scale
	for (sf::Sprite* sprite : *(compoundSprite->getComponents()))
	{
		BOOST_CHECK(sprite->getScale().x == X_SCALE_FACTOR);
		BOOST_CHECK(sprite->getScale().y == Y_SCALE_FACTOR);
	}

	//ensure all animated sprites got the correct scale
	for (AnimatedSprite* animSprite : *(compoundSprite->getAnimatedSprites()))
	{
		BOOST_CHECK(animSprite->getScale().x == X_SCALE_FACTOR);
		BOOST_CHECK(animSprite->getScale().y == Y_SCALE_FACTOR);
	}

	delete compoundSprite;
	delete sfSprite;
	delete animSpriteWithAnim1;
	delete animSpriteWithAnim2;
	delete animSet1;
	delete animSet2;
	delete aSpriteTexture;
}

// Test that setting the scale of a compound sprite scales all of its component sprites
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setScale_Two_Inputs, ReusableObjectsForOperations) {
	const float SCALE_FACTOR_X = 0.123f;
	const float SCALE_FACTOR_Y = 0.234f;
	compoundSprite->setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);

	// ensure that the scale of the sprite components has been set
	for (auto sprite : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(sprite->getScale().x, SCALE_FACTOR_X);
		BOOST_CHECK_EQUAL(sprite->getScale().y, SCALE_FACTOR_Y);
	}

	// ensure that the scale of the animated sprite components has been set
	for (auto sprite : *compoundSprite->getAnimatedSprites()) {
		BOOST_CHECK_EQUAL(sprite->getScale().x, SCALE_FACTOR_X);
		BOOST_CHECK_EQUAL(sprite->getScale().y, SCALE_FACTOR_Y);
	}
}

// Test that setting the scale of the compound sprite sets the scale of all of its component sprites
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setScale_One_Input, ReusableObjectsForOperations) {
	const float SCALE_FACTOR_X = 0.123f;
	const float SCALE_FACTOR_Y = 0.234f;
	const sf::Vector2f SCALE_FACTOR{ SCALE_FACTOR_X, SCALE_FACTOR_Y };
	compoundSprite->setScale(SCALE_FACTOR);

	// ensure that the scale of the sprite components has been set
	for (auto sprite : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(sprite->getScale().x, SCALE_FACTOR_X);
		BOOST_CHECK_EQUAL(sprite->getScale().y, SCALE_FACTOR_Y);
	}

	// ensure that the scale of the animated sprite components has been set
	for (auto sprite : *compoundSprite->getAnimatedSprites()) {
		BOOST_CHECK_EQUAL(sprite->getScale().x, SCALE_FACTOR_X);
		BOOST_CHECK_EQUAL(sprite->getScale().y, SCALE_FACTOR_Y);
	}

}

// Tests that scaling the compound sprite scales all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Scale_Point2D, ReusableObjects) {
	std::vector<sf::Sprite*> sprites{ sprite };
	std::vector<AnimatedSprite*> animSprites{ animSpriteWithAnim1, animSpriteWithAnim2 };
	const sf::Vector2f SCALE{0.5f, 0.6f};
	CompoundSprite compoundSprite(sprites, animSprites);
	compoundSprite.scale(SCALE);

	//ensure that all components were scaled correctly
	for (auto sprite : *compoundSprite.getComponents()) {
		BOOST_CHECK(sprite->getScale().x == SCALE.x && sprite->getScale().y == SCALE.y);
	}
	for (auto sprite : *compoundSprite.getAnimatedSprites()) {
		BOOST_CHECK(sprite->getScale().x == SCALE.x && sprite->getScale().y == SCALE.y);
	}
}

// Tests that rotating a compound sprite rotates all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_rotate_rotate_from_zero, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	compoundSprite->rotate(ROTATION);

	// ensure all components were rotated
	for (auto sprite : *compoundSprite->getAnimatedSprites()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
	for (auto sprite : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
}

// Test that applying a rotation to a compound sprite is cumulative.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Rotate_Additive_Rotate, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	const unsigned int NUM_ROTATIONS = 2;

	for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
		compoundSprite->rotate(ROTATION);
	}
	// ensure all components were rotated
	for (auto sprite : *compoundSprite->getAnimatedSprites()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), NUM_ROTATIONS * ROTATION);
	}
	for (auto sprite : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), NUM_ROTATIONS * ROTATION);
	}
}

// Test that setting the rotation of a compound sprite sets the rotation for all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotation_rotate_from_zero, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	compoundSprite->setRotation(10);

	// ensure all components were rotated
	for (auto sprite : *compoundSprite->getAnimatedSprites()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
	for (auto sprite : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
}

// Test that setting a rotation to a compound sprite is not cumulative.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotation_NonAdditive_Rotate, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	const unsigned int NUM_ROTATIONS = 2;

	for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
		compoundSprite->setRotation(ROTATION);
	}
	// ensure all components were rotated
	for (auto sprite : *compoundSprite->getAnimatedSprites()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
	for (auto sprite : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
}

// Test that a single component can be selected for rotation
BOOST_FIXTURE_TEST_CASE(CompoundSprite_rotateComponents_Two_Components, ReusableObjectsForOperations) {
	const std::set<size_t> SPRITES_TO_ROTATE = {1,2};
	const float ROTATION = 3.1415f;

	compoundSprite->rotateComponents(SPRITES_TO_ROTATE, ROTATION);

	// ensure that the sprites had their rotations correctly applied
	for (size_t index : SPRITES_TO_ROTATE) {
		BOOST_CHECK_EQUAL(compoundSprite->getComponents()->at(index)->getRotation(), ROTATION);
	}
}

// Test that no components can be selected for rotation
BOOST_FIXTURE_TEST_CASE(CompoundSprite_rotateComponents_No_Component, ReusableObjectsForOperations) {
	const std::set<size_t> SPRITES_TO_ROTATE = {};
	const float ROTATION = 3.1415f;

	compoundSprite->rotateComponents(SPRITES_TO_ROTATE, ROTATION);

	// ensure that the sprites had their rotations correctly applied
	for (sf::Sprite* component : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(component->getRotation(), 0);
	}
}

// Test that applying a rotation to a compound sprite is cumulative.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_rotateComponents_Additive_Rotate, ReusableObjectsForOperations) {
	const std::set<size_t> SPRITES_TO_ROTATE = { 1,2 };
	const float ROTATION = 10;
	const unsigned int NUM_ROTATIONS = 2;

	for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
		compoundSprite->rotateComponents(SPRITES_TO_ROTATE, ROTATION);
	}
	// ensure all components were rotated
	for (size_t index : SPRITES_TO_ROTATE){
		sf::Sprite* sprite = compoundSprite->getComponents()->at(index);
		BOOST_CHECK_EQUAL(sprite->getRotation(), NUM_ROTATIONS * ROTATION);
	}
	for (size_t index : SPRITES_TO_ROTATE) {
		sf::Sprite* sprite = compoundSprite->getComponents()->at(index);
		BOOST_CHECK_EQUAL(sprite->getRotation(), NUM_ROTATIONS * ROTATION);
	}
}

// Test that selected components can be selected to have its rotation set
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotationOfComponents_Two_Components, ReusableObjectsForOperations) {
	const std::set<size_t> SPRITES_TO_ROTATE = { 1,2 };
	const float ROTATION = 3.1415f;

	compoundSprite->setRotationOfComponents(SPRITES_TO_ROTATE, ROTATION);

	// ensure that the sprites had their rotations correctly applied
	for (size_t index : SPRITES_TO_ROTATE) {
		BOOST_CHECK_EQUAL(compoundSprite->getComponents()->at(index)->getRotation(), ROTATION);
	}
}

// Test that no components can be selected for rotation
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotationOfComponents_No_Component, ReusableObjectsForOperations) {
	const std::set<size_t> SPRITES_TO_ROTATE = {};
	const float ROTATION = 3.1415f;

	compoundSprite->setRotationOfComponents(SPRITES_TO_ROTATE, ROTATION);

	// ensure that the sprites had their rotations correctly applied
	for (sf::Sprite* component : *compoundSprite->getComponents()) {
		BOOST_CHECK_EQUAL(component->getRotation(), 0);
	}
}

// Test that setting a rotation to selected components compound sprite is not cumulative.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotationOfComponents_NonAdditive_Rotate, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	const unsigned int NUM_ROTATIONS = 2;
	const std::set<size_t> SPRITES_TO_ROTATE = { 1,2 };

	for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
		compoundSprite->setRotationOfComponents(SPRITES_TO_ROTATE, ROTATION);
	}
	// ensure all selected components were rotated
	for (size_t index : SPRITES_TO_ROTATE) {
		sf::Sprite* sprite = compoundSprite->getComponents()->at(index);
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
	for (size_t index : SPRITES_TO_ROTATE) {
		sf::Sprite* sprite = compoundSprite->getComponents()->at(index);
		BOOST_CHECK_EQUAL(sprite->getRotation(), ROTATION);
	}
}

BOOST_AUTO_TEST_CASE(CompoundSprite_move) {
	//for some reason cant use reusable objects. recreate them here.
	sf::Texture* aSpriteTexture = new sf::Texture();
	std::string testTexturePath = "Textures/testSprite.png";
	aSpriteTexture->loadFromFile(testTexturePath);
	sf::Vector2u textureDim = aSpriteTexture->getSize();
	std::vector<std::vector<unsigned int>> aSpriteAnims;
	std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
	aSpriteAnims.push_back(aSpriteAnim1);
	AnimationSet* animSet1 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);
	AnimationSet* animSet2 = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

	AnimatedSprite* animSpriteWithAnim1 = new AnimatedSprite(*aSpriteTexture, animSet1);
	AnimatedSprite* animSpriteWithAnim2 = new AnimatedSprite(*aSpriteTexture, animSet2);

	//create compound sprite
	sf::Sprite* sfSprite = new sf::Sprite(*aSpriteTexture);
	std::vector<sf::Sprite*> spriteVec = { sfSprite };
	std::vector<AnimatedSprite*> animSpriteVec = { animSpriteWithAnim1, animSpriteWithAnim2 };
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVec, animSpriteVec);
	const float X_OFFSET = 500.6f;
	const float Y_OFFSET = 100.2f;

	compoundSprite->move(X_OFFSET, Y_OFFSET);

	//ensure all sprites got the correct position
	for (sf::Sprite* sprite : *(compoundSprite->getComponents()))
	{
		BOOST_CHECK_CLOSE_FRACTION(sprite->getPosition().x, X_OFFSET, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(sprite->getPosition().y, Y_OFFSET, 1.0f);
	}

	//ensure all animated sprites got the correct position
	for (AnimatedSprite* animSprite : *(compoundSprite->getAnimatedSprites()))
	{
		BOOST_CHECK_CLOSE_FRACTION(animSprite->getPosition().x, X_OFFSET, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(animSprite->getPosition().y, Y_OFFSET, 1.0f);
	}

	delete compoundSprite;
	delete sfSprite;
	delete animSpriteWithAnim1;
	delete animSpriteWithAnim2;
	delete animSet1;
	delete animSet2;
	delete aSpriteTexture;
}

// Test that moving a compound sprite correctly moves all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_move_Vector2f, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite({ sprite, animSpriteWithAnim1, animSpriteWithAnim2 });
	const sf::Vector2f OFFSET(213.456f, 456.123f);

	compoundSprite->move(OFFSET);


	//ensure all sprites got the correct position
	for (sf::Sprite* tempSprite : *(compoundSprite->getComponents()))
	{
		BOOST_CHECK_CLOSE_FRACTION(tempSprite->getPosition().x, OFFSET.x, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(tempSprite->getPosition().y, OFFSET.y, 1.0f);
	}

	delete compoundSprite;
}

// Test that setting the position of the compound sprite correctly sets the position of all of the members
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Vector2f, ReusableObjectsForOperations) {
	const float POSITION_X = 123.456f;
	const float POSITION_Y = 654.321f;
	const sf::Vector2f POSITION(POSITION_X, POSITION_Y);

	std::vector<sf::Vector2f> oldPositions;
	for (sf::Sprite* tempSprite : *compoundSprite->getComponents()) {
		oldPositions.push_back(tempSprite->getPosition());
	}

	compoundSprite->setPosition(POSITION);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite->getPosition().x == POSITION_X && compoundSprite->getPosition().y == POSITION_Y);
	for (size_t i = 0; i < compoundSprite->getComponents()->size(); ++i) {
		sf::Sprite* tempSprite = compoundSprite->getComponents()->at(i);
		// can do this b/c the compound sprite started at 0,0
		BOOST_CHECK(tempSprite->getPosition().x == POSITION_X + oldPositions[i].x && tempSprite->getPosition().y == POSITION_Y + oldPositions[i].y);
	}

}

// Test that setting the position of the compound sprite to its current position does nothing
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Current_Position_Vector2f, ReusableObjectsForOperations) {
	const float POSITION_X = 0;
	const float POSITION_Y = 0;
	const sf::Vector2f POSITION(POSITION_X, POSITION_Y);

	std::vector<sf::Vector2f> oldPositions;
	for (sf::Sprite* tempSprite : *compoundSprite->getComponents()) {
		oldPositions.push_back(tempSprite->getPosition());
	}

	compoundSprite->setPosition(POSITION);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite->getPosition().x == POSITION_X && compoundSprite->getPosition().y == POSITION_Y);
	for (size_t i = 0; i < compoundSprite->getComponents()->size(); ++i) {
		sf::Sprite* tempSprite = compoundSprite->getComponents()->at(i);
		// can do this b/c the compound sprite started at 0,0
		BOOST_CHECK(tempSprite->getPosition().x == oldPositions[i].x && tempSprite->getPosition().y == oldPositions[i].y);
	}

}

// Test that setting the position of the compound sprite correctly sets the position of all of the members
// even when the compound sprite starts at a non zero position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Vector2f_NON_ORIGIN_START, ReusableObjects) {
	const float STARTING_X = 10;
	const float STARTING_Y = -20;
	const sf::Vector2f STARTING_POS = { STARTING_X, STARTING_Y };
	const float POSITION_X = 123.456f;
	const float POSITION_Y = 654.321f;
	const sf::Vector2f POSITION(POSITION_X, POSITION_Y);
	CompoundSprite* compoundSprite = new CompoundSprite{ {sprite, animSpriteWithAnim1, animSpriteWithAnim2}, STARTING_POS };

	std::vector<sf::Vector2f> oldPositions;
	for (sf::Sprite* tempSprite : *compoundSprite->getComponents()) {
		oldPositions.push_back(tempSprite->getPosition());
	}

	compoundSprite->setPosition(POSITION);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite->getPosition().x == POSITION_X && compoundSprite->getPosition().y == POSITION_Y);
	for (size_t i = 0; i < compoundSprite->getComponents()->size(); ++i) {
		sf::Sprite* tempSprite = compoundSprite->getComponents()->at(i);
		// can do this b/c the compound sprite started at 0,0
		BOOST_CHECK(tempSprite->getPosition().x == POSITION_X + (oldPositions[i].x - STARTING_X) && tempSprite->getPosition().y == POSITION_Y + (oldPositions[i].y - STARTING_Y));
	}


	delete compoundSprite;
}

// Test that setting the position of the compound sprite correctly sets the position of all of the members
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Two_Floats, ReusableObjectsForOperations) {
	const float POSITION_X = 123.456f;
	const float POSITION_Y = 654.321f;

	std::vector<sf::Vector2f> oldPositions;
	for (sf::Sprite* tempSprite : *compoundSprite->getComponents()) {
		oldPositions.push_back(tempSprite->getPosition());
	}

	compoundSprite->setPosition(POSITION_X, POSITION_Y);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite->getPosition().x == POSITION_X && compoundSprite->getPosition().y == POSITION_Y);
	for (size_t i = 0; i < compoundSprite->getComponents()->size(); ++i) {
		sf::Sprite* tempSprite = compoundSprite->getComponents()->at(i);
		// can do this b/c the compound sprite started at 0,0
		BOOST_CHECK(tempSprite->getPosition().x == POSITION_X + oldPositions[i].x && tempSprite->getPosition().y == POSITION_Y + oldPositions[i].y);
	}

}

// Test that setting the position of the compound sprite to its current position does nothing
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Current_Position_Two_Floats, ReusableObjectsForOperations) {
	const float POSITION_X = 0;
	const float POSITION_Y = 0;

	std::vector<sf::Vector2f> oldPositions;
	for (sf::Sprite* tempSprite : *compoundSprite->getComponents()) {
		oldPositions.push_back(tempSprite->getPosition());
	}

	compoundSprite->setPosition(POSITION_X, POSITION_Y);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite->getPosition().x == POSITION_X && compoundSprite->getPosition().y == POSITION_Y);
	for (size_t i = 0; i < compoundSprite->getComponents()->size(); ++i) {
		sf::Sprite* tempSprite = compoundSprite->getComponents()->at(i);
		// can do this b/c the compound sprite started at 0,0
		BOOST_CHECK(tempSprite->getPosition().x == oldPositions[i].x && tempSprite->getPosition().y == oldPositions[i].y);
	}

}

// Test that setting the position of the compound sprite correctly sets the position of all of the members
// even when the compound sprite starts at a non zero position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Two_Floats_NON_ORIGIN_START, ReusableObjects) {
	const float STARTING_X = 10;
	const float STARTING_Y = -20;
	const sf::Vector2f STARTING_POS = { STARTING_X, STARTING_Y };
	const float POSITION_X = 123.456f;
	const float POSITION_Y = 654.321f;
	CompoundSprite* compoundSprite = new CompoundSprite{ { sprite, animSpriteWithAnim1, animSpriteWithAnim2 }, STARTING_POS };

	std::vector<sf::Vector2f> oldPositions;
	for (sf::Sprite* tempSprite : *compoundSprite->getComponents()) {
		oldPositions.push_back(tempSprite->getPosition());
	}

	compoundSprite->setPosition(POSITION_X, POSITION_Y);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite->getPosition().x == POSITION_X && compoundSprite->getPosition().y == POSITION_Y);
	for (size_t i = 0; i < compoundSprite->getComponents()->size(); ++i) {
		sf::Sprite* tempSprite = compoundSprite->getComponents()->at(i);
		// can do this b/c the compound sprite started at 0,0
		BOOST_CHECK(tempSprite->getPosition().x == POSITION_X + (oldPositions[i].x - STARTING_X) && tempSprite->getPosition().y == POSITION_Y + (oldPositions[i].y - STARTING_Y));
	}


	delete compoundSprite;
}


BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_opertaions

BOOST_AUTO_TEST_SUITE_END() // END CompoundSpriteTests