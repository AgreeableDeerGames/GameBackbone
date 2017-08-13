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
	: CompoundSprite(sprites, animatedSprites), unscaledOrigin({0, 0}) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite.
/// Initializes the sprite to the passed position.
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite.</param>
/// <param name="position">The position.</param>
RelativeRotationSprite::RelativeRotationSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, Point2D<float> initialPosition) 
	: CompoundSprite(sprites, animatedSprites, initialPosition), unscaledOrigin({0, 0}) {}


/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
RelativeRotationSprite::RelativeRotationSprite(const Point2D<float> initialPosition)
	: CompoundSprite(initialPosition), unscaledOrigin({0, 0}) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/>. The Compound sprite has no components and is located at (0,0).
/// </summary>
RelativeRotationSprite::RelativeRotationSprite() : CompoundSprite(), unscaledOrigin({0, 0}) {}

/// <summary>
/// Finalizes an instance of the <see cref="CompoundSprite"/> class.
/// </summary>
RelativeRotationSprite::~RelativeRotationSprite() {
}

Point2D<float> RelativeRotationSprite::getUnscaledOrigin() const {
	return unscaledOrigin;
}

void RelativeRotationSprite::setUnscaledOrigin(Point2D<float> val) {
	unscaledOrigin = val;
}

void RelativeRotationSprite::setUnscaledOrigin(float x, float y){
	unscaledOrigin = {x, y};
}
