#include "GameWorldCompoundSprite2.h"


GameWorldCompoundSprite2::GameWorldCompoundSprite2() {
}					   

GameWorldCompoundSprite2::GameWorldCompoundSprite2(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) : CompoundSprite(sprites, animatedSprites) {
}					   
					   
					   
GameWorldCompoundSprite2::~GameWorldCompoundSprite2() {
}


//operations

///<summary>updates each animated sprite in the compound sprite</summary>
///<param name = "currentTime"> game time of the update call </param>
void GameWorldCompoundSprite2::update(sf::Time currentTime) {
	CompoundSprite::update(currentTime);
}

///<summary>Changes the position of the GameWorldCompoundSprite in the game world by the given offsets</summary>
///<param name = "xOffset"> x offset of the new position</param>
///<param name = "YOffset"> y offset of the new position</param>
void GameWorldCompoundSprite2::gMove(double xOffset, double yOffset) {
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->move((float)xOffset, (float)yOffset);
	}
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->move((float)xOffset, (float)yOffset);
	}
	gx += xOffset;
	gy += yOffset;
}

void GameWorldCompoundSprite2::setActive(bool active) {
	this->active = active;
}
