#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>

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

		sprite = sf::Sprite(*aSpriteTexture);
		sprite.setPosition(1,1);

		sprite2 = sf::Sprite(*aSpriteTexture);
		sprite2.setPosition(2,2);

		int halfTextureWidth = aSpriteTexture->getSize().x / 2;
		int textureHeight = aSpriteTexture->getSize().y;

		animSet1 = std::make_shared<AnimationSet>(
			std::vector<Animation> {
				Animation {
					sf::IntRect(0, 0, halfTextureWidth, textureHeight),
					sf::IntRect(halfTextureWidth, 0, halfTextureWidth, textureHeight)
				}
			}
		);
		animSet2 = std::make_shared<AnimationSet>(
			std::vector<Animation> {
				GB::Animation{
					sf::IntRect(0, 0, halfTextureWidth, textureHeight),
					sf::IntRect(halfTextureWidth, 0, halfTextureWidth, textureHeight)
				}
			}
		);

		animSpriteWithAnim1 = AnimatedSprite(*aSpriteTexture, animSet1);
		animSpriteWithAnim1.setPosition(10, 10);
		animSpriteWithAnim2 = AnimatedSprite(*aSpriteTexture, animSet2);
		animSpriteWithAnim2.setPosition(20, 20);
	}
	~ReusableObjects() {

		delete aSpriteTexture;
	}

	AnimatedSprite animSpriteWithAnim1;
	AnimatedSprite animSpriteWithAnim2;
	AnimationSet::Ptr animSet1;
	AnimationSet::Ptr animSet2;
	sf::Texture* aSpriteTexture;
	sf::Sprite tempsprite;
	sf::Sprite sprite2;
	sf::Sprite sprite;
};

struct ReusableObjectsForOperations : ReusableObjects {

	ReusableObjectsForOperations() : compoundSprite({sprite, sprite2}, {animSpriteWithAnim1, animSpriteWithAnim2})
	{
	}

	CompoundSprite compoundSprite;
};

BOOST_AUTO_TEST_SUITE(CompoundSprite_CTR)

// Test that the default constructor initializes values to empty and (0,0)
BOOST_FIXTURE_TEST_CASE(CompoundSprite_default_CTR, ReusableObjects) {
	CompoundSprite compoundSprite;

	BOOST_CHECK(compoundSprite.isEmpty());
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite.getPosition().x == 0 && compoundSprite.getPosition().y == 0);
}

// Test that constructing a compound sprite with a single sprite input vector correctly sets its components and position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Single_Sprite_Vector_CTR, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector{ sprite, sprite2 };
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector);

	// ensure that the right number of components are found
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// ensure that the added components are correct
	// (The components are coppied just check position as a sentinel value)
	for (std::size_t i = 0; i < compoundSprite->getSpriteComponentCount(); ++i){
		BOOST_CHECK(compoundSprite->getSpriteComponent(i).getPosition() == spriteVector[i].getPosition());
	}

	// ensure that the position of the compound sprite is set correctly
	BOOST_CHECK(compoundSprite->getPosition().x == 0 && compoundSprite->getPosition().y == 0);

	delete compoundSprite;
}


// Test that constructing a compound sprite with a single sprite input vector correctly sets its components and position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Single_Sprite_Vector_setPosition_CTR, ReusableObjects) {
	const sf::Vector2f compoundSpritePos{ 3,3 };

	std::vector<sf::Sprite> spriteVector{ sprite, sprite2 };
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, compoundSpritePos);

	// ensure that the right number of components are found
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// ensure that the added components are correct
	// (The components are coppied just check position as a sentinel value)
	for (std::size_t i = 0; i < compoundSprite->getSpriteComponentCount(); ++i){
		BOOST_CHECK(compoundSprite->getSpriteComponent(i).getPosition() == spriteVector[i].getPosition());
	}

	// check that the position is correctly assigned.
	BOOST_CHECK(compoundSprite->getPosition().x == compoundSpritePos.x && compoundSprite->getPosition().y == compoundSpritePos.y);

	delete compoundSprite;
}

