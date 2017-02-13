#include "stdafx.h"
#include "GameWorldAnimatedSprite.h"


/// <summary>
/// Initializes a new instance of the <see cref="GameWorldAnimatedSprite"/> class. No texture or animations are assigned.
/// </summary>
GameWorldAnimatedSprite::GameWorldAnimatedSprite() {
	AnimatedSpriteInit(nullptr);
}

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldAnimatedSprite"/> class. The GameWorldAnimatedSprite is given a texture, but is given no animations.
/// </summary>
/// <param name="texture">The texture.</param>
GameWorldAnimatedSprite::GameWorldAnimatedSprite(const sf::Texture & texture) : sf::Sprite(texture) {
	AnimatedSpriteInit(nullptr);
}

/// <summary>
/// Initializes a new instance of the <see cref="GameWorldAnimatedSprite"/> class. The GameWorldAnimatedSprite is given a texture, and assigned animations.
/// The first frame of the first animation is set to active.
/// </summary>
/// <param name="texture">The texture.</param>
/// <param name="animations">The animations.</param>
GameWorldAnimatedSprite::GameWorldAnimatedSprite(const sf::Texture & texture, AnimationSet * animations) : sf::Sprite(texture) {
	AnimatedSpriteInit(animations);
}

/// <summary>
/// Finalizes an instance of the <see cref="GameWorldAnimatedSprite"/> class.
/// </summary>
GameWorldAnimatedSprite::~GameWorldAnimatedSprite() {
}

/// <summary>
/// Changes the position of the sprite in the game world by the given offsets
/// </summary>
/// <param name="xOffset">The x offset.</param>
/// <param name="yOffset">The y offset.</param>
void GameWorldAnimatedSprite::gMove(double xOffset, double yOffset) {
	GameWorldSprite::gMove(xOffset, yOffset);
}

/// <summary>
/// Sets the GameWorldAnimatedSprite active.
/// </summary>
/// <param name="active">if set to <c>true</c> [active].</param>
void GameWorldAnimatedSprite::setActive(bool active) {
	this->active = active;
}

/// <summary>
/// Moves the next frame of the active animation if the sprite is animating.
/// </summary>
/// <param name="currentTime">The current time.</param>
void GameWorldAnimatedSprite::update(sf::Time currentTime) {
	AnimatedSprite::update(currentTime);
}
