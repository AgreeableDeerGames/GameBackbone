#include <GameBackbone/Core/CompoundSprite.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

using namespace GB;


/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
CompoundSprite::CompoundSprite(sf::Vector2f position){
	setPosition(position);
}

CompoundSprite::CompoundSprite(const CompoundSprite& other) : CompoundSprite()
{
	this->setPosition(other.getPosition());
	this->setRotation(other.getRotation());
	this->setScale(other.getScale());
	this->setOrigin(other.getOrigin());

	for (auto& priorityComponent : other.m_prioritizedComponents)
	{
		this->m_prioritizedComponents.emplace(
			priorityComponent.first, 
			priorityComponent.second->cloneAsUnique()
		);
	}
}

CompoundSprite& CompoundSprite::operator=(const CompoundSprite& other)
{
	CompoundSprite tempOther{ other };
	*this = std::move(tempOther);
	return *this;
}

CompoundSprite::CompoundSprite(CompoundSprite&& other) noexcept
	: Transformable(other), m_prioritizedComponents(std::move(other.m_prioritizedComponents))
{}

CompoundSprite& CompoundSprite::operator=(CompoundSprite&& other) noexcept
{
	// Move the CompoundSprite members from the other
	this->m_prioritizedComponents = std::move(other.m_prioritizedComponents);

	// Copy the Transformable members from the other, since it cannot be moved.
	this->Transformable::setPosition(other.getPosition());
	this->Transformable::setRotation(other.getRotation());
	this->Transformable::setScale(other.getScale());
	this->Transformable::setOrigin(other.getOrigin());

	return *this;
}

/// <summary>
/// Gets the count of Sprite components.
/// </summary>
/// <return> The count of sprite components. </return>
std::size_t CompoundSprite::getComponentCount() const {
	return m_prioritizedComponents.size();
}

/// <summary>
/// Gets the count of Sprite components for a given priority.
/// </summary>
/// <param name="priority">The priority to check.</param>
/// <return> The count of sprite components. </return>
std::size_t CompoundSprite::getComponentCount(int priority) const {
	return m_prioritizedComponents.count(priority);
}

/// <summary>True if this CompoundSprite holds no components. False otherwise.</summary>
bool CompoundSprite::isEmpty() const {
	return m_prioritizedComponents.empty();
}

/// <summary>
/// Removes all components from the compound sprite
/// </summary>
void CompoundSprite::clearComponents() {
	m_prioritizedComponents.clear();
}

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="x">The new x.</param>
/// <param name="y">The new y.</param>
void CompoundSprite::setPosition(float x, float y) {
	const sf::Vector2f& oldPosition = sf::Transformable::getPosition();
	move(x - oldPosition.x, y - oldPosition.y);
}

/// <summary>
/// Sets the rotation of the CompoundSprite and all of its components.
/// The components will rotate about the origin of the CompoundSprite.
/// </summary>
/// <param name="val">The value.</param>
void CompoundSprite::setPosition(const sf::Vector2f& position) {
	setPosition(position.x, position.y);
}

/// <summary>
/// Sets the rotation of the CompoundSprite and all of its components.
/// The components will rotate about the origin of the CompoundSprite.
/// </summary>
/// <param name="angle"> Angle of rotation, in degrees.</param>
void CompoundSprite::setRotation(float angle) {
	// Lambda for rotating components
	auto setRotationFunction = [angle](auto& componentPair) {
		componentPair.second->setRotation(angle);
	};

	// Apply the rotateFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), setRotationFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::setRotation(angle);
}

/// <summary>
/// Sets the scale factor of the CompoundSprite and all of its components.
/// </summary>
/// <param name="factorX">The scale factor in the x direction.</param>
/// <param name="factorY">The scale factor in the y direction.</param>
void CompoundSprite::setScale(float factorX, float factorY) {
	// Lambda function for scaling components
	auto setScaleFunction = [factorX, factorY](auto& componentPair) {
		componentPair.second->setScale(factorX, factorY);
	};

	// Apply the setScaleFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), setScaleFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::setScale(factorX, factorY);
}

/// <summary>
/// Sets the scale factor of the CompoundSprite and all of its components.
/// </summary>
/// <param name="factors">The new scale.</param>
void CompoundSprite::setScale(const sf::Vector2f& factors) {
	setScale(factors.x, factors.y);
}