// Test that constructing the CompundSprite with its components correctly sets the components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Sprite_And_AnimatedSprite_Vectors_CTR, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector{sprite, sprite2};
	std::vector<AnimatedSprite> animatedSpriteVector{animSpriteWithAnim1, animSpriteWithAnim2};

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	//check that the internal vectors have the correct values
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == spriteVector.size());
	for (unsigned int i = 0; i < spriteVector.size(); ++i) {
		BOOST_CHECK(compoundSprite->getSpriteComponent(i).getPosition() == spriteVector[i].getPosition());
	}
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == animatedSpriteVector.size());
	for (unsigned int i = 0; i < animatedSpriteVector.size(); ++i) {
		BOOST_CHECK(compoundSprite->getAnimatedComponent(i).getPosition() == animatedSpriteVector[i].getPosition());
	}

	// check that the initial position is set correctly.
	BOOST_CHECK(compoundSprite->getPosition().x == 0 && compoundSprite->getPosition().y == 0);

	delete compoundSprite;
}

// Test that the CompoundSprite is safe to construct with empty component vectors.
BOOST_AUTO_TEST_CASE(CompoundSprite_Empty_Component_Vector_CTR) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animatedSpriteVector;
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	//check that the component vectors are empty
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty());

	delete compoundSprite;
}

// Test that CompoundSprite correctly sets its position.
BOOST_AUTO_TEST_CASE(CompoundSprite_setPosition_CTR) {
	const sf::Vector2f compoundSpritePos{ 3,3 };

	CompoundSprite* compoundSprite = new CompoundSprite(compoundSpritePos);

	BOOST_CHECK(compoundSprite->getPosition().x == compoundSpritePos.x && compoundSprite->getPosition().y == compoundSpritePos.y);
	BOOST_CHECK(compoundSprite->isEmpty());
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);

	delete compoundSprite;
}


BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_CTR

BOOST_AUTO_TEST_SUITE(CompoundSprite_getter)

// Test that CompoundSprite correctly adds all sprites and animated sprites to its components vector
BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Populated_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animatedSpriteVector;

	spriteVector.push_back(sprite);
	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	// ensure that both sprites and animated sprites are added
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 1);
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 1);
	BOOST_CHECK(compoundSprite->getAnimatedComponent(0).getPosition() == animSpriteWithAnim1.getPosition());
	BOOST_CHECK(compoundSprite->getSpriteComponent(0).getPosition() == sprite.getPosition());

	delete compoundSprite;
}

// Test that CompoundSprite correctly gets sprites when only the sprites vector is populated
BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Populated_Sprite_Vector, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animatedSpriteVector;

	spriteVector.push_back(sprite);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	// check that the sprite from the input vector was correctly added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 1);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == false);
	BOOST_CHECK(compoundSprite->getSpriteComponent(0).getPosition() == sprite.getPosition());

	delete compoundSprite;
}

