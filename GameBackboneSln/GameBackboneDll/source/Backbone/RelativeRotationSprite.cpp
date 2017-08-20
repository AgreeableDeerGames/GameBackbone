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
/*
Point2D<float> RelativeRotationSprite::getUnscaledOrigin() const {
	return unscaledOrigin;
}

void RelativeRotationSprite::setUnscaledOrigin(Point2D<float> val) {
	unscaledOrigin = val;
}

void RelativeRotationSprite::setUnscaledOrigin(float x, float y){
	unscaledOrigin = {x, y};
}*/


// Add / remove

/// <summary>
/// adds a sprite component to the CompoundSprite
/// </summary>
/// <param name="component">new sprite component of the compound sprite.</param>
void RelativeRotationSprite::addComponent(sf::Sprite * component) {
	CompoundSprite::addComponent(component);

	//TODO: Stuff with ORIGIN
	component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);

	//component->setOrigin(component->getPosition().x - position.x, component->getPosition().y - position.y);
	//component->setOrigin(position.x, position.y);
}

void RelativeRotationSprite::addComponent(sf::Sprite* component, Point2D<float> relativeOffset) {
	CompoundSprite::addComponent(component);

	//TODO: Stuff with ORIGIN
	component->setOrigin(relativeOffset.x, relativeOffset.y);
}


/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite
/// </summary>
/// <param name="component">New Animated Sprite component of the compound sprite.</param>
void RelativeRotationSprite::addComponent(AnimatedSprite * component) {
	CompoundSprite::addComponent(component);

	//TODO: Stuff with ORIGIN
}

void RelativeRotationSprite::addComponent(AnimatedSprite* component, Point2D<float> relativeOffset){
	CompoundSprite::addComponent(component);

	//TODO: Stuff with ORIGIN
}


void RelativeRotationSprite::removeComponent(sf::Sprite* component) {
	auto it = std::find(components.begin(), components.end(), component);
	int index = it - components.begin();

	CompoundSprite::removeComponent(component);

	//TODO: Remove things from vectors
}

void RelativeRotationSprite::clearComponents(){
	CompoundSprite::clearComponents();

	//TODO: Remove things from vectors
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
	/*for (size_t ii = 0; ii < animatedSprites.size(); ++ii) {
		animatedSprites[ii]->scale(factorX*animatedSprites[ii]->getOrigin().x, factorY*animatedSprites[ii]->getOrigin().y);
	}*/
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