/// <summary>
/// Sets the origin of the compound sprite.
/// Sets the origin of all components relative to the new origin.
/// </summary>
/// <param name="x">The x coordinate of the new origin.</param>
/// <param name="y">The y coordinate of the new origin.</param>
void CompoundSprite::setOrigin(float x, float y) {
	// function to update the origin of a component
	auto setOriginFunction = [x, y, this](auto& componentPair) {

		/*
		 * Move the origin of the component relative to how the origin of the full CompoundSprite is moving.
		 * This preserves the positioning established when components were first added to the CompoundSprite
		 */
		componentPair.second->setOrigin(componentPair.second->getOrigin().x + (x - getOrigin().x), componentPair.second->getOrigin().y + (y - getOrigin().y));
	};

	// update the origin of all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), setOriginFunction);

	// Update the origin of the CompoundSprite as a whole
	sf::Transformable::setOrigin(x, y);
}

/// <summary>
/// Sets the origin of the compound sprite.
/// Sets the origin of all components relative to the new origin.
/// </summary>
/// <param name="origin">The new position of the origin.</param>
void CompoundSprite::setOrigin(const sf::Vector2f& origin) {
	setOrigin(origin.x, origin.y);
}

/// <summary>
/// Moves the CompoundSprite and all of its components by the same offset.
/// </summary>
/// <param name="offsetX">The offset x.</param>
/// <param name="offsetY">The offset y.</param>
void CompoundSprite::move(float offsetX, float offsetY) {
	// function for moving a component
	auto moveFunction = [offsetX, offsetY](auto& componentPair) {
		componentPair.second->move(offsetX, offsetY);
	};

	// apply the rotateFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), moveFunction);

	// update the position of the CompoundSprite as a whole
	sf::Transformable::move(offsetX, offsetY);
}

/// <summary>
/// Moves the CompoundSprite and all of its components by the same offset.
/// </summary>
/// <param name="offset">The offset.</param>
void CompoundSprite::move(const sf::Vector2f& offset) {
	move(offset.x, offset.y);
}

/// <summary>
/// Rotates the CompoundSprite and all of its components.
/// The components will rotate about the origin of the CompoundSprite.
/// </summary>
/// <param name="angle">The offset to the current rotation.</param>
void CompoundSprite::rotate(float angle) {
	// Lambda for rotating components
	auto rotateFunction = [angle](auto& componentPair) {
		componentPair.second->rotate(angle);
	};

	// Apply the rotateFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), rotateFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::rotate(angle);
}

/// <summary>
/// Scales the CompoundSprite and all of its components.
/// </summary>
/// <param name="factorX">The horizontal scale factor.</param>
/// <param name="factorY">The vertical scale factor.</param>
void CompoundSprite::scale(float factorX, float factorY) {
	// Lambda function for scaling components
	auto scaleFunction = [factorX, factorY](auto& componentPair) {
		componentPair.second->scale(factorX, factorY);
	};

	// Apply the scaleFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), scaleFunction);

	// Update the position of the CompoundSprite as a whole
	sf::Transformable::scale(factorX, factorY);
}

/// <summary>
/// Scales the CompoundSprite and all of its components.
/// </summary>
/// <param name="factor">The scale factors.</param>
void CompoundSprite::scale(const sf::Vector2f& factor) {
	scale(factor.x, factor.y);
}

/// <summary>
/// Updates each animated sprite in the compound sprite.
/// </summary>
/// <param name="elapsedTime">The elapsed time.</param>
void CompoundSprite::update(sf::Int64 elapsedTime) {
	// Forward the update to each component
	for (auto& componentPair : m_prioritizedComponents) {
		componentPair.second->update(elapsedTime);
	}
}

/// <summary>
/// Draw all the component sprites of the compound sprite.
/// </summary>
/// <param name="target"> The render target to be drawn to. </param>
/// <param name="states"> Current render states. </param>
void CompoundSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// lambda function to draw a component
	auto drawFunction = [&target, &states](auto& componentPair) {
		target.draw(componentPair.second->getDataAsDrawable(), states);
	};

	// apply drawFunction to all components
	std::for_each(std::begin(m_prioritizedComponents), std::end(m_prioritizedComponents), drawFunction);
}

