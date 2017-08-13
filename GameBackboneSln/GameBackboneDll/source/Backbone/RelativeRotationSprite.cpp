#include <Backbone\CompoundSprite.h>
#include <Backbone\RelativeRotationSprite.h>

using namespace GB;

// ctr / dtr

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
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, Point2D<float> initialPosition) 
	: CompoundSprite(sprites, animatedSprites, initialPosition){}


/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(const Point2D<float> initialPosition)
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
void RelativeRotationSprite::addSprite(sf::Sprite * component) {
	CompoundSprite::addSprite(component);

	//TODO: Stuff with ORIGIN
}

void RelativeRotationSprite::addSprite(sf::Sprite* component, Point2D<float> relativeOffset) {
	CompoundSprite::addSprite(component);

	//TODO: Stuff with ORIGIN
}


/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite
/// </summary>
/// <param name="component">New Animated Sprite component of the compound sprite.</param>
void RelativeRotationSprite::addAnimatedSprite(AnimatedSprite * component) {
	CompoundSprite::addAnimatedSprite(component);

	//TODO: Stuff with ORIGIN
}

void RelativeRotationSprite::addAnimatedSprite(AnimatedSprite* component, Point2D<float> relativeOffset){
	CompoundSprite::addAnimatedSprite(component);

	//TODO: Stuff with ORIGIN
}


void RelativeRotationSprite::removeSprite(sf::Sprite* component) {
	auto it = std::find(sprites.begin(), sprites.end(), component);
	int index = it - sprites.begin();

	CompoundSprite::removeSprite(component);

	//TODO: Remove things from vectors
}

void RelativeRotationSprite::removeAnimatedSprite(AnimatedSprite* component) {
	auto it = std::find(animatedSprites.begin(), animatedSprites.end(), component);
	int index = it - animatedSprites.begin();

	CompoundSprite::removeAnimatedSprite(component);

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
	for (size_t ii = 0; ii < sprites.size(); ++ii) {
		sprites[ii]->setOrigin(factorX*sprites[ii]->getOrigin().x, factorY*sprites[ii]->getOrigin().y);
	}
	for (size_t ii = 0; ii < animatedSprites.size(); ++ii) {
		animatedSprites[ii]->scale(factorX*animatedSprites[ii]->getOrigin().x, factorY*animatedSprites[ii]->getOrigin().y);
	}
}

/// <summary>
/// Scales all the components of the compound sprite.
/// </summary>
/// <param name="newScale">The new scale.</param>
void RelativeRotationSprite::scale(Point2D<float> newScale) {
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
void RelativeRotationSprite::setScale(Point2D<float> newScale) {
	//TODO: THROW EXCEPTION for not implemented
}
