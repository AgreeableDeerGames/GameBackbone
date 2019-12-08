#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <algorithm>
#include <cstddef>
#include <set>
#include <stdexcept>
#include <vector>

using namespace GB;

// ctr / dtr


/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/>. The Compound sprite has no components and is located at (0,0).
/// </summary>
CompoundSprite::CompoundSprite() {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed Sprites become components of the compound sprite.
/// The position of the sprite is (0,0).
/// </summary>
/// <param name="components">The components.</param>
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components) 
	: CompoundSprite(std::move(components), sf::Vector2f{ 0,0 }) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed Sprites become components of the compound sprite.
/// Initializes the CompoundSprite to the passed position.
/// </summary>
/// <param name="components">The components.</param>
/// <param name="position">The position.</param>
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components, sf::Vector2f position) 
	: CompoundSprite(std::move(components), std::vector<AnimatedSprite>(), position){}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class.
/// The passed instances of sf::Sprite and AnimatedSprite become components of the CompoundSprite.
/// The animated sprites will update when the compound sprite updates.
/// The position of the sprite is (0,0).
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents) :
	CompoundSprite(std::move(components), std::move(animatedComponents), {0,0}) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class.
/// The passed instance of sf::Sprite and AnimatedSprite as components of the CompoundSprite.
/// The animated sprites will update when the compound sprite updates.
/// Initializes the CompoundSprite to the passed position.
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite.</param>
/// <param name="position">The position.</param>
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, sf::Vector2f position){
	setPosition(position);

	// function for adding a component to the RelativeRotationSprite
	auto addComponentFunction = [this](auto& component) {
		addComponent(std::move(component));
	};

	// Add all of the passed components to the RelativerotationSprite
	std::for_each(std::begin(components), std::end(components), addComponentFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), addComponentFunction);
}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
CompoundSprite::CompoundSprite(sf::Vector2f position){
	setPosition(position);
}

/// <summary>
/// Gets the count of Sprite components.
/// </summary>
/// <return> The count of sprite components. </return>
std::size_t CompoundSprite::getSpriteComponentCount() const {
	return m_internalComponents.size();
}

/// <summary>True if this CompoundSprite holds no components. False otherwise.</summary>
bool CompoundSprite::isEmpty() const {
	return m_internalComponents.empty();
}

/// <summary>
/// Removes the Sprite component at the passed index from the CompoundSprite.
/// Throws std::out_of_range exception if the component index is out of bounds.
/// This invalidates all indices returned by addComponent(sf::sprite)
/// </summary>
/// <param name="component">The component to remove from the CompoundSprite</param>
void CompoundSprite::removeComponent(std::size_t componentIndex) {
	if (componentIndex < m_internalComponents.size()) {
		m_internalComponents.erase(m_internalComponents.begin() + componentIndex);
	} else {
		throw std::out_of_range("Component not in CompoundSprite");
	}
}

/// <summary>
/// Removes all components from the compound sprite
/// </summary>
void CompoundSprite::clearComponents() {
	m_internalComponents.clear();
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
	auto setRotationFunction = [angle](auto& component) {
		component.setRotation(angle);
	};

	// Apply the rotateFunction to all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), setRotationFunction);

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
	auto setScaleFunction = [factorX, factorY](auto& component) {
		component.setScale(factorX, factorY);
	};

	// Apply the setScaleFunction to all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), setScaleFunction);

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
	auto setOriginFunction = [x, y, this](auto& component) {

		/*
		 * Move the origin of the component relative to how the origin of the full CompoundSprite is moving.
		 * This preserves the positioning established when components were first added to the CompoundSprite
		 */
		component.setOrigin(component.getOrigin().x + (x - getOrigin().x), component.getOrigin().y + (y - getOrigin().y));
	};

	// update the origin of all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), setOriginFunction);

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
	auto moveFunction = [offsetX, offsetY](auto& component) {
		component.move(offsetX, offsetY);
	};

	// apply the rotateFunction to all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), moveFunction);

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
	auto rotateFunction = [angle](auto& component) {
		component.rotate(angle);
	};

	// Apply the rotateFunction to all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), rotateFunction);

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
	auto scaleFunction = [factorX, factorY](auto& component) {
		component.scale(factorX, factorY);
	};

	// Apply the scaleFunction to all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), scaleFunction);

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
	for (auto& component : m_internalComponents) {
		component->update(elapsedTime);
	}
}

/// <summary>
/// Draw all the component sprites of the compound sprite.
/// </summary>
/// <param name="target"> The render target to be drawn to. </param>
/// <param name="states"> Current render states. </param>
void CompoundSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// lambda function to draw a component
	auto drawFunction = [&target, &states](auto& drawable) {
		target.draw(drawable, states);
	};

	// apply drawFunction to all components
	std::for_each(std::begin(m_internalComponents), std::end(m_internalComponents), drawFunction);
}

