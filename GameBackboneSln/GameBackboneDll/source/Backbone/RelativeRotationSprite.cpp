#include <Backbone\BackboneBaseExceptions.h>
#include <Backbone\CompoundSprite.h>
#include <Backbone\RelativeRotationSprite.h>

using namespace GB;

// ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Animated sprites from the components array are identified via RTTI
/// and will update when the compound sprite updates.
/// The position of the sprite is (0,0).
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& components)
	: CompoundSprite(components){}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite. The position of the sprite is (0,0)
/// The position of the sprite is (0,0).
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="sprites">Sprite components of the new RelativeRotationSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new RelativeRotationSprite</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) 
	: CompoundSprite(sprites, animatedSprites){}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the RelativeRotationSprite.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="sprites">Sprite components of the new RelativeRotationSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new RelativeRotationSprite.</param>
/// <param name="position">The position.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const sf::Vector2f&  initialPosition)
	: CompoundSprite(sprites, animatedSprites, initialPosition){}


/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. Sets the initial position of the RelativeRotationSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(const sf::Vector2f&  initialPosition)
	: CompoundSprite(initialPosition){}

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/>. The RelativeRotationSprite has no components and is located at (0,0).
/// </summary>
RelativeRotationSprite::RelativeRotationSprite() : CompoundSprite(){}

/// <summary>
/// Finalizes an instance of the <see cref="RelativeRotationSprite"/> class.
/// </summary>
RelativeRotationSprite::~RelativeRotationSprite() {
}


// Add / remove

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite. This sprite's position will be set to the RelativeRotationSprite's position, 
/// and the sprite's origin will be set using the relative offset. 
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New sprite component of the RelativeRotationSprite.</param>
void RelativeRotationSprite::addComponent(sf::Sprite * component) {
	CompoundSprite::addComponent(component);

	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	component->setPosition(position.x, position.y);
}

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the RelativeRotationSprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component.</param>
/// <param name="relativeOffset">The relative offset.</param>
void RelativeRotationSprite::addComponent(sf::Sprite* component, sf::Vector2f relativeOffset) {
	CompoundSprite::addComponent(component);

	component->setOrigin(relativeOffset.x, relativeOffset.y);
}


/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This sprite's position will be set to the RelativeRotationSprite's position,
/// and the sprite's origin will be set using the relative offset. 
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New Animated Sprite component of the RelativeRotationSprite.</param>
void RelativeRotationSprite::addComponent(AnimatedSprite * component) {
	CompoundSprite::addComponent(component);

	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	component->setPosition(position.x, position.y);
}

/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the RelativeRotationSprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component.</param>
/// <param name="relativeOffset">The relative offset.</param>
void RelativeRotationSprite::addComponent(AnimatedSprite* component, sf::Vector2f relativeOffset){
	CompoundSprite::addComponent(component);

	component->setOrigin(relativeOffset.x, relativeOffset.y);
}



// operations

/// <summary>
/// Scales all the components of the RelativeRotationSprite.
/// </summary>
/// <param name="factorX">The new horizontal scale factor.</param>
/// <param name="factorY">The new vertical scale factor.</param>
void RelativeRotationSprite::scale(float factorX, float factorY) {
	CompoundSprite::scale(factorX, factorY);

	// Scales ech of the origins to keep rotating correct.
	for (size_t ii = 0; ii < components.size(); ++ii) {
		components[ii]->setOrigin(factorX*components[ii]->getOrigin().x, factorY*components[ii]->getOrigin().y);
	}
}

/// <summary>
/// Scales all the components of the RelativeRotationSprite.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::scale(sf::Vector2f newScale) {
	RelativeRotationSprite::scale(newScale.x, newScale.y);
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
