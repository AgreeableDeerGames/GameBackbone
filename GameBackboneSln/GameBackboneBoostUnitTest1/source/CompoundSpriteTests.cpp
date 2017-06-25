#include <Backbone/AnimatedSprite.h>
#include <Backbone/CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <boost/test/unit_test.hpp>

#include <string>

using namespace GB;


BOOST_AUTO_TEST_SUITE(CompoundSpriteTests)

struct ReusableObjects
{
	ReusableObjects() {
		aSpriteTexture = new sf::Texture();
		std::string testTexturePath = "..\\..\\Textures\\testSprite.png";
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

BOOST_AUTO_TEST_SUITE(CompoundSprite_ctr)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_default_ctr, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getSfSprites()->empty());
	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addAnimatedSprite_ctr, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	for (unsigned int i = 0; i < spriteVector.size(); ++i) {
		BOOST_CHECK(compoundSprite->getSfSprites()->at(i) == spriteVector[i]);
	}

	for (unsigned int i = 0; i < emptyAnimatedSpriteVector.size(); ++i) {
		BOOST_CHECK(compoundSprite->getAnimatedSprites()->at(i) == emptyAnimatedSpriteVector[i]);
	}

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_ctr

BOOST_AUTO_TEST_SUITE(CompoundSprite_getter)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSfSprites_Populated_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);
	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);
	
	BOOST_CHECK(compoundSprite->getSfSprites()->size() == 1);
	BOOST_CHECK(compoundSprite->getSfSprites()->at(0) == sprite);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSfSprites_Populated_Sprite_Vector, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	spriteVector.push_back(sprite);
	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	BOOST_CHECK(compoundSprite->getSfSprites()->size() == 1);
	BOOST_CHECK(compoundSprite->getSfSprites()->at(0) == sprite);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSfSprites_Populated_Animated_Vector, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> animatedSpriteVector;

	animatedSpriteVector.push_back(animSpriteWithAnim1);

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, animatedSpriteVector);

	BOOST_CHECK(compoundSprite->getSfSprites()->size() == 0);

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSfSprites_Empty_Input_Vectors, ReusableObjects) {
	std::vector<sf::Sprite*> spriteVector;
	std::vector<AnimatedSprite*> emptyAnimatedSpriteVector;

	CompoundSprite* compoundSprite = new CompoundSprite(spriteVector, emptyAnimatedSpriteVector);

	BOOST_CHECK(compoundSprite->getSfSprites()->empty());
	
	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getSfSprites_default_ctr, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getSfSprites()->empty());

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

BOOST_FIXTURE_TEST_CASE(CompoundSprite_getAnimatedSprites_default_ctr, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	BOOST_CHECK(compoundSprite->getAnimatedSprites()->empty());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_getter


BOOST_AUTO_TEST_SUITE(CompoundSprite_add)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addSprite(sprite);
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getSfSprites();

	auto it = std::find(spriteVector->begin(), spriteVector->end(), sprite);
	BOOST_CHECK(it != spriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addAnimatedSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addAnimatedSprite(animSpriteWithAnim1);
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	auto it = std::find(animatedSpriteVector->begin(), animatedSpriteVector->end(), animSpriteWithAnim1);
	BOOST_CHECK(it != animatedSpriteVector->end());

	delete compoundSprite;
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_add


BOOST_AUTO_TEST_SUITE(CompoundSprite_remove)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addSprite(sprite);
	compoundSprite->removeSprite(sprite);
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getSfSprites();

	BOOST_CHECK(spriteVector->empty());

	auto it = std::find(spriteVector->begin(), spriteVector->end(), sprite);
	BOOST_CHECK(it == spriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->removeSprite(sprite);
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getSfSprites();

	BOOST_CHECK(spriteVector->empty());

	auto it = std::find(spriteVector->begin(), spriteVector->end(), sprite);
	BOOST_CHECK(it == spriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeAnimatedSprite, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addAnimatedSprite(animSpriteWithAnim1);
	compoundSprite->removeAnimatedSprite(animSpriteWithAnim1);
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	BOOST_CHECK(animatedSpriteVector->empty());
	auto it = std::find(animatedSpriteVector->begin(), animatedSpriteVector->end(), animSpriteWithAnim1);
	BOOST_CHECK(it == animatedSpriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeAnimatedSprite_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();
	
	compoundSprite->removeSprite(sprite);
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	BOOST_CHECK(animatedSpriteVector->empty());
	auto it = std::find(animatedSpriteVector->begin(), animatedSpriteVector->end(), animSpriteWithAnim1);
	BOOST_CHECK(it == animatedSpriteVector->end());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->addSprite(sprite);
	compoundSprite->addAnimatedSprite(animSpriteWithAnim1);
	compoundSprite->addAnimatedSprite(animSpriteWithAnim2);

	compoundSprite->clearComponents();
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getSfSprites();
	std::vector<AnimatedSprite*> *animatedSpriteVector = compoundSprite->getAnimatedSprites();

	BOOST_CHECK(spriteVector->empty());
	BOOST_CHECK(animatedSpriteVector->empty());

	delete compoundSprite;
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents_empty, ReusableObjects) {
	CompoundSprite* compoundSprite = new CompoundSprite();

	compoundSprite->clearComponents();
	std::vector<sf::Sprite*> *spriteVector = compoundSprite->getSfSprites();
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
	std::string testTexturePath = "..\\..\\Textures\\testSprite.png";
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
	for (sf::Sprite* sprite : *(compoundSprite->getSfSprites()))
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

BOOST_AUTO_TEST_CASE(CompoundSprite_move) {
	//for some reason cant use reusable objects. recreate them here.
	sf::Texture* aSpriteTexture = new sf::Texture();
	std::string testTexturePath = "..\\..\\Textures\\testSprite.png";
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
	for (sf::Sprite* sprite : *(compoundSprite->getSfSprites()))
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

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_opertaions

BOOST_AUTO_TEST_SUITE_END() // END CompoundSpriteTests