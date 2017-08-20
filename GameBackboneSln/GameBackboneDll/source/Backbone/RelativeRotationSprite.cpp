#include <Backbone\CompoundSprite.h>
#include <Backbone\RelativeRotationSprite.h>

using namespace GB;

// ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. The passed sprites become components of the compound sprite.
/// Animated sprites from the components array are identified via RTTI.
/// and will update when the compound sprite updates.
/// The position of the sprite is (0,0).
/// </summary>
/// <param name="components">The components.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& components)
	: CompoundSprite(components){}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite. The position of the sprite is (0,0)
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) 
	: CompoundSprite(sprites, animatedSprites){}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite.
/// Initializes the sprite to the passed position.
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite.</param>
/// <param name="position">The position.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const sf::Vector2f&  initialPosition)
	: CompoundSprite(sprites, animatedSprites, initialPosition){}


/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(const sf::Vector2f&  initialPosition)
	: CompoundSprite(initialPosition){}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/>. The Compound sprite has no components and is located at (0,0).
/// </summary>
RelativeRotationSprite::RelativeRotationSprite() : CompoundSprite(){}

/// <summary>
/// Finalizes an instance of the <see cref="CompoundSprite"/> class.
/// </summary>
RelativeRotationSprite::~RelativeRotationSprite() {
}


// Add / remove

/// <summary>
/// Adds a sprite component to the CompoundSprite. This sprite's position will be set to the CompoundSprite's position, 
/// and the sprite's origin will be set using the relative offset. 
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New sprite component of the compound sprite.</param>
void RelativeRotationSprite::addComponent(sf::Sprite * component) {
	CompoundSprite::addComponent(component);

	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	component->setPosition(position.x, position.y);
}

/// <summary>
/// Adds a sprite component to the CompoundSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the compound sprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component.</param>
/// <param name="relativeOffset">The relative offset.</param>
void RelativeRotationSprite::addComponent(sf::Sprite* component, sf::Vector2f relativeOffset) {
	CompoundSprite::addComponent(component);

	component->setOrigin(relativeOffset.x, relativeOffset.y);
}


/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite. This sprite's position will be set to the CompoundSprite's position,
/// and the sprite's origin will be set using the relative offset. 
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New Animated Sprite component of the compound sprite.</param>
void RelativeRotationSprite::addComponent(AnimatedSprite * component) {
	CompoundSprite::addComponent(component);

	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	component->setPosition(position.x, position.y);
}

/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the compound sprite.
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
/// Scales all the components of the compound sprite.
/// </summary>
/// <param name="factorX">The new horizontal scale factor.</param>
/// <param name="factorY">The new vertical scale factor.</param>
void RelativeRotationSprite::scale(float factorX, float factorY) {
	CompoundSprite::scale(factorX, factorY);

	//TODO: Stuff with ORIGIN
	for (size_t ii = 0; ii < components.size(); ++ii) {
		components[ii]->setOrigin(factorX*components[ii]->getOrigin().x, factorY*components[ii]->getOrigin().y);
	}
}

/// <summary>
/// Scales all the components of the compound sprite.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::scale(sf::Vector2f newScale) {
	RelativeRotationSprite::scale(newScale.x, newScale.y);
}


/// <summary>
/// Sets the scale factor of all component sprites.
/// </summary>
/// <param name="factorX">The factor x.</param>
/// <param name="factorY">The factor y.</param>
void RelativeRotationSprite::setScale(float factorX, float factorY) {
	//TODO: THROW EXCEPTION for not implemented
}

/// <summary>
/// Sets the scale of all component sprites.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::setScale(sf::Vector2f newScale) {
	//TODO: THROW EXCEPTION for not implemented
}
