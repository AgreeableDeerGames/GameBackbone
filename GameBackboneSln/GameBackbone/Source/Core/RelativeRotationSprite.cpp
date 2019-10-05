#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Core/CompoundSprite.h>
#include <GameBackbone/Core/RelativeRotationSprite.h>

#include <exception>
#include <vector>

using namespace GB;

// ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// The position of the sprite is (0,0).
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components) 
	: RelativeRotationSprite(std::move(components), {0, 0}) {
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
/// <param name="position">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, sf::Vector2f position) 
	: RelativeRotationSprite(std::move(components), std::vector<AnimatedSprite>(), position){
}


/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// The position of the sprite is (0,0).
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">Sprite components of the new RelativeRotationSprite</param>
/// <param name="animatedComponents">AnimatedSprite components of the new RelativeRotationSprite</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents) 
	: RelativeRotationSprite(std::move((components)), std::move(animatedComponents), {0, 0}) {
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">Sprite components of the new RelativeRotationSprite.</param>
/// <param name="animatedComponents">AnimatedSprite components of the new RelativeRotationSprite.</param>
/// <param name="position">The position.</param>
RelativeRotationSprite::RelativeRotationSprite (std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, sf::Vector2f position) :
	CompoundSprite(position),
	m_currentScale(1.0f, 1.0f) {
	// function for adding a component to the RelativeRotationSprite
	auto addComponentFunction = [this] (auto& component) {
		RelativeRotationSprite::addComponent(component);
	};

	// Add all of the passed components to the RelativerotationSprite
	std::for_each(std::begin(components), std::end(components), addComponentFunction);
	std::for_each(std::begin(animatedComponents), std::end(animatedComponents), addComponentFunction);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Sets the initial position of the RelativeRotationSprite to the passed value.
/// </summary>
/// <param name="position">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(sf::Vector2f position) :
	CompoundSprite(position),
	m_currentScale(1.0f, 1.0f) {
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
/// <returns></returns>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets) :
	m_currentScale(1.0f, 1.0f) {
	initializeComponentVector(std::move(components), relativeOffsets);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Initializes the sprite's position (0,0).
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
/// <param name="position">The initial position.</param>
/// <returns></returns>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets, sf::Vector2f position) :
	CompoundSprite(position),
	m_currentScale(1.0f, 1.0f) {
	initializeComponentVector(std::move(components), relativeOffsets);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// Initializes the sprite's position to (0,0).
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="components">Sprite components of the new RelativeRotationSprite</param>
/// <param name="animatedComponents">AnimatedSprite components of the new RelativeRotationSprite</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, const std::vector<sf::Vector2f>& relativeOffsets) :
	m_currentScale(1.0f, 1.0f) {
	initializeComponentVector(std::move(components), std::move(animatedComponents), relativeOffsets);
}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' positions will be set to the RelativeRotationSprite's position,
/// and the components' origin will be set using the relative offsets.
/// </summary>
/// <param name="components">Sprite components of the new RelativeRotationSprite</param>
/// <param name="animatedComponents">AnimatedSprite components of the new RelativeRotationSprite</param>
/// <param name="relativeOffsets">The relative offsets of the components.</param>
/// <param name="position">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, const std::vector<sf::Vector2f>& relativeOffsets, sf::Vector2f position) :
	CompoundSprite(position),
	m_currentScale(1.0f, 1.0f) {
	initializeComponentVector(std::move(components), std::move(animatedComponents), relativeOffsets);
}

// Add / remove

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite. This sprite's position will be set to the RelativeRotationSprite's position,
/// and the sprite's origin will be set using the relative offset.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New sprite component of the RelativeRotationSprite.</param>
std::size_t RelativeRotationSprite::addComponent(sf::Sprite component) {
	// Fix the position and origin of the new component
	component.setOrigin(component.getPosition().x - m_position.x, component.getPosition().y - m_position.y);
	component.setPosition(m_position.x, m_position.y);

	// Add the fixed component as if it were in a normal CompoundSprite
	return CompoundSprite::addComponent(std::move(component));
}

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite.
/// The position of the Sprite will be set to the position of the RelativeRotationSprite.
/// This sprite's origin will be set using the passed in offset.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component.</param>
/// <param name="relativeOffset">The relative offset.</param>
std::size_t RelativeRotationSprite::addComponent(sf::Sprite component, sf::Vector2f relativeOffset) {
	// Fix the position and origin of the new component
	component.setPosition(m_position.x, m_position.y);
	component.setOrigin(relativeOffset.x, relativeOffset.y);

	// Add the component as if it were in a normal compound sprite
	return CompoundSprite::addComponent(std::move(component));

}

/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This AnimatedSprite's position will be set to the RelativeRotationSprite's position,
/// and the AnimatedSprite's origin will be set using the relative offset.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New Animated Sprite component of the RelativeRotationSprite. Passing nullptr is illegal.</param>
std::size_t RelativeRotationSprite::addComponent(AnimatedSprite component) {
	// Fix origin and position of component 
	component.setOrigin(component.getPosition().x - m_position.x, component.getPosition().y - m_position.y);
	component.setPosition(m_position.x, m_position.y);

	// Add the component as if it were in a normal compound sprite
	return CompoundSprite::addComponent(std::move(component));
}

/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite.
/// The position of the AnimatedSprite will be set to the position of the RelativeRotationSprite.
/// This AnimatedSprite's origin will be set using the passed in offset.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component.</param>
/// <param name="relativeOffset">The relative offset.</param>
std::size_t RelativeRotationSprite::addComponent(AnimatedSprite component, sf::Vector2f relativeOffset) {
	// Fix origin and position of component 
	component.setPosition(m_position.x, m_position.y);
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
	std::for_each(std::begin(m_components), std::end(m_components), scaleFunction);
	std::for_each(std::begin(m_animatedComponents), std::end(m_animatedComponents), scaleFunction);

	// set the current scale of the entire RelativeRotationsprite
	m_currentScale.x *= factorX;
	m_currentScale.y *= factorY;
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
/// Throws std::invalid_argument exception if the components and relativeOffsets vectors are not the same size.
/// </summary>
/// <param name="components">The components to be added.</param>
/// <param name="relativeOffsets">The relative offsets for each sprite.</param>
void RelativeRotationSprite::initializeComponentVector(std::vector<sf::Sprite> components, const std::vector<sf::Vector2f>& relativeOffsets) {
	if (components.size() != relativeOffsets.size()) {
		throw std::invalid_argument("The vector inputs to RelativeRotationSprite::initializeComponentVector must be the same size.");
	}

	// add the components to the CompoundSprite
	for (std::size_t i = 0; i < components.size(); ++i) {
		RelativeRotationSprite::addComponent(std::move(components[i]), relativeOffsets[i]);
	}
}

/// <summary>
/// Initializes the component vectors for Sprite and AnimatedSprite.
/// Throws std::invalid_argument exception if the components and relativeOffsets vectors are not the same size.
/// </summary>
/// <param name="components">The sprites to be added.</param>
/// <param name="animatedComponents">The animated sprites to be added.</param>
/// <param name="relativeOffsets">The relative offsets for the sprites.</param>
void RelativeRotationSprite::initializeComponentVector(std::vector<sf::Sprite> components, std::vector<AnimatedSprite> animatedComponents, const std::vector<sf::Vector2f>& relativeOffsets) {
	if (components.size() + animatedComponents.size() != relativeOffsets.size())
	{
		throw std::invalid_argument("The vector inputs to RelativeRotationSprite::initializeComponentVector must be the same size.");
	}

	// add the components to the CompoundSprite
	for (std::size_t ii = 0; ii < components.size(); ++ii) {
		RelativeRotationSprite::addComponent(std::move(components[ii]), relativeOffsets[ii]);
	}
	for (std::size_t ii = components.size(); ii < components.size() + animatedComponents.size(); ++ii) {
		RelativeRotationSprite::addComponent(std::move(animatedComponents[ii - components.size()]), relativeOffsets[ii]);
	}
}

/// <summary>
/// Set the scale of the RelativeRotation sprite.
/// Scales the components of the RelativeRotation sprite relative to their scale on construction.
/// </summary>
/// <param name="newScaleX">The factor x.</param>
/// <param name="newScaleY">The factor y.</param>
void RelativeRotationSprite::setScale(float newScaleX, float newScaleY) {
	float scaleX = newScaleX / m_currentScale.y;
	float scaleY = newScaleY / m_currentScale.y;

	scale(scaleX, scaleY);
}

/// <summary>
/// Set the scale of the RelativeRotation sprite.
/// Scales the components of the RelativeRotation sprite relative to their scale on construction.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::setScale(sf::Vector2f newScale) {
	float scaleFactorX = newScale.x / m_currentScale.x;
	float scaleFactorY = newScale.y / m_currentScale.y;

	scale({scaleFactorX, scaleFactorY});
}

/// <summary>
/// Get the scale of the full RelativeRotationSprite
/// (This is not always the same as the scale of the component sprites)
/// </summary>
sf::Vector2f RelativeRotationSprite::getScale() const {
	return m_currentScale;
}