// Test that CompoundSprite correctly gets sprites when only the animated sprites vector was populated on construction
BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Populated_Animated_Vector, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animatedSpriteVector;

	animatedSpriteVector.push_back(animSpriteWithAnim1);
	animatedSpriteVector.push_back(animSpriteWithAnim2);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

		// check that the sprite from the input vector was correctly added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 2);
	BOOST_CHECK(compoundSprite->isEmpty() == false);
	BOOST_CHECK(compoundSprite->getAnimatedComponent(0).getPosition() == animSpriteWithAnim1.getPosition());
	BOOST_CHECK(compoundSprite->getAnimatedComponent(1).getPosition() == animSpriteWithAnim2.getPosition());


	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSprites_Empty_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	BOOST_CHECK(compoundSprite->isEmpty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_getter


BOOST_AUTO_TEST_SUITE(CompoundSprite_add)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	std::size_t index = compoundSprite->addComponent(sprite);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 1);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// check that the sprite has the correct values by checking position
	BOOST_CHECK(compoundSprite->getSpriteComponent(index).getPosition() == sprite.getPosition());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_returns_correct_index, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	std::size_t index = compoundSprite->addComponent(sprite);
	std::size_t index2 = compoundSprite->addComponent(sprite2);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// check that the sprite has the correct values by checking position
	BOOST_CHECK(compoundSprite->getSpriteComponent(index).getPosition() == sprite.getPosition());
	BOOST_CHECK(compoundSprite->getSpriteComponent(index2).getPosition() == sprite2.getPosition());

	// check that the indicies are correct
	BOOST_CHECK(index == 0);
	BOOST_CHECK(index2 == 1);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite_returns_correct_index, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	std::size_t index = compoundSprite->addComponent(animSpriteWithAnim1);
	std::size_t index2 = compoundSprite->addComponent(animSpriteWithAnim2);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 2);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// check that the sprite has the correct values by checking position
	BOOST_CHECK(compoundSprite->getAnimatedComponent(index).getPosition() == animSpriteWithAnim1.getPosition());
	BOOST_CHECK(compoundSprite->getAnimatedComponent(index2).getPosition() == animSpriteWithAnim2.getPosition());

	// check that the indicies are correct
	BOOST_CHECK(index == 0);
	BOOST_CHECK(index2 == 1);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite_and_sprite_returns_correct_index, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	std::size_t animIndex = compoundSprite->addComponent(animSpriteWithAnim1);
	std::size_t animIndex2 = compoundSprite->addComponent(animSpriteWithAnim2);
	std::size_t index = compoundSprite->addComponent(sprite);
	std::size_t index2 = compoundSprite->addComponent(sprite2);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 2);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// check that the animated sprite has the correct values by checking position
	BOOST_CHECK(compoundSprite->getAnimatedComponent(animIndex).getPosition() == animSpriteWithAnim1.getPosition());
	BOOST_CHECK(compoundSprite->getAnimatedComponent(animIndex2).getPosition() == animSpriteWithAnim2.getPosition());

	// check that the sprite has the correct values by checking position
	BOOST_CHECK(compoundSprite->getSpriteComponent(index).getPosition() == sprite.getPosition());
	BOOST_CHECK(compoundSprite->getSpriteComponent(index2).getPosition() == sprite2.getPosition());

	// check that the indicies are correct
	BOOST_CHECK(index == 0);
	BOOST_CHECK(index2 == 1);	
	BOOST_CHECK(animIndex == 0);
	BOOST_CHECK(animIndex2 == 1);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	std::size_t index = compoundSprite->addComponent(animSpriteWithAnim1);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 1);
	BOOST_CHECK(compoundSprite->isEmpty() == false);

	// check that the sprite has the correct values by checking position
	BOOST_CHECK(compoundSprite->getAnimatedComponent(index).getPosition() == animSpriteWithAnim1.getPosition());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_add


BOOST_AUTO_TEST_SUITE(CompoundSprite_remove)

// Test that adding and then removing a single component results in an empty CompoundSprite
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	auto index = compoundSprite->addComponent(sprite);
	compoundSprite->removeSpriteComponent(index);

	BOOST_CHECK(compoundSprite->isEmpty());
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);

	delete compoundSprite;
}

// Test that when removing an animated sprite the correct sprite is removed.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_AnimatedSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	auto animIndex1 = compoundSprite->addComponent(animSpriteWithAnim1);
	auto animIndex2 = compoundSprite->addComponent(animSpriteWithAnim2);
	compoundSprite->removeAnimatedComponent(animIndex1);

	//Ensure that the compound sprite correctly removed the selected sprite
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 1);
	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getAnimatedComponent(0).getPosition() == animSpriteWithAnim2.getPosition());

	delete compoundSprite;
}

// Test that removing a sprite with an out of bounds index throws
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_out_of_bounds_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(animSpriteWithAnim1);
	BOOST_CHECK_THROW(compoundSprite->removeAnimatedComponent(2), std::out_of_range);
	BOOST_CHECK_THROW(compoundSprite->removeSpriteComponent(2), std::out_of_range);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addComponent(sprite);
	compoundSprite->addComponent(animSpriteWithAnim1);
	compoundSprite->addComponent(animSpriteWithAnim2);

	compoundSprite->clearComponents();

	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == true);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->clearComponents();

	BOOST_CHECK(compoundSprite->getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite->getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite->isEmpty() == true);

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_remove


