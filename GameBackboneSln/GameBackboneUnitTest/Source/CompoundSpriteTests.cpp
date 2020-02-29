#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <string>

using namespace GB;

BOOST_AUTO_TEST_SUITE(CompoundSpriteTests)
/*
struct ReusableObjects
{
	ReusableObjects() {
		std::string testTexturePath = "Textures/testSprite.png";
		aSpriteTexture.loadFromFile(testTexturePath);

		sprite = sf::Sprite(aSpriteTexture);
		sprite.setPosition(1,1);

		sprite2 = sf::Sprite(aSpriteTexture);
		sprite2.setPosition(2,2);

		int halfTextureWidth = aSpriteTexture.getSize().x / 2;
		int textureHeight = aSpriteTexture.getSize().y;

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

		animSpriteWithAnim1 = AnimatedSprite(aSpriteTexture, animSet1);
		animSpriteWithAnim1.setPosition(10, 10);
		animSpriteWithAnim2 = AnimatedSprite(aSpriteTexture, animSet2);
		animSpriteWithAnim2.setPosition(20, 20);
	}
	~ReusableObjects() {}

	AnimatedSprite animSpriteWithAnim1;
	AnimatedSprite animSpriteWithAnim2;
	AnimationSet::Ptr animSet1;
	AnimationSet::Ptr animSet2;
	sf::Texture aSpriteTexture;
	sf::Sprite tempsprite;
	sf::Sprite sprite2;
	sf::Sprite sprite;
};

struct ReusableObjectsForOperations : ReusableObjects {

	ReusableObjectsForOperations() : compoundSprite(sprite, sprite2, animSpriteWithAnim1, animSpriteWithAnim2)
	{
	}

	CompoundSprite compoundSprite;
};


BOOST_AUTO_TEST_SUITE(CompoundSprite_CTR)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_VariadicCtr_Sprite, ReusableObjects) {
	CompoundSprite compoundSprite{ sprite };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_VariadicCtr_AnimatedSprite, ReusableObjects) {
	CompoundSprite compoundSprite{ animSpriteWithAnim1 };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_VariadicCtr_RectangleShape, ReusableObjects) {
	CompoundSprite compoundSprite{ sf::RectangleShape{} };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_VariadicCtr_TwoTypes, ReusableObjects) {
	CompoundSprite compoundSprite{ sprite, animSpriteWithAnim1 };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 2);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_VariadicCtr_FourTypes, ReusableObjects) {
	CompoundSprite compoundSprite{ sprite, animSpriteWithAnim1, sf::RectangleShape{}, CompoundSprite{} };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 4);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_VariadicPositionCtr, ReusableObjects)
{
	CompoundSprite compoundSprite{ sf::Vector2f{10.0f, 10.0f}, sprite, animSpriteWithAnim1 };

	BOOST_CHECK(compoundSprite.getPosition().x == 10.0f);
	BOOST_CHECK(compoundSprite.getPosition().y == 10.0f);
	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 2);
}

class dummy : public sf::Drawable, public sf::Transformable {
public:
	int& m_copies;
	int& m_moves;

	dummy(int& copies, int& moves) : m_copies(copies), m_moves(moves) {}

	dummy(const dummy& other) : m_copies(other.m_copies), m_moves(other.m_moves)
	{
		m_copies++;
	}
	dummy& operator=(const dummy& other)
	{
		dummy tempOther{ other.m_copies, other.m_moves };
		*this = std::move(tempOther);
		m_copies++;
		return *this;
	}
	dummy(dummy&& other) noexcept : m_copies(other.m_copies), m_moves(other.m_moves)
	{
		m_moves++;
	}
	dummy& operator=(dummy&& other) noexcept
	{
		this->m_copies = other.m_copies;
		this->m_moves = other.m_moves;
		m_moves++;
		return *this;
	}


protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};

BOOST_AUTO_TEST_CASE(CompoundSprite_VariadicCtr_NoCopies)
{
	int copies = 0;
	int moves = 0;
	dummy dummy1{ copies , moves };
	CompoundSprite compoundSprite{ std::move(dummy1) };

	BOOST_CHECK(copies == 0);
	BOOST_CHECK(moves == 5);
}

BOOST_AUTO_TEST_CASE(CompoundSprite_VariadicCtr_OneCopies)
{
	int copies = 0;
	int moves = 0;
	dummy dummy1{ copies , moves };
	CompoundSprite compoundSprite{ dummy1 };

	BOOST_CHECK(copies == 1);
	BOOST_CHECK(moves == 4);
}

BOOST_AUTO_TEST_CASE(CompundSprite_CopyCtr_DoesCopyConstruction)
{
	CompoundSprite compoundSprite{};
	CompoundSprite compoundSprite2(compoundSprite);
	CompoundSprite compoundSprite3{ compoundSprite };
	BOOST_CHECK(compoundSprite2.getComponentCount() == 0);
	BOOST_CHECK(compoundSprite3.getComponentCount() == 0);
}

BOOST_AUTO_TEST_CASE(CompundSprite_CopyCtr_ClonesComponents)
{
	int copies = 0;
	int moves = 0;
	dummy dummy1{ copies , moves };
	CompoundSprite compoundSprite{ std::move(dummy1) };
	CompoundSprite compoundSprite2(compoundSprite);
	BOOST_CHECK(copies == 1);
}

BOOST_AUTO_TEST_CASE(CompundSprite_MoveCtr_DoesCopyConstruction)
{
	CompoundSprite compoundSprite{};
	CompoundSprite compoundSprite2(std::move(compoundSprite));
	CompoundSprite compoundSprite3{ std::move(compoundSprite) };
	BOOST_CHECK(compoundSprite2.getComponentCount() == 0);
	BOOST_CHECK(compoundSprite3.getComponentCount() == 0);
}

BOOST_AUTO_TEST_CASE(CompundSprite_MoveCtr_DoesNotCloneComponents)
{
	int copies = 0;
	int moves = 0;
	dummy dummy1{ copies , moves };
	CompoundSprite compoundSprite{ std::move(dummy1) };
	CompoundSprite compoundSprite2(std::move(compoundSprite));
	BOOST_CHECK(copies == 0);
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_CTR

BOOST_AUTO_TEST_SUITE(CompoundSprite_addComponent)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_Sprite, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(sprite);

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(animSpriteWithAnim1);

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_RectangleShape, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(sf::RectangleShape{});

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_CompoundSprite, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(CompoundSprite{});

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_Return, ReusableObjects) {
	CompoundSprite compoundSprite{};
	sprite.setColor(sf::Color::Red);
	auto& returnRef = compoundSprite.addComponent(sprite);

	BOOST_CHECK(returnRef.getColor() == sprite.getColor());
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_addComponent


BOOST_AUTO_TEST_SUITE(CompoundSprite_SFINAETests)

// SFINAE types for checking if CompoundSprite can be constructed with given inputs
template <class, class = std::void_t<> >
struct CanConstructCompoundSprite : std::false_type {};

template <class T>
struct CanConstructCompoundSprite <
	T,
	std::void_t<
	decltype(CompoundSprite(std::declval<T>()))
	>
> : std::true_type {};

template <class T>
inline constexpr bool CanConstructCompoundSprite_v = CanConstructCompoundSprite<T>::value;

BOOST_AUTO_TEST_CASE(SFINAE_CanConstruct_Sprite)
{
	BOOST_CHECK(CanConstructCompoundSprite_v<sf::Sprite>);
}

BOOST_AUTO_TEST_CASE(SFINAE_CanConstruct_AnimatedSprite)
{
	BOOST_CHECK(CanConstructCompoundSprite_v<GB::AnimatedSprite>);
}

BOOST_AUTO_TEST_CASE(SFINAE_CanConstruct_RectangleShape)
{
	BOOST_CHECK(CanConstructCompoundSprite_v<sf::RectangleShape>);
}

BOOST_AUTO_TEST_CASE(SFINAE_NOTCanConstruct_VertexBuffer)
{
	BOOST_CHECK(!CanConstructCompoundSprite_v<sf::VertexBuffer>);
}

BOOST_AUTO_TEST_CASE(SFINAE_NOTCanConstruct_VertexArray)
{
	BOOST_CHECK(!CanConstructCompoundSprite_v<sf::VertexArray>);
}

BOOST_AUTO_TEST_CASE(SFINAE_NOTCanConstruct_Transformable)
{
	BOOST_CHECK(!CanConstructCompoundSprite_v<sf::Transformable>);
}

// SFINAE types for checking if addComponent can be called with given inputs
template <class, class = std::void_t<> >
struct CanAddComponent : std::false_type {};

template <class T>
struct CanAddComponent <
	T,
	std::void_t<
	decltype(CompoundSprite{}.addComponent(std::declval<T>()))
	>
> : std::true_type {};

template <class T>
inline constexpr bool CanAddComponent_v = CanAddComponent<T>::value;

BOOST_AUTO_TEST_CASE(SFINAE_CanAddComponent_Sprite)
{
	BOOST_CHECK(CanAddComponent_v<sf::Sprite>);
}

BOOST_AUTO_TEST_CASE(SFINAE_CanAddComponent_AnimatedSprite)
{
	BOOST_CHECK(CanAddComponent_v<GB::AnimatedSprite>);
}

BOOST_AUTO_TEST_CASE(SFINAE_CanAddComponent_RectangleShape)
{
	BOOST_CHECK(CanAddComponent_v<sf::RectangleShape>);
}

BOOST_AUTO_TEST_CASE(SFINAE_NOTCanAddComponent_VertexBuffer)
{
	BOOST_CHECK(!CanAddComponent_v<sf::VertexBuffer>);
}

BOOST_AUTO_TEST_CASE(SFINAE_NOTCanAddComponent_VertexArray)
{
	BOOST_CHECK(!CanAddComponent_v<sf::VertexArray>);
}

BOOST_AUTO_TEST_CASE(SFINAE_NOTCanAddComponent_Transformable)
{
	BOOST_CHECK(!CanAddComponent_v<sf::Transformable>);
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_SFINAETests
*/
/*BOOST_AUTO_TEST_SUITE(CompoundSprite_CTR)

// Test that the default constructor initializes values to empty
BOOST_FIXTURE_TEST_CASE(CompoundSprite_default_CTR, ReusableObjects) {
	CompoundSprite compoundSprite;

	BOOST_CHECK(compoundSprite.isEmpty());
	BOOST_CHECK(compoundSprite.getComponentCount() == 0);
}

// Test that constructing a compound sprite with a single sprite input vector correctly sets its components and position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Single_Sprite_Vector_CTR, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector{ sprite, sprite2 };
	CompoundSprite compoundSprite(spriteVector);

	// ensure that the right number of components are found
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// ensure that the added components are correct
	
	// The position of each component becomes the position of the compound sprite
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); ++i){
		BOOST_CHECK(compoundSprite.getSpriteComponent(i).getPosition() == compoundSprite.getPosition());
	}

	// The origin of each component is the difference between the position of the compound sprite
	// and the position of the component at the time the component was added
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); ++i) {
		const auto& component = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - spriteVector[i].getPosition().x);
		BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - spriteVector[i].getPosition().y);
	}

	// Ensure that the correct number of components was added
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == spriteVector.size());

	// ensure that the position of the compound sprite is set correctly
	BOOST_CHECK(compoundSprite.getPosition().x == 0 && compoundSprite.getPosition().y == 0);
}

// Test that constructing a compound sprite with a single sprite input vector correctly sets its components and position
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Single_Sprite_Vector_setPosition_CTR, ReusableObjects) {
	const sf::Vector2f compoundSpritePos{ 3,3 };

	std::vector<sf::Sprite> spriteVector{ sprite, sprite2 };
	CompoundSprite compoundSprite(spriteVector, compoundSpritePos);

	// ensure that the right number of components are found
	BOOST_CHECK(compoundSprite.getComponentCount() == 2);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// ensure that the added components are correct

	// The position of each component becomes the position of the compound sprite
	for (std::size_t i = 0; i < compoundSprite.getComponentCount(); ++i) {
		BOOST_CHECK(compoundSprite.getSpriteComponent(i).getPosition() == compoundSprite.getPosition());
	}

	// The origin of each component is the difference between the position of the compound sprite
	// and the position of the component at the time the component was added
	for (std::size_t i = 0; i < compoundSprite.getComponentCount(); ++i) {
		const auto& component = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - spriteVector[i].getPosition().x);
		BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - spriteVector[i].getPosition().y);
	}

	// Ensure that the correct number of components was added
	BOOST_CHECK(compoundSprite.getComponentCount() == spriteVector.size());

	// Ensure the compound sprite is at the right position
	BOOST_CHECK(compoundSprite.getPosition() == compoundSpritePos);
}

// Test that constructing the CompundSprite with its components correctly sets the components
BOOST_FIXTURE_TEST_CASE(CompoundSprite_Sprite_And_AnimatedSprite_Vectors_CTR, ReusableObjects) {
	std::vector<sf::Sprite> spriteVector{sprite, sprite2};
	std::vector<AnimatedSprite> animatedSpriteVector{animSpriteWithAnim1, animSpriteWithAnim2};

	CompoundSprite compoundSprite(spriteVector, animatedSpriteVector);

	// The position of each component becomes the position of the compound sprite
	for (std::size_t i = 0; i < compoundSprite.getComponentCount(); ++i) {
		BOOST_CHECK(compoundSprite.getSpriteComponent(i).getPosition() == compoundSprite.getPosition());
	}

	// The position of each component becomes the position of the compound sprite
	for (std::size_t i = 0; i < compoundSprite.getComponentCount(); ++i) {
		BOOST_CHECK(compoundSprite.getAnimatedComponent(i).getPosition() == compoundSprite.getPosition());
	}

	// The origin of each component is the difference between the position of the compound sprite
	// and the position of the component at the time the component was added
	for (std::size_t i = 0; i < compoundSprite.getComponentCount(); ++i) {
		const auto& component = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - spriteVector[i].getPosition().x);
		BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - spriteVector[i].getPosition().y);
	}
	for (std::size_t i = 0; i < compoundSprite.getComponentCount(); ++i) {
		const auto& component = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - animatedSpriteVector[i].getPosition().x);
		BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - animatedSpriteVector[i].getPosition().y);
	}

	// Ensure that the correct number of components was added
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == spriteVector.size());
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == animatedSpriteVector.size());

	// check that the initial position is set correctly.
	BOOST_CHECK(compoundSprite.getPosition().x == 0 && compoundSprite.getPosition().y == 0);
}

// Test that the CompoundSprite is safe to construct with empty component vectors.
BOOST_AUTO_TEST_CASE(CompoundSprite_Empty_Component_Vector_CTR) {
	std::vector<sf::Sprite> spriteVector;
	std::vector<AnimatedSprite> animatedSpriteVector;
	CompoundSprite compoundSprite(spriteVector, animatedSpriteVector);

	//check that the component vectors are empty
	BOOST_CHECK(compoundSprite.getComponentCount() == 0);
	BOOST_CHECK(compoundSprite.isEmpty());
}

// Test that CompoundSprite correctly sets its position.
BOOST_AUTO_TEST_CASE(CompoundSprite_setPosition_CTR) {
	const sf::Vector2f compoundSpritePos{ 3,3 };

	CompoundSprite compoundSprite(compoundSpritePos);

	BOOST_CHECK(compoundSprite.getPosition().x == compoundSpritePos.x && compoundSprite.getPosition().y == compoundSpritePos.y);
	BOOST_CHECK(compoundSprite.isEmpty());
	BOOST_CHECK(compoundSprite.getComponentCount() == 0);
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_CTR

BOOST_AUTO_TEST_SUITE(CompoundSprite_add)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent, ReusableObjects) {
	CompoundSprite compoundSprite;

	std::size_t index = compoundSprite.addComponent(sprite);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// check that the sprite has the correct values by checking position
	const auto& component = compoundSprite.getSpriteComponent(index);
	BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - sprite.getPosition().x);
	BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - sprite.getPosition().y);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_returns_correct_index, ReusableObjects) {
	CompoundSprite compoundSprite;

	std::size_t index = compoundSprite.addComponent(sprite);
	std::size_t index2 = compoundSprite.addComponent(sprite2);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// check that the indices are correct
	BOOST_CHECK(index == 0);
	BOOST_CHECK(index2 == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite_returns_correct_index, ReusableObjects) {
	CompoundSprite compoundSprite;

	std::size_t index = compoundSprite.addComponent(animSpriteWithAnim1);
	std::size_t index2 = compoundSprite.addComponent(animSpriteWithAnim2);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 2);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// check that the indices are correct
	BOOST_CHECK(index == 0);
	BOOST_CHECK(index2 == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite_and_sprite_returns_correct_index, ReusableObjects) {
	CompoundSprite compoundSprite;

	std::size_t animIndex = compoundSprite.addComponent(animSpriteWithAnim1);
	std::size_t animIndex2 = compoundSprite.addComponent(animSpriteWithAnim2);
	std::size_t index = compoundSprite.addComponent(sprite);
	std::size_t index2 = compoundSprite.addComponent(sprite2);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 2);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 2);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// check that the indices are correct
	BOOST_CHECK(index == 0);
	BOOST_CHECK(index2 == 1);	
	BOOST_CHECK(animIndex == 0);
	BOOST_CHECK(animIndex2 == 1);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_addComponent_AnimatedSprite, ReusableObjects) {
	CompoundSprite compoundSprite;

	std::size_t index = compoundSprite.addComponent(animSpriteWithAnim1);

	// ensure that the correct number of sprites has been added
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 1);
	BOOST_CHECK(compoundSprite.isEmpty() == false);

	// check that the sprite has the correct values by checking position
	const auto& component = compoundSprite.getAnimatedComponent(index);
	BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - animSpriteWithAnim1.getPosition().x);
	BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - animSpriteWithAnim1.getPosition().y);
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_add


BOOST_AUTO_TEST_SUITE(CompoundSprite_remove)

// Test that adding and then removing a single component results in an empty CompoundSprite
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite, ReusableObjects) {
	CompoundSprite compoundSprite;

	auto index = compoundSprite.addComponent(sprite);
	compoundSprite.removeSpriteComponent(index);

	BOOST_CHECK(compoundSprite.isEmpty());
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
}

// Test that when removing an animated sprite the correct sprite is removed.
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_AnimatedSprite, ReusableObjects) {
	CompoundSprite compoundSprite;

	auto animIndex1 = compoundSprite.addComponent(animSpriteWithAnim1);
	compoundSprite.addComponent(animSpriteWithAnim2);
	compoundSprite.removeAnimatedComponent(animIndex1);

	//Ensure that the compound sprite correctly removed the selected sprite
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
	// check that the sprite has the correct values by checking position
	const auto& component = compoundSprite.getAnimatedComponent(0);
	BOOST_CHECK(component.getOrigin().x == compoundSprite.getPosition().x - animSpriteWithAnim2.getPosition().x);
	BOOST_CHECK(component.getOrigin().y == compoundSprite.getPosition().y - animSpriteWithAnim2.getPosition().y);
}

// Test that removing a sprite with an out of bounds index throws
BOOST_FIXTURE_TEST_CASE(CompoundSprite_removeSprite_out_of_bounds_empty, ReusableObjects) {
	CompoundSprite compoundSprite;

	compoundSprite.addComponent(animSpriteWithAnim1);
	BOOST_CHECK_THROW(compoundSprite.removeAnimatedComponent(2), std::out_of_range);
	BOOST_CHECK_THROW(compoundSprite.removeSpriteComponent(2), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents, ReusableObjects) {
	CompoundSprite compoundSprite;

	compoundSprite.addComponent(sprite);
	compoundSprite.addComponent(animSpriteWithAnim1);
	compoundSprite.addComponent(animSpriteWithAnim2);

	compoundSprite.clearComponents();

	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite.isEmpty() == true);
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_clearComponents_empty, ReusableObjects) {
	CompoundSprite compoundSprite;

	compoundSprite.clearComponents();

	BOOST_CHECK(compoundSprite.getSpriteComponentCount() == 0);
	BOOST_CHECK(compoundSprite.getAnimatedComponentCount() == 0);
	BOOST_CHECK(compoundSprite.isEmpty() == true);
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_remove


BOOST_AUTO_TEST_SUITE(CompoundSprite_operations)

BOOST_FIXTURE_TEST_CASE(CompoundSprite_update, ReusableObjects) {
	CompoundSprite compoundSprite;
	compoundSprite.addComponent(animSpriteWithAnim1);
	compoundSprite.addComponent(animSpriteWithAnim2);

	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++) {
		compoundSprite.getAnimatedComponent(i).runAnimation(0);
	}

	compoundSprite.update(2);

	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++) {
		BOOST_CHECK(compoundSprite.getAnimatedComponent(i).getCurrentFrame() == 1);
	}
}

BOOST_FIXTURE_TEST_CASE(CompoundSprite_scale, ReusableObjects) {

	std::vector<sf::Sprite> spriteVec = { sprite };
	std::vector<AnimatedSprite> animSpriteVec = { animSpriteWithAnim1, animSpriteWithAnim2 };
	CompoundSprite compoundSprite(spriteVec, animSpriteVec);
	const float X_SCALE_FACTOR = 0.1f;
	const float Y_SCALE_FACTOR = 0.2f;

	compoundSprite.scale(X_SCALE_FACTOR, Y_SCALE_FACTOR);

	//ensure all sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getSpriteComponentCount(); i++)
	{
		auto& testSprite = compoundSprite.getSpriteComponent(i);
		BOOST_CHECK(testSprite.getScale().x == X_SCALE_FACTOR);
		BOOST_CHECK(testSprite.getScale().y == Y_SCALE_FACTOR);
	}

	//ensure all animated sprites got the correct scale
	for (std::size_t i = 0; i < compoundSprite.getAnimatedComponentCount(); i++)
	{
		auto& animSprite = compoundSprite.getAnimatedComponent(i);
		BOOST_CHECK(animSprite.getScale().x == X_SCALE_FACTOR);
		BOOST_CHECK(animSprite.getScale().y == Y_SCALE_FACTOR);
	}
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


BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_operations*/

BOOST_AUTO_TEST_SUITE_END() // END CompoundSpriteTests