#include "GameWorldCompoundSprite2.h"


GameWorldCompoundSprite2::GameWorldCompoundSprite2() {
}					   

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldCompoundSprite2"/> class.  Stores the passed groups of sf::Sprite and AnimatedSprite as components of the CompoundSprite.
/// </summary>
/// <param name="sprites">Sprite components of the new CompoundSprite.</param>
/// <param name="animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
GameWorldCompoundSprite2::GameWorldCompoundSprite2(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) : CompoundSprite(sprites, animatedSprites) {
}					   
					   					   
/// <summary>
/// Finalizes an instance of the <see cref="GameWorldCompoundSprite2"/> class.
/// </summary>
GameWorldCompoundSprite2::~GameWorldCompoundSprite2() {
}


//operations

/// <summary>
/// Updates each animated sprite in the GameWorldCompoundSprite2.
/// </summary>
/// <param name="currentTime">The current time.</param>
void GameWorldCompoundSprite2::update(sf::Time currentTime) {
	CompoundSprite::update(currentTime);
}

/// <summary>
/// Changes the position of the GameWorldCompoundSprite2 in the game world by the given offsets.
/// </summary>
/// <param name="xOffset">X offset of the new position.</param>
/// <param name="yOffset">Y offset of the new position.</param>
void GameWorldCompoundSprite2::gMove(double xOffset, double yOffset) {
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->move((float)xOffset, (float)yOffset);
	}
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->move((float)xOffset, (float)yOffset);
	}
	gwPosition.x += xOffset;
	gwPosition.y += yOffset;
}

/// <summary>
/// Sets the GameWorldCompoundSprite2 active.
/// </summary>
/// <param name="active">if set to <c>true</c> [active].</param>
void GameWorldCompoundSprite2::setActive(bool active) {
	this->active = active;
}
