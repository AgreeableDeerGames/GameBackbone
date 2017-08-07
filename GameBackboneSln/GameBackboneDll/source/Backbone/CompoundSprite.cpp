#include <Backbone\CompoundSprite.h>

#include<algorithm>

using namespace GB;

// ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite. The position of the sprite is (0,0)
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
CompoundSprite::CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) : CompoundSprite(sprites, animatedSprites, {0,0}) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite.
/// Initializes the sprite to the passed position.
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite.</param>
/// <param name="position">The position.</param>
CompoundSprite::CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites, Point2D<float> initialPosition) : position(initialPosition) {
	for (auto component : sprites) {
		this->sprites.push_back(component);
	}
	for (auto component : animatedSprites) {
		this->animatedSprites.push_back(component);
	}
}


/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Sets the initial position of the CompoundSprite to the passed value.
/// </summary>
/// <param name="initialPosition">The initial position.</param>
CompoundSprite::CompoundSprite(const Point2D<float> initialPosition) : position(initialPosition) {}

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/>. The Compound sprite has no components and is located at (0,0).
/// </summary>
CompoundSprite::CompoundSprite() : position({ 0,0 }) {}

/// <summary>
/// Finalizes an instance of the <see cref="CompoundSprite"/> class.
/// </summary>
CompoundSprite::~CompoundSprite() {
}

// getters

/// <summary>
/// returns the non animated sprite components of the CompoundSprite
/// </summary>
/// <returns>The non animated sprite components of the CompoundSprite.</returns>
std::vector<sf::Sprite*>* CompoundSprite::getSfSprites() {
	return &sprites;
}

/// <summary>
/// Returns the animated sprite components of the CompoundSprite
/// </summary>
/// <returns>The animated sprite components of the CompoundSprite.</returns>
std::vector<AnimatedSprite*>* CompoundSprite::getAnimatedSprites() {
	return &animatedSprites;
}


/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
Point2D<float> GB::CompoundSprite::getPosition() const {
	return position;
}

// setters

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="val">The value.</param>
void CompoundSprite::setPosition(GB::Point2D<float> val) {
	Point2D<float> oldPosition = position;
	Point2D<float> positionDifference{ position.x - oldPosition.x, position.y - oldPosition.y };

	move(positionDifference.x, positionDifference.y);
}

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="x">The new x.</param>
/// <param name="y">The new y.</param>
void CompoundSprite::setPosition(float x, float y) {
	setPosition({ x,y });
}



// Add / remove

/// <summary>
/// adds a sprite component to the CompoundSprite
/// </summary>
/// <param name="component">new sprite component of the compound sprite.</param>
void CompoundSprite::addSprite(sf::Sprite * component) {
	sprites.push_back(component);
	component->setOrigin(position.x - component->getPosition().x, position.y - component->getPosition().y);
}

/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite
/// </summary>
/// <param name="component">New Animated Sprite component of the compound sprite.</param>
void CompoundSprite::addAnimatedSprite(AnimatedSprite * component) {
	animatedSprites.push_back(component);
	component->setOrigin(position.x - component->getPosition().x, position.y - component->getPosition().y);
}

/// <summary>
/// Removes the passed component from the CompoundSprite
/// </summary>
/// <param name="component">The component to remove from the compound sprite</param>
void CompoundSprite::removeSprite(sf::Sprite * component) {
	auto it = std::find(sprites.begin(), sprites.end(), component);
	if (it != sprites.end()) {
		sprites.erase(it);
	}
}

/// <summary>
/// Removes the passed component from the CompoundSprite.
/// </summary>
/// <param name="component">The component to remove from the compound sprite. </param>
void CompoundSprite::removeAnimatedSprite(AnimatedSprite * component) {
	auto it = std::find(animatedSprites.begin(), animatedSprites.end(), component);
	if (it != animatedSprites.end()) {
		animatedSprites.erase(it);
	}
}


/// <summary>
/// Removes all components from the compound sprite
/// </summary>
void CompoundSprite::clearComponents() {
	sprites.clear();
	animatedSprites.clear();
}

