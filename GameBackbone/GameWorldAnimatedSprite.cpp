#include "GameWorldAnimatedSprite.h"



GameWorldAnimatedSprite::GameWorldAnimatedSprite() {
}

GameWorldAnimatedSprite::GameWorldAnimatedSprite(const sf::Texture & texture) : AnimatedSprite(texture){
}

GameWorldAnimatedSprite::GameWorldAnimatedSprite(const sf::Texture & texture, AnimationSet * animations) : AnimatedSprite(texture, animations) {
}


GameWorldAnimatedSprite::~GameWorldAnimatedSprite() {
}

void GameWorldAnimatedSprite::update(sf::Time currentTime) {
	AnimatedSprite::update(currentTime);
}