BOOST_AUTO_TEST_SUITE(CompoundSprite_operations)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_update, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();
	compoundSprite->addComponent(animSpriteWithAnim1);
	compoundSprite->addComponent(animSpriteWithAnim2);

	for (std::size_t i = 0; i < compoundSprite->getAnimatedComponentCount(); i++) {
		compoundSprite->getAnimatedComponent(i).runAnimation(0);
	}

	compoundSprite->update(2);

	for (std::size_t i = 0; i < compoundSprite->getAnimatedComponentCount(); i++) {
		BOOST_CHECK(compoundSprite->getAnimatedComponent(i).getCurrentFrame() == 1);
	}

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_scale, ReusableObjects) {

	std::vector<sf::Sprite> spriteVec = { sprite };
	std::vector<AnimatedSprite> animSpriteVec = { animSpriteWithAnim1, animSpriteWithAnim2 };
	CompoundSprite* compoundSprite = new CompoundSprite(spriteVec, animSpriteVec);
	const float X_SCALE_FACTOR = 0.1f;
	const float Y_SCALE_FACTOR = 0.2f;

	compoundSprite->scale(X_SCALE_FACTOR, Y_SCALE_FACTOR);

	//ensure all sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite->getSpriteComponentCount(); i++)
	{
		auto& sprite = compoundSprite->getSpriteComponent(i);
		BOOST_CHECK(sprite.getScale().x == X_SCALE_FACTOR);
		BOOST_CHECK(sprite.getScale().y == Y_SCALE_FACTOR);
	}

	//ensure all animated sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite->getAnimatedComponentCount(); i++)
	{
		auto& animSprite = compoundSprite->getAnimatedComponent(i);
		BOOST_CHECK(animSprite.getScale().x == X_SCALE_FACTOR);
		BOOST_CHECK(animSprite.getScale().y == Y_SCALE_FACTOR);
	}

	delete compoundSprite;
}

// Test that setting the scale of a compound sprite scales all of its component sprites
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setScale_Two_Inputs, ReusableObjectsForOperations) {
	const float SCALE_FACTOR_X = 0.123f;
	const float SCALE_FACTOR_Y = 0.234f;
	compoundSprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);

	//ensure all sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(temp.getScale().x == SCALE_FACTOR_X);
		BOOST_CHECK(temp.getScale().y == SCALE_FACTOR_Y);
	}

	//ensure all animated sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK(temp.getScale().x == SCALE_FACTOR_X);
		BOOST_CHECK(temp.getScale().y == SCALE_FACTOR_Y);
	}
}

// Test that setting the scale of the compound sprite sets the scale of all of its component sprites
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setScale_One_Input, ReusableObjectsForOperations) {
	const float SCALE_FACTOR_X = 0.123f;
	const float SCALE_FACTOR_Y = 0.234f;
	const sf::Vector2f SCALE_FACTOR{ SCALE_FACTOR_X, SCALE_FACTOR_Y };
	compoundSprite.setScale(SCALE_FACTOR);

	//ensure all sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(temp.getScale().x == SCALE_FACTOR_X);
		BOOST_CHECK(temp.getScale().y == SCALE_FACTOR_Y);
	}

	//ensure all animated sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK(temp.getScale().x == SCALE_FACTOR_X);
		BOOST_CHECK(temp.getScale().y == SCALE_FACTOR_Y);
	}
}

// Tests that scaling the compound sprite scales all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Scale_Point2D, ReusableObjects) {
	std::vector<sf::Sprite> sprites{ sprite };
	std::vector<AnimatedSprite> animSprites{ animSpriteWithAnim1, animSpriteWithAnim2 };
	const sf::Vector2f SCALE{0.5f, 0.6f};
	CompoundSprite compoundSprite(sprites, animSprites);
	compoundSprite.scale(SCALE);

	//ensure all sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(temp.getScale().x == SCALE.x);
		BOOST_CHECK(temp.getScale().y == SCALE.y);
	}

	//ensure all animated sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK(temp.getScale().x == SCALE.x);
		BOOST_CHECK(temp.getScale().y == SCALE.y);
	}
}

// Tests that rotating a compound sprite rotates all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_rotate_rotate_from_zero, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	compoundSprite.rotate(ROTATION);

	//ensure all sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), ROTATION);

	}
	//ensure all animated sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), ROTATION);
	}
}

// Test that applying a rotation to a compound sprite is cumulative.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Rotate_Additive_Rotate, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	const unsigned int NUM_ROTATIONS = 2;

	for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
		compoundSprite.rotate(ROTATION);
	}

	//ensure all sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), NUM_ROTATIONS * ROTATION);

	}
	//ensure all animated sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), NUM_ROTATIONS * ROTATION);
	}
}

// Test that setting the rotation of a compound sprite sets the rotation for all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotation_rotate_from_zero, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	compoundSprite.setRotation(ROTATION);

	//ensure all sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), ROTATION);

	}
	//ensure all animated sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), ROTATION);
	}
}