// operations

/// <summary>
/// Scales all the components of the compound sprite.
/// </summary>
/// <param name="factorX">The new horizontal scale factor.</param>
/// <param name="factorY">The new vertical scale factor.</param>
void CompoundSprite::scale(float factorX, float factorY) {
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->scale(factorX, factorY);
	}
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->scale(factorX, factorY);
	}
}

/// <summary>
/// Scales all the components of the compound sprite.
/// </summary>
/// <param name="newScale">The new scale.</param>
void CompoundSprite::scale(Point2D<float> newScale) {
	scale(newScale.x, newScale.y);
}

/// <summary>
/// Rotates all components of the compound sprite.
/// </summary>
/// <param name="degreeOffset">The offset to the current rotation.</param>
void CompoundSprite::rotate(float degreeOffset) {
	for (auto sprite : sprites) {
		sprite->rotate(degreeOffset);
	}
	for (auto sprite : animatedSprites) {
		sprite->rotate(degreeOffset);
	}
}

/// <summary>
/// Sets the of all components in the compound sprite.
/// </summary>
/// <param name="newRotation">The new rotation.</param>
void CompoundSprite::setRotation(float newRotation) {
	for (auto sprite : sprites) {
		sprite->setRotation(newRotation);
	}
	for (auto sprite : animatedSprites) {
		sprite->setRotation(newRotation);
	}
}

/// <summary>
/// Rotates the animated sprite components at the passed indices by the.
/// </summary>
/// <param name="indicesToRotate">The indices to rotate.</param>
/// <param name="degreeOffset">The offset to the current rotation..</param>
void CompoundSprite::rotateAnimatedSprites(std::set<size_t> indicesToRotate, float degreeOffset) {
	for (size_t index : indicesToRotate) {
		animatedSprites.at(index)->rotate(degreeOffset);
	}
}

/// <summary>
/// Sets the rotation of the animated sprite components at the passed indices.
/// </summary>
/// <param name="indicesToRotate">The indices to rotate.</param>
/// <param name="newRotation">The new rotation of the sprite.</param>
void CompoundSprite::setRotationAnimatedSprites(std::set<size_t> indicesToRotate, float newRotation) {
	for (size_t index : indicesToRotate) {
		animatedSprites.at(index)->setRotation(newRotation);
	}
}

/// <summary>
/// Rotates the sf sprite components of the compound sprite by the passed offset.
/// </summary>
/// <param name="indicesToRotate">The indices to rotate.</param>
/// <param name="degreeOffset">The offset to the current rotation.</param>
void CompoundSprite::rotateSfSprites(std::set<size_t> indicesToRotate, float degreeOffset) {
	for (size_t index : indicesToRotate) {
		sprites.at(index)->rotate(degreeOffset);
	}
}

/// <summary>
/// Sets the rotation of the sprite components at the passed indices.
/// </summary>
/// <param name="indicesToRotate">The indices to rotate.</param>
/// <param name="newRotation">The new rotation.</param>
void CompoundSprite::setRotationSfSprites(std::set<size_t> indicesToRotate, float newRotation) {
	for (size_t index : indicesToRotate) {
		sprites.at(index)->setRotation(newRotation);
	}
}

/// <summary>
/// Moves all the components of the compound sprite by the same offset.
/// </summary>
/// <param name="offsetX">The offset x.</param>
/// <param name="offsetY">The offset y.</param>
void CompoundSprite::move(float offsetX, float offsetY) {
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->move(offsetX, offsetY);
	}
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->move(offsetX, offsetY);
	}
	position.x += offsetX;
	position.y += offsetY;
}

/// <summary>
/// Moves all the components of the compound sprite by the same offset.
/// </summary>
/// <param name="offset">The offset.</param>
void CompoundSprite::move(Point2D<float> offset) {
	move(offset.x, offset.y);
}

/// <summary>
/// Updates each animated sprite in the compound sprite.
/// </summary>
/// <param name="currentTime">The current time.</param>
void CompoundSprite::update(sf::Time currentTime) {
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->update(currentTime);
	}
}
