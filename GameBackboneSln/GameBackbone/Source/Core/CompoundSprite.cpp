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
CompoundSprite::CompoundSprite() : position({ 0,0 }) {}

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
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components, sf::Vector2f position) :
	components(std::move(components)),
	position(position){
}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed instances of sf::Sprite and AnimatedSprite become components of the CompoundSprite.
/// The animated sprites will update when the compound sprite updates.
/// The position of the sprite is (0,0).
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents) :
	CompoundSprite(std::move(components), std::move(animatedComponents), {0,0}) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed instance of sf::Sprite and AnimatedSprite as components of the CompoundSprite.
/// The animated sprites will update when the compound sprite updates.
/// Initializes the CompoundSprite to the passed position.
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite.</param>
/// <param name="position">The position.</param>
CompoundSprite::CompoundSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, sf::Vector2f initialPosition) :
	components(std::move(components)),
	animatedComponents(std::move(animatedComponents)),
	position(initialPosition) {
}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
CompoundSprite::CompoundSprite(sf::Vector2f initialPosition) : position(initialPosition) {}

// getters

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
sf::Vector2f CompoundSprite::getPosition() const {
	return position;
}

/// <summary>
/// Returns the Sprite component at the provided index.
/// Throws std::out_of_range exception if the index is out of bounds.
/// </summary>
/// <param name="componentIndex"> </param>
/// <return> sf::Sprite& </return>
sf::Sprite& CompoundSprite::GetSpriteComponent(std::size_t componentIndex) {
	return components.at(componentIndex);
}

/// <summary>
/// Returns the AnimatedSprite component at the provided index.
/// Throws std::out_of_range exception if the index is out of bounds.
/// </summary>
/// <param name="componentIndex"> </param>
/// <return> sf::Sprite& </return>
AnimatedSprite& CompoundSprite::GetAnimatedComponent(std::size_t componentIndex) {
	return animatedComponents.at(componentIndex);
}

// setters

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="val">The value.</param>
void CompoundSprite::setPosition(sf::Vector2f val) {
	setPosition(val.x, val.y);
}

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="x">The new x.</param>
/// <param name="y">The new y.</param>
void CompoundSprite::setPosition(float x, float y) {
	sf::Vector2f oldPosition = position;
	move(x - oldPosition.x, y - oldPosition.y);
}

/// <summary>
/// Adds a Sprite component to the CompoundSprite.
/// </summary>
/// <param name="component"> The component to add to the CompoundSprite. </param>
/// <return> The index of the added sprite within the CompoundSprite. </return>
std::size_t CompoundSprite::addComponent(sf::Sprite component) {

	// Add the component the the vector of Sprite components
	components.emplace_back(std::move(component));

	// Return the place in the components vector that the new component was placed.
	return components.size();
}

/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite.
/// Sets the animated sprite to be updated when the compound sprite is updated.
/// </summary>
/// <param name="component"> The component to add to the CompoundSprite. </param>
/// <return> The index of the added AnimatedSprite within the CompoundSprite. </return>
std::size_t CompoundSprite::addComponent(AnimatedSprite component) {

	// Add the component the the vector of AnimatedSprite components
	animatedComponents.emplace_back(std::move(component));

	// Return the place in the components vector that the new component was placed.
	return animatedComponents.size();
}

/// <summary>
/// Removes the Sprite component at the passed index from the CompoundSprite.
/// Throws std::out_of_range exception if the component index is out of bounds.
/// </summary>
/// <param name="component">The component to remove from the CompoundSprite</param>
void CompoundSprite::removeSpriteComponent(std::size_t componentIndex) {

	if (componentIndex < components.size()) {
		components.erase(components.begin() + componentIndex);
	} else {
		throw std::out_of_range("Component not in CompoundSprite");
	}
}

/// <summary>
/// Removes the AnimatedSprite component at the passed index from the CompoundSprite.
/// Throws std::out_of_range exception if the component index is out of bounds.
/// </summary>
/// <param name="component">The component to remove from the CompoundSprite</param>
void CompoundSprite::removeAnimatedComponent(std::size_t componentIndex) {

	if (componentIndex < animatedComponents.size()) {
		animatedComponents.erase(animatedComponents.begin() + componentIndex);
	} else {
		throw std::out_of_range("Component not in CompoundSprite");
	}
}

