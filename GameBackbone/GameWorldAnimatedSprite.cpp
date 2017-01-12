#include "GameWorldAnimatedSprite.h"



GameWorldAnimatedSprite::GameWorldAnimatedSprite() {
	AnimatedSpriteInit(nullptr);
}

GameWorldAnimatedSprite::GameWorldAnimatedSprite(const sf::Texture & texture) : sf::Sprite(texture){
	AnimatedSpriteInit(nullptr);
}

GameWorldAnimatedSprite::GameWorldAnimatedSprite(const sf::Texture & texture, AnimationSet * animations) : sf::Sprite(texture) {
	AnimatedSpriteInit(animations);
}


GameWorldAnimatedSprite::~GameWorldAnimatedSprite() {
}

///<summary>Changes the position of the sprite in the game world by the given offsets</summary>
void GameWorldAnimatedSprite::gMove(double xOffset, double yOffset) {
	move((float)xOffset, (float)yOffset);
	gx += xOffset;
	gy += yOffset;
}

void GameWorldAnimatedSprite::setActive(bool active) {
	this->active = active;
}

void GameWorldAnimatedSprite::update(sf::Time currentTime) {
	AnimatedSprite::update(currentTime);
}
