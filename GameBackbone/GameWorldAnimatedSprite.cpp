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
///<param name = "xOffset"> x offset of the new position</param>
///<param name = "YOffset"> y offset of the new position</param>
void GameWorldAnimatedSprite::gMove(double xOffset, double yOffset) {
	GameWorldSprite::gMove(xOffset, yOffset);
}

void GameWorldAnimatedSprite::setActive(bool active) {
	this->active = active;
}

void GameWorldAnimatedSprite::update(sf::Time currentTime) {
	AnimatedSprite::update(currentTime);
}