// Test that setting a rotation to a compound sprite is not cumulative.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotation_NonAdditive_Rotate, ReusableObjectsForOperations) {
	const float ROTATION = 10;
	const unsigned int NUM_ROTATIONS = 2;

	for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
		compoundSprite.setRotation(ROTATION);
	}
	//ensure all sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), ROTATION);
	}
	//ensure all animated sprites got the correct rotation
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK_EQUAL(temp.getRotation(), ROTATION);
	}
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_move, ReusableObjectsForOperations) {
	
	const float X_OFFSET = 500.6f;
	const float Y_OFFSET = 100.2f;

	compoundSprite.move(X_OFFSET, Y_OFFSET);

	//ensure all sprites got the correct position
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().x, X_OFFSET, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().y, Y_OFFSET, 1.0f);

	}
	//ensure all animated sprites got the correct position
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().x, X_OFFSET, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().y, Y_OFFSET, 1.0f);
	}
}

// Test that moving a compound sprite correctly moves all of its components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_move_Vector2f, ReusableObjectsForOperations) {
	const sf::Vector2f OFFSET(213.456f, 456.123f);

	compoundSprite.move(OFFSET);

	//ensure all sprites got the correct position 
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().x, OFFSET.x, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().y, OFFSET.y, 1.0f);

	}
	//ensure all animated sprites got the correct position
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().x, OFFSET.x, 1.0f);
		BOOST_CHECK_CLOSE_FRACTION(temp.getPosition().y, OFFSET.y, 1.0f);
	}
}

// Test that setting the position of the compound sprite correctly sets the position of all of the members
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Vector2f, ReusableObjectsForOperations) {
	const float POSITION_X = 123.456f;
	const float POSITION_Y = 654.321f;
	const sf::Vector2f POSITION(POSITION_X, POSITION_Y);

	// store the old positions
	std::vector<sf::Vector2f> oldPositions;

	// store the old positions
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		oldPositions.push_back(temp.getPosition());

	}
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		oldPositions.push_back(temp.getPosition());
	}

	compoundSprite.setPosition(POSITION);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

	// ensure the new positions are correct
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(temp.getPosition().x == POSITION_X + oldPositions[i].x && temp.getPosition().y == POSITION_Y + oldPositions[i].y);

	}
	for (std::size_t i = compoundSprite.getSpriteComponentCount(); i < compoundSprite.getAnimatedComponentCount() + compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i - compoundSprite.getSpriteComponentCount());
		BOOST_CHECK(temp.getPosition().x == POSITION_X + oldPositions[i].x && temp.getPosition().y == POSITION_Y + oldPositions[i].y);
	}
}

// Test that setting the position of the compound sprite to its current position does nothing
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Current_Position_Vector2f, ReusableObjectsForOperations) {
	const float POSITION_X = 0;
	const float POSITION_Y = 0;
	const sf::Vector2f POSITION(POSITION_X, POSITION_Y);

	// store the old positions
	std::vector<sf::Vector2f> oldPositions;

	// store the old positions
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		oldPositions.push_back(temp.getPosition());

	}
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		oldPositions.push_back(temp.getPosition());
	}

	compoundSprite.setPosition(POSITION);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

	// ensure the new positions are correct
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(temp.getPosition().x == oldPositions[i].x && temp.getPosition().y == oldPositions[i].y);

	}
	for (std::size_t i = compoundSprite.getSpriteComponentCount(); i < compoundSprite.getAnimatedComponentCount() + compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i - compoundSprite.getSpriteComponentCount());
		BOOST_CHECK(temp.getPosition().x == oldPositions[i].x && temp.getPosition().y == oldPositions[i].y);
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
	CompoundSprite compoundSprite = CompoundSprite{ {sprite}, {animSpriteWithAnim1, animSpriteWithAnim2}, STARTING_POS };

	// store the old positions
	std::vector<sf::Vector2f> oldPositions;

	// store the old positions
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		oldPositions.push_back(temp.getPosition());

	}
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		oldPositions.push_back(temp.getPosition());
	}

	compoundSprite.setPosition(POSITION);

	// ensure the new positions are correct
	BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_CLOSE(temp.getPosition().x, (POSITION_X - STARTING_X) + oldPositions[i].x, 0.001);
		BOOST_CHECK_CLOSE(temp.getPosition().y, (POSITION_Y - STARTING_Y) + oldPositions[i].y, 0.001);

	}
	for (std::size_t i = compoundSprite.getSpriteComponentCount(); i < compoundSprite.getAnimatedComponentCount() + compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i - compoundSprite.getSpriteComponentCount());
		BOOST_CHECK_CLOSE(temp.getPosition().x, (POSITION_X - STARTING_X) + oldPositions[i].x, 0.001);
		BOOST_CHECK_CLOSE(temp.getPosition().y, (POSITION_Y - STARTING_Y) + oldPositions[i].y, 0.001);
	}
}

