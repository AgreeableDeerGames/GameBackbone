#include "GameWorldSprite.h"
#include <iostream>



GameWorldSprite::GameWorldSprite() {}
GameWorldSprite::GameWorldSprite(const sf::Texture & texture) : sf::Sprite(texture) {}
GameWorldSprite::GameWorldSprite(const sf::Texture & texture, const sf::IntRect & rectangle) : sf::Sprite(texture, rectangle) {}


GameWorldSprite::~GameWorldSprite() {
}

///<summary>Changes the position of the sprite in the game world by the given offsets</summary>
void GameWorldSprite::gMove(double xOffset, double yOffset) {

	move((float)xOffset, (float)yOffset);
	gx += xOffset;
	gy += yOffset;
}

void GameWorldSprite::update(sf::Time currentTime) {}

void GameWorldSprite::setActive(bool active) {
	this->active = active;
}


