#include <Backbone\BackboneBaseExceptions.h>
#include <Backbone\CompoundSprite.h>
#include <Backbone\RelativeRotationSprite.h>

using namespace GB;

// ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Animated sprites from the components array are identified via RTTI and will update when the RelativeRotationSprite updates.
/// The position of the sprite is (0,0).
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& components)
	: CompoundSprite() {
	// RTTI
	CompoundSprite::initializeComponentVector(components);
}


/// <summary>
/// Initializes a new instance of the <see cref="RelativeRotationSprite"/> class. The passed sprites become components of the RelativeRotationSprite.
/// Animated sprites from the components array are identified via RTTI and will update when the RelativeRotationSprite updates.
/// Initializes the sprite to the passed position.
///
/// The RelativeRotationSprite's components' offsets will be determined
/// using their current position relative to the RelativeRotationSprite's.
/// </summary>
/// <param name="components">The components of the new RelativeRotationSprite.</param>
/// <param name="initialPosition">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& components, const sf::Vector2f& initialPosition)
	: CompoundSprite(initialPosition) {
	// RTTI
	CompoundSprite::initializeComponentVector(components);
}

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
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& components, const std::vector<sf::Vector2f>& relativeOffsets)
	: CompoundSprite() {
	// RTTI
	initializeComponentVector(components, relativeOffsets);
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
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& components, const std::vector<sf::Vector2f>& relativeOffsets, const sf::Vector2f& initialPosition)
	: CompoundSprite(initialPosition) {
	//RTTI
	initializeComponentVector(components, relativeOffsets);
}

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
	: CompoundSprite(){
	CompoundSprite::initializeComponentVector(sprites, animatedSprites);
}

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
	: CompoundSprite(initialPosition){
	CompoundSprite::initializeComponentVector(sprites, animatedSprites);

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
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const std::vector<sf::Vector2f>& relativeOffsets)
	: CompoundSprite() {
	initializeComponentVector(sprites, animatedSprites, relativeOffsets);
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
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const std::vector<sf::Vector2f>& relativeOffsets, const sf::Vector2f& initialPosition)
	: CompoundSprite(initialPosition) {
	initializeComponentVector(sprites, animatedSprites, relativeOffsets);
}


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
/// <param name="component">New sprite component of the RelativeRotationSprite. Passing nullptr is illegal.</param>
void RelativeRotationSprite::addComponent(sf::Sprite* component) {
	if (component == nullptr){
		throw Error::Pointer_IllegalNull();
	}

	CompoundSprite::addComponent(component);

	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	component->setPosition(position.x, position.y);
}

/// <summary>
/// Adds a sprite component to the RelativeRotationSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the RelativeRotationSprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component. Passing nullptr is illegal.</param>
/// <param name="relativeOffset">The relative offset.</param>
void RelativeRotationSprite::addComponent(sf::Sprite* component, sf::Vector2f relativeOffset) {
	if (component == nullptr) {
		throw Error::Pointer_IllegalNull();
	}

	CompoundSprite::addComponent(component);

	component->setOrigin(relativeOffset.x, relativeOffset.y);
}


/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This sprite's position will be set to the RelativeRotationSprite's position,
/// and the sprite's origin will be set using the relative offset. 
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">New Animated Sprite component of the RelativeRotationSprite. Passing nullptr is illegal.</param>
void RelativeRotationSprite::addComponent(AnimatedSprite* component) {
	if (component == nullptr) {
		throw Error::Pointer_IllegalNull();
	}

	CompoundSprite::addComponent(component);

	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	component->setPosition(position.x, position.y);
}

/// <summary>
/// Adds an AnimatedSprite component to the RelativeRotationSprite. This sprite's origin will be set using the passed in offset.
/// It is expected that the position of the sprite is the same as the RelativeRotationSprite.
/// The position and origin will be updated automatically by the RelativeRotationSprite.
/// </summary>
/// <param name="component">The component. Passing nullptr is illegal.</param>
/// <param name="relativeOffset">The relative offset.</param>
void RelativeRotationSprite::addComponent(AnimatedSprite* component, sf::Vector2f relativeOffset){
	if (component == nullptr) {
		throw Error::Pointer_IllegalNull();
	}

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

	// Scales each of the origins to keep rotating correct.
	for (std::size_t ii = 0; ii < components.size(); ++ii) {
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
/// Initializes the component vector using RTTI and the offset vector.
/// </summary>
/// <param name="components">The components to be added.</param>
/// <param name="relativeOffsets">The relative offsets for each sprite.</param>
void RelativeRotationSprite::initializeComponentVector(const std::vector<sf::Sprite*>& components, const std::vector<sf::Vector2f>& relativeOffsets) {
	if (components.size() != relativeOffsets.size())
	{
		throw Error::RelativeRotationSprite_MismatchedSizes();
	}
	
	// Add any components that are AnimatedSprites to AnimatedSprite storage to allow them to be updated
	for (std::size_t ii = 0; ii < components.size(); ++ii) {
		sf::Sprite* sprite = components[ii];
		AnimatedSprite* animSprite = dynamic_cast<AnimatedSprite*>(sprite);
		if (animSprite) {
			addComponent(animSprite, relativeOffsets[ii]);
		}
		else {
			addComponent(sprite, relativeOffsets[ii]);
		}
	}
}

/// <summary>
/// Initializes the component vector without RTTI and uses the offset vector.
/// </summary>
/// <param name="sprites">The sprites to be added.</param>
/// <param name="animatedSprites">The animated sprites to be added.</param>
/// <param name="relativeOffsets">The relative offsets for the sprites.</param>
void RelativeRotationSprite::initializeComponentVector(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, const std::vector<sf::Vector2f>& relativeOffsets) {
	if (sprites.size() + animatedSprites.size() != relativeOffsets.size())
	{
		throw Error::RelativeRotationSprite_MismatchedSizes();
	}

	for (std::size_t ii = 0; ii < sprites.size(); ++ii) {
		addComponent(sprites[ii], relativeOffsets[ii]);
	}
	for (std::size_t ii = sprites.size(); ii < sprites.size() + animatedSprites.size(); ++ii) {
		addComponent(animatedSprites[ii - sprites.size()], relativeOffsets[ii]);
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