// Test that setting the position of the compound sprite correctly sets the position of all of the members
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Two_Floats, ReusableObjectsForOperations) {
	const float POSITION_X = 123.456f;
	const float POSITION_Y = 654.321f;

	// store the old positions
	std::vector<sf::Vector2f> oldPositions;

	// store the old positions
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		oldPositions.push_back(temp.getPosition());

	}
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		oldPositions.push_back(temp.getPosition());
	}

	compoundSprite.setPosition(POSITION_X, POSITION_Y);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_CLOSE(temp.getPosition().x, (POSITION_X) + oldPositions[i].x, 0.001);
		BOOST_CHECK_CLOSE(temp.getPosition().y, (POSITION_Y) + oldPositions[i].y, 0.001);

	}
	for (std::size_t i = compoundSprite.getSpriteComponentCount(); i < compoundSprite.getAnimatedComponentCount() + compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i - compoundSprite.getSpriteComponentCount());
		BOOST_CHECK_CLOSE(temp.getPosition().x, (POSITION_X) + oldPositions[i].x, 0.001);
		BOOST_CHECK_CLOSE(temp.getPosition().y, (POSITION_Y) + oldPositions[i].y, 0.001);
	}

}

// Test that setting the position of the compound sprite to its current position does nothing
BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Current_Position_Two_Floats, ReusableObjectsForOperations) {
	const float POSITION_X = 0;
	const float POSITION_Y = 0;

	// store the old positions
	std::vector<sf::Vector2f> oldPositions;

	// store the old positions
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		oldPositions.push_back(temp.getPosition());

	}
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		oldPositions.push_back(temp.getPosition());
	}

	compoundSprite.setPosition(POSITION_X, POSITION_Y);

	// ensure that all components maintain their position relative to the new position of the compound sprite
	BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

	// ensure the new positions are correct
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(temp.getPosition().x == oldPositions[i].x && temp.getPosition().y == oldPositions[i].y);

	}
	for (std::size_t i = compoundSprite.getSpriteComponentCount(); i < compoundSprite.getAnimatedComponentCount() + compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i - compoundSprite.getSpriteComponentCount());
		BOOST_CHECK(temp.getPosition().x == oldPositions[i].x && temp.getPosition().y == oldPositions[i].y);
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
	CompoundSprite compoundSprite = CompoundSprite{ { sprite} , {animSpriteWithAnim1, animSpriteWithAnim2 }, STARTING_POS };
	// store the old positions
	std::vector<sf::Vector2f> oldPositions;
	// store the old positions
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		oldPositions.push_back(temp.getPosition());

	}
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i);
		oldPositions.push_back(temp.getPosition());
	}

	compoundSprite.setPosition(POSITION_X, POSITION_Y);


	// ensure the new positions are correct
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK_CLOSE(temp.getPosition().x, (POSITION_X - STARTING_X) + oldPositions[i].x, 0.001);
		BOOST_CHECK_CLOSE(temp.getPosition().y, (POSITION_Y - STARTING_Y) + oldPositions[i].y, 0.001);

	}
	for (std::size_t i = compoundSprite.getSpriteComponentCount(); i < compoundSprite.getAnimatedComponentCount() + compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& temp = compoundSprite.getAnimatedComponent(i - compoundSprite.getSpriteComponentCount());
		BOOST_CHECK_CLOSE(temp.getPosition().x, (POSITION_X - STARTING_X) + oldPositions[i].x, 0.001);
		BOOST_CHECK_CLOSE(temp.getPosition().y, (POSITION_Y - STARTING_Y) + oldPositions[i].y, 0.001);
	}
}


BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_operations

BOOST_AUTO_TEST_SUITE_END() // END CompoundSpriteTests