/// <summary>
/// Removes all components from the compound sprite
/// </summary>
void CompoundSprite::clearComponents() {
	components.clear();
	animatedComponents.clear();
}

// operations

/// <summary>
/// Scales all the components of the CompoundSprite.
/// </summary>
/// <param name="factorX">The new horizontal scale factor.</param>
/// <param name="factorY">The new vertical scale factor.</param>
void CompoundSprite::scale(float factorX, float factorY) {

	// lambda function for scaling components
	auto scaleFunction = [factorX, factorY] (auto& component) {
		component.scale(factorX, factorY);
	};

	// apply the scaleFunction to all components
	std::for_each(std::begin(components), std::end(components), scaleFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), scaleFunction);
}

/// <summary>
/// Scales all the components of the  CompoundSprite.
/// </summary>
/// <param name="newScale">The new scale.</param>
void CompoundSprite::scale(sf::Vector2f newScale) {
	scale(newScale.x, newScale.y);
}

/// <summary>
/// Sets the scale factor of all component sprites.
/// </summary>
/// <param name="factorX">The factor x.</param>
/// <param name="factorY">The factor y.</param>
void CompoundSprite::setScale(float factorX, float factorY) {

	// lambda function for scaling components
	auto scaleFunction = [factorX, factorY] (auto& component) {
		component.setScale(factorX, factorY);
	};

	// apply the scaleFunction to all components
	std::for_each(std::begin(components), std::end(components), scaleFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), scaleFunction);
}

/// <summary>
/// Sets the scale of all component sprites.
/// </summary>
/// <param name="newScale">The new scale.</param>
void CompoundSprite::setScale(sf::Vector2f newScale) {
	setScale(newScale.x, newScale.y);
}



/// <summary>
/// Rotates all components of the compound sprite.
/// </summary>
/// <param name="degreeOffset">The offset to the current rotation.</param>
void CompoundSprite::rotate(float degreeOffset) {

	// lambda for ratating components
	auto rotateFunction = [degreeOffset] (auto& component) {
		component.rotate(degreeOffset);
	};

	// apply the rotateFunction to all components
	std::for_each(std::begin(components), std::end(components), rotateFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), rotateFunction);

}

/// <summary>
/// Sets the rotation of all components in the compound sprite.
/// </summary>
/// <param name="newRotation">The new rotation.</param>
void CompoundSprite::setRotation(float newRotation) {

	// lambda for ratating components
	auto rotateFunction = [newRotation] (auto& component) {
		component.setRotation(newRotation);
	};

	// apply the rotateFunction to all components
	std::for_each(std::begin(components), std::end(components), rotateFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), rotateFunction);
}

/// <summary>
/// Moves all the components of the compound sprite by the same offset.
/// </summary>
/// <param name="offsetX">The offset x.</param>
/// <param name="offsetY">The offset y.</param>
void CompoundSprite::move(float offsetX, float offsetY) {

	// function for moving a component
	auto moveFunction = [offsetX, offsetY](auto& component) {
		component.move(offsetX, offsetY);
	};

	// apply the rotateFunction to all components
	std::for_each(std::begin(components), std::end(components), moveFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), moveFunction);

	// update the position of the CompoundSprite as a whole
	position.x += offsetX;
	position.y += offsetY;
}

/// <summary>
/// Moves all the components of the compound sprite by the same offset.
/// </summary>
/// <param name="offset">The offset.</param>
void CompoundSprite::move(sf::Vector2f offset) {
	move(offset.x, offset.y);
}

/// <summary>
/// Updates each animated sprite in the compound sprite.
/// </summary>
/// <param name="currentTime">The current time.</param>
void CompoundSprite::update(sf::Time currentTime) {

	// Forward the update to each component
	for (auto& animatedComponent : animatedComponents) {
		animatedComponent.update(currentTime);
	}
}

/// <summary>
/// Draw all the component sprites of the compound sprite.
/// </summary>
/// <param name="target"> The render target to be drawn to. </param>
/// <param name="states"> Current render states. </param>
void CompoundSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// lambda function to draw a component
	auto drawFunction = [&target, &states](auto& drawable) {
		target.draw(drawable, states);
	};

	// apply drawFunction to all components
	std::for_each(std::begin(components), std::end(components), drawFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), drawFunction);
}

