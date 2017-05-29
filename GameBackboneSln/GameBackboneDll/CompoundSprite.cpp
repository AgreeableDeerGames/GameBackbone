#include "stdafx.h"
#include "CompoundSprite.h"

#include<algorithm>

using namespace GB;

//ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="CompoundSprite"/> class. Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite 
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
CompoundSprite::CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) {
	for (auto component : sprites) {
		this->sprites.push_back(component);
	}
	for (auto component : animatedSprites) {
		this->animatedSprites.push_back(component);
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="CompoundSprite"/> class.
/// </summary>
CompoundSprite::~CompoundSprite() {
}

//getters

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

//Add / remove

/// <summary>
/// adds a sprite component to the CompoundSprite
/// </summary>
/// <param name="component">new sprite component of the compound sprite.</param>
void CompoundSprite::addSprite(sf::Sprite * component) {
	sprites.push_back(component);
}

/// <summary>
/// Adds an AnimatedSprite component to the CompoundSprite
/// </summary>
/// <param name="component">New Animated Sprite component of the compound sprite.</param>
void CompoundSprite::addAnimatedSprite(AnimatedSprite * component) {
	animatedSprites.push_back(component);
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

//operations

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

