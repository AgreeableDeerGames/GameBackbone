#include "stdafx.h"

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/CompoundSprite.h>

#include <SFML/Graphics.hpp>

#include <string>
#include <type_traits>

using namespace GB;

BOOST_AUTO_TEST_SUITE(CompoundSpriteTests)

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

	ReusableObjectsForOperations() : compoundSprite(0, sprite, sprite2, animSpriteWithAnim1, animSpriteWithAnim2)
	{
	}

	CompoundSprite compoundSprite;
};

class MockDrawable_ForMoveCopyCounts : public sf::Drawable, public sf::Transformable {
public:
	int& m_copies;
	int& m_moves;

	MockDrawable_ForMoveCopyCounts(int& copies, int& moves) : m_copies(copies), m_moves(moves) {}

	MockDrawable_ForMoveCopyCounts(const MockDrawable_ForMoveCopyCounts& other)
		: m_copies(other.m_copies), m_moves(other.m_moves)
	{
		m_copies++;
	}
	MockDrawable_ForMoveCopyCounts& operator=(const MockDrawable_ForMoveCopyCounts& other)
	{
		MockDrawable_ForMoveCopyCounts tempOther{ other.m_copies, other.m_moves };
		*this = std::move(tempOther);
		m_copies++;
		return *this;
	}
	MockDrawable_ForMoveCopyCounts(MockDrawable_ForMoveCopyCounts&& other) noexcept
		: m_copies(other.m_copies), m_moves(other.m_moves)
	{
		m_moves++;
	}
	MockDrawable_ForMoveCopyCounts& operator=(MockDrawable_ForMoveCopyCounts&& other) noexcept
	{
		this->m_copies = other.m_copies;
		this->m_moves = other.m_moves;
		m_moves++;
		return *this;
	}


protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};

/* Name: areSpritesEquivalent
*  Description: Helper method used to determine if two sprites are the same for the purposes of test cases.
*		As designed this will test the color and transform of each sprite.
*  Inputs: Two sprites to be compared.
*  Ouput: True if equivalent / Flase if not.
*/
static bool areSpritesEquivalent(const sf::Sprite& lhs, const sf::Sprite& rhs)
{
	if (lhs.getColor() != rhs.getColor())
	{
		return false;
	}

	if (lhs.getTexture() != rhs.getTexture())
	{
		return false;
	}

	if (lhs.getTextureRect() != rhs.getTextureRect())
	{
		return false;
	}

	if (lhs.getTransform() != rhs.getTransform())
	{
		return false;
	}

	return true;
}

class ComponentWrapperTestHelper : public CompoundSprite::ComponentWrapper {
public: 	
	sf::Drawable& m_internalData;
	sf::Vector2f m_vec;
	sf::Transform m_transform;

	ComponentWrapperTestHelper(sf::Drawable& internalData) : m_internalData(internalData){}

	sf::Drawable& getDataAsDrawable() override
	{
		return m_internalData;
	}

	std::unique_ptr<ComponentWrapper> cloneAsUnique() override
	{
		return nullptr;
	}

	void setPosition(float x, float y) override {}
	void setPosition(const sf::Vector2f& position) override {}
	void setRotation(float angle) override {}
	void setScale(float factorX, float factorY) override {}
	void setScale(const sf::Vector2f& factors) override {}
	void setOrigin(float x, float y) override {}
	void setOrigin(const sf::Vector2f& origin) override {}
	const sf::Vector2f& getPosition() const override { return m_vec; }
	float getRotation() const override { return -1; }
	const sf::Vector2f& getScale() const override { return m_vec; }
	const sf::Vector2f& getOrigin() const override { return m_vec; }
	void move(float offsetX, float offsetY) override {}
	void move(const sf::Vector2f& offset) override {}
	void rotate(float angle) override {}
	void scale(float factorX, float factorY) override {}
	void scale(const sf::Vector2f& factor) override {}
	const sf::Transform& getTransform() const override { return m_transform; }
	const sf::Transform& getInverseTransform() const override { return m_transform; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
	void update(sf::Int64 elapsedTime) override {}
};

BOOST_AUTO_TEST_SUITE(CompoundSprite_CTR)

BOOST_FIXTURE_TEST_CASE(VariadicCtr_Sprite, ReusableObjects) {
	CompoundSprite compoundSprite{ 0,  sprite };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(VariadicCtr_AnimatedSprite, ReusableObjects) {
	CompoundSprite compoundSprite{ 0,  animSpriteWithAnim1 };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(VariadicCtr_RectangleShape, ReusableObjects) {
	CompoundSprite compoundSprite{ 0,  sf::RectangleShape{} };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(VariadicCtr_TwoTypes, ReusableObjects) {
	CompoundSprite compoundSprite{ 0,  sprite, animSpriteWithAnim1 };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 2);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 2);
}

BOOST_FIXTURE_TEST_CASE(VariadicCtr_FourTypes, ReusableObjects) {
	CompoundSprite compoundSprite{ 0,  sprite, animSpriteWithAnim1, sf::RectangleShape{}, CompoundSprite{} };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 4);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 4);
}

