#include "GameWorldSprite.h"
#include <iostream>


/// <summary>
/// Creates a sprite with default parameters at game world position 0,0;
/// </summary>
GameWorldSprite::GameWorldSprite() {}

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldSprite"/> class with a default game world position of 0,0 and a valid texture
/// </summary>
/// <param name="texture">The texture.</param>
GameWorldSprite::GameWorldSprite(const sf::Texture & texture) : sf::Sprite(texture) {}

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldSprite"/> class with a valid texture, a sub-rectangle of the source texture,
/// default game world position of 0, 0.
/// </summary>
/// <param name="texture">The texture.</param>
/// <param name="rectangle">Sub-rectangle of the texture to assign to the sprite.</param>
GameWorldSprite::GameWorldSprite(const sf::Texture & texture, const sf::IntRect & rectangle) : sf::Sprite(texture, rectangle) {}


/// <summary>
/// Finalizes an instance of the <see cref="GameWorldSprite"/> class.
/// </summary>
GameWorldSprite::~GameWorldSprite() {
}

/// <summary>
/// Changes the position of the sprite in the game world by the given offsets.
/// </summary>
/// <param name="xOffset">The x offset.</param>
/// <param name="yOffset">The y offset.</param>
void GameWorldSprite::gMove(double xOffset, double yOffset) {

	move((float)xOffset, (float)yOffset);
	gwPosition.x += xOffset;
	gwPosition.y += yOffset;
}

/// <summary>
/// Do not use this.
/// </summary>
/// <param name="currentTime">The current time.</param>
void GameWorldSprite::update(sf::Time currentTime) {}

/// <summary>
/// Sets the GameWorldSprite active.
/// </summary>
/// <param name="active">if set to <c>true</c> [active].</param>
void GameWorldSprite::setActive(bool active) {
	this->active = active;
}


