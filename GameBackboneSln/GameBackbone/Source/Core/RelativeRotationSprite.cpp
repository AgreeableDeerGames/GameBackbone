#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>
#include <GameBackbone/Core/RelativeRotationSprite.h>

using namespace GB;

// ctr / dtr


/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Animated sprites from the components array are identified via RTTI and will update when the RelativeRotationSprite updates.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
/// <returns></returns>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets) :
	CompoundSprite() {
	initializeComponentVector(std::move(components), relativeOffsets);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Animated sprites from the components array are identified via RTTI and will update when the RelativeRotationSprite updates.
/// Initializes the sprite's position (0,0).
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
/// <param name="initialPosition">The initial position.</param>
/// <returns></returns>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets, sf::Vector2f initialPosition) :
	CompoundSprite(initialPosition) {
	initializeComponentVector(std::move(components), relativeOffsets);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// Initializes the sprite's position to (0,0).
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="sprites">Sprite components of the new RelativeRotationSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new RelativeRotationSprite</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> sprites, std::vector<AnimatedSprite> animatedSprites, const std::vector<sf::Vector2f>& relativeOffsets) :
	CompoundSprite() {
	initializeComponentVector(std::move(sprites), std::move(animatedSprites), relativeOffsets);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="sprites">Sprite components of the new RelativeRotationSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new RelativeRotationSprite</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
/// <param name="initialPosition">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> sprites, std::vector<AnimatedSprite> animatedSprites, const std::vector<sf::Vector2f>& relativeOffsets, sf::Vector2f initialPosition) :
	CompoundSprite(initialPosition) {
	initializeComponentVector(std::move(sprites), std::move(animatedSprites), relativeOffsets);
}

// Add / remove

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite. This sprite's position will be set to the RelativeRotationSprite's position,
/// and the sprite's origin will be set using the relative offset.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New sprite component of the RelativeRotationSprite. Passing nullptr is illegal.</param>
std::size_t RelativeRotationSprite::addComponent(sf::Sprite component) {

	// Fix the position and origin of the new component
	component.setOrigin(component.getPosition().x - position.x, component.getPosition().y - position.y);
	component.setPosition(position.x, position.y);

	// Add the fixed component as if it were in a normal CompoundSprite
	return CompoundSprite::addComponent(std::move(component));
}

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the RelativeRotationSprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component. Passing nullptr is illegal.</param>
/// <param name="relativeOffset">The relative offset.</param>
std::size_t RelativeRotationSprite::addComponent(sf::Sprite component, sf::Vector2f relativeOffset) {

	// Fix the origin of the component
	component.setOrigin(relativeOffset.x, relativeOffset.y);

	// Add the component as if it were in a normal compound sprite
	return CompoundSprite::addComponent(std::move(component));

}

/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This sprite's position will be set to the RelativeRotationSprite's position,
/// and the sprite's origin will be set using the relative offset.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New Animated Sprite component of the RelativeRotationSprite. Passing nullptr is illegal.</param>
std::size_t RelativeRotationSprite::addComponent(AnimatedSprite component) {

	// Fix origin and position of component 
	component.setOrigin(component.getPosition().x - position.x, component.getPosition().y - position.y);
	component.setPosition(position.x, position.y);

	// Add the component as if it were in a normal compound sprite
	return CompoundSprite::addComponent(std::move(component));
}

/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the RelativeRotationSprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component. Passing nullptr is illegal.</param>
/// <param name="relativeOffset">The relative offset.</param>
std::size_t RelativeRotationSprite::addComponent(AnimatedSprite component, sf::Vector2f relativeOffset) {
	// Fix origin of component
	component.setOrigin(relativeOffset.x, relativeOffset.y);

	// Add the component as if it were in a normal compound sprite
	return CompoundSprite::addComponent(std::move(component));
}

// operations

/// <summary>
/// Scales all the components of the RelativeRotationSprite.
/// </summary>
/// <param name="factorX">The new horizontal scale factor.</param>
/// <param name="factorY">The new vertical scale factor.</param>
void RelativeRotationSprite::scale(float factorX, float factorY) {
	CompoundSprite::scale(factorX, factorY);

	// function that scales a component along with its origin to keep rotation correct
	auto scaleFunction = [factorX, factorY] (auto& component) {
		component.setOrigin(factorX*component.getOrigin().x, factorY*component.getOrigin().y);
	};

	// scale all of the components
	std::for_each(std::begin(components), std::end(components), scaleFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), scaleFunction);
}

/// <summary>
/// Scales all the components of the RelativeRotationSprite.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::scale(sf::Vector2f newScale) {
	RelativeRotationSprite::scale(newScale.x, newScale.y);
}


/// <summary>
/// Initializes the component vector using the offset vector.
/// </summary>
/// <param name="components">The components to be added.</param>
/// <param name="relativeOffsets">The relative offsets for each sprite.</param>
void RelativeRotationSprite::initializeComponentVector(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets) {
	if (components.size() != relativeOffsets.size()) {
		throw Error::RelativeRotationSprite_MismatchedSizes();
	}

	// add the components to the CompoundSprite
	for (std::size_t i = 0; i < components.size(); ++i) {
		addComponent(std::move(components[i]), relativeOffsets[i]);
	}

}

/// <summary>
/// Initializes the component vectors for Sprite and AnimatedSprite.
/// </summary>
/// <param name="sprites">The sprites to be added.</param>
/// <param name="animatedSprites">The animated sprites to be added.</param>
/// <param name="relativeOffsets">The relative offsets for the sprites.</param>
void RelativeRotationSprite::initializeComponentVector(std::vector<sf::Sprite> sprites, std::vector<AnimatedSprite> animatedComponents, const std::vector<sf::Vector2f>& relativeOffsets) {
	if (sprites.size() + animatedComponents.size() != relativeOffsets.size())
	{
		throw Error::RelativeRotationSprite_MismatchedSizes();
	}

	// add the components to the CompoundSprite
	for (std::size_t ii = 0; ii < sprites.size(); ++ii) {
		addComponent(std::move(sprites[ii]), relativeOffsets[ii]);
	}
	for (std::size_t ii = sprites.size(); ii < sprites.size() + animatedComponents.size(); ++ii) {
		addComponent(std::move(animatedComponents[ii - sprites.size()]), relativeOffsets[ii]);
	}
}

/// <summary>
/// This function is Not Implemented for RelativeRotationSprite. Please use RelativeRotationSprite::scale instead.
/// </summary>
/// <param name="factorX">The factor x.</param>
/// <param name="factorY">The factor y.</param>
void RelativeRotationSprite::setScale(float factorX, float factorY) {
	throw Error::Function_NotImplemented();
}

/// <summary>
/// This function is Not Implemented for RelativeRotationSprite. Please use RelativeRotationSprite::scale instead.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::setScale(sf::Vector2f newScale) {
	throw Error::Function_NotImplemented();
}