BOOST_FIXTURE_TEST_CASE(VariadicPositionCtr, ReusableObjects)
{
	CompoundSprite compoundSprite{ sf::Vector2f{10.0f, 10.0f}, 0, sprite, animSpriteWithAnim1 };

	BOOST_CHECK(compoundSprite.getPosition().x == 10.0f);
	BOOST_CHECK(compoundSprite.getPosition().y == 10.0f);
	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 2);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 2);
}

BOOST_AUTO_TEST_CASE(VariadicCtr_NoCopies)
{
	int copies = 0;
	int moves = 0;
	MockDrawable_ForMoveCopyCounts mock{ copies , moves };
	CompoundSprite compoundSprite{ 0,  std::move(mock) };

	BOOST_CHECK(copies == 0);
	BOOST_CHECK(moves == 5);
}

BOOST_AUTO_TEST_CASE(VariadicCtr_OneCopies)
{
	int copies = 0;
	int moves = 0;
	MockDrawable_ForMoveCopyCounts mock{ copies , moves };
	CompoundSprite compoundSprite{ 0,  mock };

	BOOST_CHECK(copies == 1);
}

BOOST_FIXTURE_TEST_CASE(CopyCtr_DoesCopyConstruction, ReusableObjects)
{
	CompoundSprite compoundSprite{ 0, sprite };
	CompoundSprite compoundSprite2{ compoundSprite };

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite2.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite2.getComponentCount(0) == 1);
}

BOOST_AUTO_TEST_CASE(CopyCtr_ClonesComponents)
{
	int copies = 0;
	int moves = 0;
	MockDrawable_ForMoveCopyCounts mock{ copies , moves };
	CompoundSprite compoundSprite{ 0, std::move(mock) };
	CompoundSprite compoundSprite2{ compoundSprite };
	BOOST_CHECK(copies == 1);
}

BOOST_FIXTURE_TEST_CASE(CopyAssign_DoesCopyAssign, ReusableObjects)
{
	CompoundSprite compoundSprite{ 0, sprite };
	CompoundSprite compoundSprite2{};
	compoundSprite2 = compoundSprite;

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite2.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite2.getComponentCount(0) == 1);
}

BOOST_AUTO_TEST_CASE(CopyAssign_ClonesComponents)
{
	int copies = 0;
	int moves = 0;
	MockDrawable_ForMoveCopyCounts mock{ copies , moves };
	CompoundSprite compoundSprite{ 0, std::move(mock) };
	CompoundSprite compoundSprite2;
	compoundSprite2 = compoundSprite;
	BOOST_CHECK(copies == 1);
}

BOOST_AUTO_TEST_CASE(MoveCtr_DoesMoveConstruction)
{
	CompoundSprite compoundSprite{ 0, sf::Sprite{} };
	CompoundSprite compoundSprite2( std::move(compoundSprite) );

	BOOST_CHECK(compoundSprite2.isEmpty() == false);
	BOOST_CHECK(compoundSprite2.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite2.getComponentCount(0) == 1);
}

BOOST_AUTO_TEST_CASE(MoveCtr_ClonesComponents)
{
	int copies = 0;
	int moves = 0;
	MockDrawable_ForMoveCopyCounts mock{ copies , moves };
	CompoundSprite compoundSprite{ 0, std::move(mock) };
	CompoundSprite compoundSprite2{ std::move(compoundSprite) };
	BOOST_CHECK(copies == 0);
}

BOOST_FIXTURE_TEST_CASE(MoveAssign_DoesMoveAssign, ReusableObjects)
{
	CompoundSprite compoundSprite{ 0, sprite };
	CompoundSprite compoundSprite2{};
	compoundSprite2 = std::move(compoundSprite);

	BOOST_CHECK(compoundSprite2.isEmpty() == false);
	BOOST_CHECK(compoundSprite2.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite2.getComponentCount(0) == 1);
}

BOOST_AUTO_TEST_CASE(MoveAssign_DoesNotCloneComponents)
{
	int copies = 0;
	int moves = 0;
	MockDrawable_ForMoveCopyCounts mock{ copies , moves };
	CompoundSprite compoundSprite{ 0, std::move(mock) };
	CompoundSprite compoundSprite2;
	compoundSprite2 = std::move(compoundSprite);
	BOOST_CHECK(copies == 0);
}

// TODO: This does not test the copy at all. After CompoundSprite becomes iterable?, we can.
BOOST_FIXTURE_TEST_CASE(CopyCtr_TransformCheck, ReusableObjects)
{
	// Create CS with sprites
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(0, sprite);
	// Transform so sprite transform too
	compoundSprite.setPosition(1.0f, 1.0f);
	compoundSprite.setScale(2.0f, 2.0f);
	compoundSprite.setRotation(1.0f);

	// Copy
	CompoundSprite compoundSprite2{ compoundSprite };

	// Check transform things on CS.
	BOOST_CHECK(compoundSprite2.getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(compoundSprite2.getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(compoundSprite2.getRotation() == 1.0f);
	// Check transform things on Sprites.
	CompoundSprite::ComponentWrapper* returnedSprite = compoundSprite2.getComponentsWithPriorty(0)[0];
	BOOST_CHECK(returnedSprite->getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(returnedSprite->getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(returnedSprite->getRotation() == 1.0f);
}

// TODO: This does not test the copy at all. After CompoundSprite becomes iterable?, we can.
BOOST_FIXTURE_TEST_CASE(CopyAssign_TransformCheck, ReusableObjects)
{
	// Create CS with sprites
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(0, sprite);
	// Transform so sprite transform too
	compoundSprite.setPosition(1.0f, 1.0f);
	compoundSprite.setScale(2.0f, 2.0f);
	compoundSprite.setRotation(1.0f);

	// Copy Assign
	CompoundSprite compoundSprite2;
	compoundSprite2 = compoundSprite;

	// Check transform things on CS.
	BOOST_CHECK(compoundSprite2.getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(compoundSprite2.getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(compoundSprite2.getRotation() == 1.0f);
	// Check transform things on Sprites.
	CompoundSprite::ComponentWrapper* returnedSprite = compoundSprite2.getComponentsWithPriorty(0)[0];
	BOOST_CHECK(returnedSprite->getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(returnedSprite->getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(returnedSprite->getRotation() == 1.0f);
}

BOOST_FIXTURE_TEST_CASE(MoveCtr_TransformCheck, ReusableObjects)
{
	// Create CS with sprites
	CompoundSprite compoundSprite{};
	auto& spriteReturn = compoundSprite.addComponent(0, sprite);
	// Transform so sprite transform too
	compoundSprite.setPosition(1.0f, 1.0f);
	compoundSprite.setScale(2.0f, 2.0f);
	compoundSprite.setRotation(1.0f);

	// Move
	CompoundSprite compoundSprite2{ std::move(compoundSprite) };

	// Check tranform things on CS.
	BOOST_CHECK(compoundSprite2.getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(compoundSprite2.getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(compoundSprite2.getRotation() == 1.0f);
	// Check transform things on Sprites.
	BOOST_CHECK(spriteReturn.getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(spriteReturn.getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(spriteReturn.getRotation() == 1.0f);
}

BOOST_FIXTURE_TEST_CASE(MoveAssign_TransformCheck, ReusableObjects)
{
	// Create CS with sprites
	CompoundSprite compoundSprite{};
	auto& spriteReturn = compoundSprite.addComponent(0, sprite);
	// Transform so sprite transform too
	compoundSprite.setPosition(1.0f, 1.0f);
	compoundSprite.setScale(2.0f, 2.0f);
	compoundSprite.setRotation(1.0f);

	// Move Assign
	CompoundSprite compoundSprite2;
	compoundSprite2 = std::move(compoundSprite);

	// Check tranform things on CS.
	BOOST_CHECK(compoundSprite2.getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(compoundSprite2.getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(compoundSprite2.getRotation() == 1.0f);
	// Check transform things on Sprites.
	BOOST_CHECK(spriteReturn.getPosition() == sf::Vector2f(1.0f, 1.0f));
	BOOST_CHECK(spriteReturn.getScale() == sf::Vector2f(2.0f, 2.0f));
	BOOST_CHECK(spriteReturn.getRotation() == 1.0f);
}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_CTR

BOOST_AUTO_TEST_SUITE(addComponent)

BOOST_FIXTURE_TEST_CASE(addComponent_Sprite, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(0, sprite);

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(addComponent_AnimatedSprite, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(0, animSpriteWithAnim1);

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(addComponent_RectangleShape, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(0, sf::RectangleShape{});

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(addComponent_CompoundSprite, ReusableObjects) {
	CompoundSprite compoundSprite{};
	compoundSprite.addComponent(0, CompoundSprite{});

	BOOST_CHECK(compoundSprite.isEmpty() == false);
	BOOST_CHECK(compoundSprite.getComponentCount() == 1);
	BOOST_CHECK(compoundSprite.getComponentCount(0) == 1);
}

BOOST_FIXTURE_TEST_CASE(addComponent_Return, ReusableObjects) {
	CompoundSprite compoundSprite{};
	sprite.setColor(sf::Color::Red);
	auto& returnRef = compoundSprite.addComponent(0, sprite);

	BOOST_CHECK(returnRef.getColor() == sprite.getColor());
}

BOOST_AUTO_TEST_SUITE_END() // END addComponent

BOOST_AUTO_TEST_SUITE(GetComponents)

	BOOST_FIXTURE_TEST_CASE(ComponentWrapper_getDataAs, ReusableObjects)
	{
		sprite.setColor(sf::Color::Red);
		// Create a ComponentWrapper(Child) and assign it to a ComponentWrapper&
		ComponentWrapperTestHelper inheritedWrapper{ sprite };
		CompoundSprite::ComponentWrapper& compWrapper = inheritedWrapper;

		CompoundSprite compoundSprite{};

		compoundSprite.addComponent(1, sprite);

		sf::Sprite& retrievedSprite = compWrapper.getDataAs<sf::Sprite>();
		BOOST_CHECK(areSpritesEquivalent(retrievedSprite, sprite));
	}

	BOOST_FIXTURE_TEST_CASE(ComponentWrapper_getDataAs_WrongType, ReusableObjects)
	{
		sprite.setColor(sf::Color::Red);
		// Create a ComponentWrapper(Child) and assign it to a ComponentWrapper&
		ComponentWrapperTestHelper inheritedWrapper{ sprite };
		CompoundSprite::ComponentWrapper& compWrapper = inheritedWrapper;

		CompoundSprite compoundSprite{};

		compoundSprite.addComponent(1, sprite);

		BOOST_CHECK_THROW(compWrapper.getDataAs<CompoundSprite>(), CompoundSprite::ComponentWrapper::BadComponentCast);
	}

	BOOST_FIXTURE_TEST_CASE(IsIterable, ReusableObjects)
	{
		sprite.setColor(sf::Color::Blue);
		sprite2.setColor(sf::Color::Green);

		CompoundSprite compoundSprite{};
		compoundSprite.addComponent(0, sprite);
		compoundSprite.addComponent(1, sprite2);

		std::vector<sf::Sprite*> testVector{ &sprite, &sprite2 };

		int testIndex = 0;
		for (const std::pair<const int, std::unique_ptr<CompoundSprite::ComponentWrapper>>& priorityPair : compoundSprite)
		{
			BOOST_CHECK_EQUAL(testIndex, priorityPair.first);

			sf::Sprite& retrievedSprite = priorityPair.second->getDataAs<sf::Sprite>();
			BOOST_CHECK(areSpritesEquivalent(*testVector[testIndex], retrievedSprite));
			testIndex++;
		}
	}
	
	BOOST_FIXTURE_TEST_CASE(GetCoponentsWithPriority, ReusableObjects)
	{
		CompoundSprite compoundSprite{};
		sprite.setColor(sf::Color::Yellow);
		sprite2.setColor(sf::Color::Green);
		compoundSprite.addComponent(1, sprite);
		compoundSprite.addComponent(2, sprite);
		compoundSprite.addComponent(2, sprite2);

		// Positive Test
		BOOST_CHECK(compoundSprite.getComponentsWithPriorty(1).size() == 1);
		BOOST_CHECK(compoundSprite.getComponentsWithPriorty(2).size() == 2);
		sf::Sprite& retrievedSprite = compoundSprite.getComponentsWithPriorty(1).at(0)->getDataAs<sf::Sprite>();
		sf::Sprite& retrievedSprite2 = compoundSprite.getComponentsWithPriorty(2).at(0)->getDataAs<sf::Sprite>();
		sf::Sprite& retrievedSprite3 = compoundSprite.getComponentsWithPriorty(2).at(1)->getDataAs<sf::Sprite>();
		areSpritesEquivalent(sprite, retrievedSprite);
		areSpritesEquivalent(sprite, retrievedSprite2);
		areSpritesEquivalent(sprite, retrievedSprite3);

		// Negative Test
		BOOST_CHECK(compoundSprite.getComponentsWithPriorty(0).size() == 0);
		BOOST_CHECK(compoundSprite.getComponentsWithPriorty(3).size() == 0);
	}

BOOST_AUTO_TEST_SUITE_END() // END CompoundSprite_GetComponents


BOOST_AUTO_TEST_SUITE(Update)

	BOOST_FIXTURE_TEST_CASE(CompoundSprite_update, ReusableObjects)
	{
		CompoundSprite compoundSprite;
		compoundSprite.addComponent(1, animSpriteWithAnim1);
		compoundSprite.addComponent(1, animSpriteWithAnim2);

		for (const auto& priorityComponentPair : compoundSprite)
		{
			priorityComponentPair.second->getDataAs<AnimatedSprite>().runAnimation(0);
		}

		compoundSprite.update(2);

		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getDataAs<AnimatedSprite>().getCurrentFrame() == 1);
		}
	}

BOOST_AUTO_TEST_SUITE_END() // END Update

BOOST_AUTO_TEST_SUITE(Transform)

	BOOST_FIXTURE_TEST_CASE(CompoundSprite_scale, ReusableObjects)
	{
		CompoundSprite compoundSprite(1, sprite, animSpriteWithAnim1, animSpriteWithAnim2);
		const float X_SCALE_FACTOR = 0.1f;
		const float Y_SCALE_FACTOR = 0.2f;

		compoundSprite.scale(X_SCALE_FACTOR, Y_SCALE_FACTOR);

		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getScale().x == X_SCALE_FACTOR);
			BOOST_CHECK(priorityComponentPair.second->getScale().y == Y_SCALE_FACTOR);
		}
	}

	// Test that setting the scale of a compound sprite scales all of its component sprites
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setScale_Two_Inputs, ReusableObjectsForOperations) {
		const float SCALE_FACTOR_X = 0.123f;
		const float SCALE_FACTOR_Y = 0.234f;
		compoundSprite.setScale(SCALE_FACTOR_X, SCALE_FACTOR_Y);

		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getScale().x == SCALE_FACTOR_X);
			BOOST_CHECK(priorityComponentPair.second->getScale().y == SCALE_FACTOR_Y);
		}
	}

	// Test that setting the scale of the compound sprite sets the scale of all of its component sprites
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setScale_One_Input, ReusableObjectsForOperations) {
		const float SCALE_FACTOR_X = 0.123f;
		const float SCALE_FACTOR_Y = 0.234f;
		const sf::Vector2f SCALE_FACTOR{ SCALE_FACTOR_X, SCALE_FACTOR_Y };
		compoundSprite.setScale(SCALE_FACTOR);

		//ensure all sprites got the correct scale
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getScale().x == SCALE_FACTOR_X);
			BOOST_CHECK(priorityComponentPair.second->getScale().y == SCALE_FACTOR_Y);
		}
	}


	// Tests that rotating a compound sprite rotates all of its components
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_rotate_rotate_from_zero, ReusableObjectsForOperations) 
	{
		const float ROTATION = 10;
		compoundSprite.rotate(ROTATION);

		//ensure all sprites got the correct rotation
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getRotation() == ROTATION);
		}
	}

	// Test that applying a rotation to a compound sprite is cumulative.
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_Rotate_Additive_Rotate, ReusableObjectsForOperations) 
	{
		const float ROTATION = 10;
		const unsigned int NUM_ROTATIONS = 2;

		for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
			compoundSprite.rotate(ROTATION);
		}

		//ensure all sprites got the correct rotation
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getRotation() == NUM_ROTATIONS * ROTATION);
		}
	}

	// Test that setting the rotation of a compound sprite sets the rotation for all of its components
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotation_rotate_from_zero, ReusableObjectsForOperations) {
		const float ROTATION = 10;
		compoundSprite.setRotation(ROTATION);

		//ensure all sprites got the correct rotation
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getRotation() == ROTATION);
		}
	}

	// Test that setting a rotation to a compound sprite is not cumulative.
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setRotation_NonAdditive_Rotate, ReusableObjectsForOperations)
	{
		const float ROTATION = 10;
		const unsigned int NUM_ROTATIONS = 2;

		for (unsigned int i = 0; i < NUM_ROTATIONS; i++) {
			compoundSprite.setRotation(ROTATION);
		}

		//ensure all sprites got the correct rotation
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getRotation() == ROTATION);
		}
	}

	BOOST_FIXTURE_TEST_CASE(CompoundSprite_move, ReusableObjectsForOperations) 
	{
		const float X_OFFSET = 500.6f;
		const float Y_OFFSET = 100.2f;

		compoundSprite.move(X_OFFSET, Y_OFFSET);

		//ensure all components got the correct position
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK_CLOSE_FRACTION(priorityComponentPair.second->getPosition().x, X_OFFSET, 1.0f);
			BOOST_CHECK_CLOSE_FRACTION(priorityComponentPair.second->getPosition().y, Y_OFFSET, 1.0f);
		}
	}

	// Test that moving a compound sprite correctly moves all of its components
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_move_Vector2f, ReusableObjectsForOperations) 
	{
		const float X_OFFSET = 213.456f;
		const float Y_OFFSET = 456.123f;
		const sf::Vector2f OFFSET(X_OFFSET, Y_OFFSET);

		compoundSprite.move(OFFSET);

		//ensure all components got the correct position
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK_CLOSE_FRACTION(priorityComponentPair.second->getPosition().x, X_OFFSET, 1.0f);
			BOOST_CHECK_CLOSE_FRACTION(priorityComponentPair.second->getPosition().y, Y_OFFSET, 1.0f);
		}
	}

	// Test that setting the position of the compound sprite correctly sets the position of all of the members
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Vector2f, ReusableObjectsForOperations) 
	{
		const float POSITION_X = 123.456f;
		const float POSITION_Y = 654.321f;
		const sf::Vector2f POSITION(POSITION_X, POSITION_Y);

		// store the old positions
		std::vector<sf::Vector2f> oldPositions;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			oldPositions.push_back(priorityComponentPair.second->getPosition());
		}

		compoundSprite.setPosition(POSITION);

		// ensure that all components maintain their position relative to the new position of the compound sprite
		BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

		// ensure the new positions are correct
		std::size_t count = 0;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getPosition().x == POSITION_X + oldPositions[count].x && priorityComponentPair.second->getPosition().y == POSITION_Y + oldPositions[count].y);
			++count;
		}
	}

	// Test that setting the position of the compound sprite to its current position does nothing
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Current_Position_Vector2f, ReusableObjectsForOperations) 
	{
		const float POSITION_X = 0;
		const float POSITION_Y = 0;
		const sf::Vector2f POSITION(POSITION_X, POSITION_Y);

		// store the old positions
		std::vector<sf::Vector2f> oldPositions;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			oldPositions.push_back(priorityComponentPair.second->getPosition());
		}

		compoundSprite.setPosition(POSITION);

		// ensure that all components maintain their position relative to the new position of the compound sprite
		BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

		// ensure the new positions are correct
		std::size_t count = 0;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			BOOST_CHECK(priorityComponentPair.second->getPosition().x == POSITION_X + oldPositions[count].x && priorityComponentPair.second->getPosition().y == POSITION_Y + oldPositions[count].y);
			++count;
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
		CompoundSprite compoundSprite = CompoundSprite{ STARTING_POS, 0, sprite, animSpriteWithAnim1, animSpriteWithAnim2 };

		// store the old positions
		std::vector<sf::Vector2f> oldPositions;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			oldPositions.push_back(priorityComponentPair.second->getPosition());
		}

		compoundSprite.setPosition(POSITION);

		// ensure the new positions are correct
		BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);
		int count = 0;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			auto& temp = priorityComponentPair.second;
			BOOST_CHECK_CLOSE(temp->getPosition().x, (POSITION_X - STARTING_X) + oldPositions[count].x, 0.001);
			BOOST_CHECK_CLOSE(temp->getPosition().y, (POSITION_Y - STARTING_Y) + oldPositions[count].y, 0.001);
			count++;
		}
	}

	// Test that setting the position of the compound sprite correctly sets the position of all of the members
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Two_Floats, ReusableObjectsForOperations) {
		const float POSITION_X = 123.456f;
		const float POSITION_Y = 654.321f;

		// store the old positions
		std::vector<sf::Vector2f> oldPositions;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			oldPositions.push_back(priorityComponentPair.second->getPosition());
		}

		compoundSprite.setPosition(POSITION_X, POSITION_Y);

		// ensure that all components maintain their position relative to the new position of the compound sprite
		BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

		// ensure the new positions are correct
		int count = 0;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			auto& temp = priorityComponentPair.second;
			BOOST_CHECK_CLOSE(temp->getPosition().x, (POSITION_X)+oldPositions[count].x, 0.001);
			BOOST_CHECK_CLOSE(temp->getPosition().y, (POSITION_Y)+oldPositions[count].y, 0.001);
			count++;
		}
	}

	// Test that setting the position of the compound sprite to its current position does nothing
	BOOST_FIXTURE_TEST_CASE(CompoundSprite_setPosition_Current_Position_Two_Floats, ReusableObjectsForOperations) {
		const float POSITION_X = 0;
		const float POSITION_Y = 0;

		// store the old positions
		std::vector<sf::Vector2f> oldPositions;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			oldPositions.push_back(priorityComponentPair.second->getPosition());
		}

		compoundSprite.setPosition(POSITION_X, POSITION_Y);

		// ensure that all components maintain their position relative to the new position of the compound sprite
		BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

		// ensure the new positions are correct
		int count = 0;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			auto& temp = priorityComponentPair.second;
			BOOST_CHECK_CLOSE(temp->getPosition().x, oldPositions[count].x, 0.001);
			BOOST_CHECK_CLOSE(temp->getPosition().y, oldPositions[count].y, 0.001);
			count++;
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
		CompoundSprite compoundSprite = CompoundSprite{ STARTING_POS, 0, sprite, animSpriteWithAnim1, animSpriteWithAnim2 };

		// store the old positions
		std::vector<sf::Vector2f> oldPositions;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			oldPositions.push_back(priorityComponentPair.second->getPosition());
		}

		compoundSprite.setPosition(POSITION_X, POSITION_Y);

		// ensure that all components maintain their position relative to the new position of the compound sprite
		BOOST_CHECK(compoundSprite.getPosition().x == POSITION_X && compoundSprite.getPosition().y == POSITION_Y);

		// ensure the new positions are correct
		int count = 0;
		for (const auto& priorityComponentPair : compoundSprite)
		{
			auto& temp = priorityComponentPair.second;
			BOOST_CHECK_CLOSE(temp->getPosition().x, (POSITION_X - STARTING_X) + oldPositions[count].x, 0.001);
			BOOST_CHECK_CLOSE(temp->getPosition().y, (POSITION_Y - STARTING_Y) + oldPositions[count].y, 0.001);
			count++;
		}
	}

BOOST_AUTO_TEST_SUITE_END() // Transform


BOOST_AUTO_TEST_SUITE(CompoundSprite_SFINAETests)

	// SFINAE types for checking if CompoundSprite can be constructed with given inputs
	template <class, class = std::void_t<> >
	struct CanConstructCompoundSprite : std::false_type {};

	template <class T>
	struct CanConstructCompoundSprite <
		T,
		std::void_t<
		decltype(CompoundSprite(std::declval<int>(), std::declval<T>()))
		>
	> : std::true_type {};

	template <class T>
	inline constexpr bool CanConstructCompoundSprite_v = CanConstructCompoundSprite<T>::value;

	BOOST_AUTO_TEST_CASE(SFINAE_CanConstruct_Sprite)
	{
		bool test = CanConstructCompoundSprite_v<sf::Sprite>;
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
		decltype(CompoundSprite{}.addComponent(std::declval<int>(), std::declval<T>()))
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

BOOST_AUTO_TEST_SUITE_END() // END CompoundSpriteTests