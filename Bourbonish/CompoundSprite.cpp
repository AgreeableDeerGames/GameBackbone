#include "CompoundSprite.h"

#include<algorithm>


//ctr / dtr
CompoundSprite::CompoundSprite() {
}

///<summary> stores the passed sprites and animatedSprites as components of the CompoundSprite </summary>
///<param name = "sprites">Sprite components of the new CompoundSprite</param>
///<param name = "animatedSprites">AnimatedSprite components of the new CompoundSprite</param>
CompoundSprite::CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites) {
	for (auto component : sprites) {
		this->sprites.push_back(component);
	}
	for (auto component : animatedSprites) {
		this->animatedSprites.push_back(component);
	}
}


CompoundSprite::~CompoundSprite() {
}

//getters

///<summary>returns the non animated sprite components of the CompoundSprite</summary>
std::vector<sf::Sprite*>* CompoundSprite::getSfSprites() {
	return &sprites;
}

///<summary>returns the animated sprite components of the CompoundSprite</summary>
std::vector<AnimatedSprite*>* CompoundSprite::getaAnimatedSprites() {
	return &animatedSprites;
}

//Add / remove

///<summary>adds a sprite component to the CompoundSprite</summary>
///<param name = "component"> new sprite component of the compound sprite </param>
void CompoundSprite::addSprite(sf::Sprite * component) {
	sprites.push_back(component);
}


///<summary>adds an AnimatedSprite component to the CompoundSprite</summary>
///<param name = "component"> new Animated Sprite component of the compound sprite </param>
void CompoundSprite::addAnimatedSprite(AnimatedSprite * component) {
	animatedSprites.push_back(component);
}

///<summary>removes the passed component from the CompoundSprite</summary>
///<param name = "component"> component to remove from the compound sprite </param>
void CompoundSprite::removeSprite(sf::Sprite * component) {
	auto it = std::find(sprites.begin(), sprites.end(), component);
	if (it != sprites.end()) {
		sprites.erase(it);
	}
}


///<summary>removes the passed component from the CompoundSprite</summary>
///<param name = "component"> component to remove from the compound sprite </param>
void CompoundSprite::removeAnimatedSprite(AnimatedSprite * component) {
	auto it = std::find(animatedSprites.begin(), animatedSprites.end(), component);
	if (it != animatedSprites.end()) {
		animatedSprites.erase(it);
	}
}

///<summary> removes all components from the compound sprite</summary>
void CompoundSprite::clearComponents() {
	sprites.clear();
	animatedSprites.clear();
}

//operations

///<summary> scales all the components of the compound sprite </summary>
///<param name = "factorX"> the new horizontal scale factor </param>
///<param name = "factorY"> the new vertical scale factor </param>
void CompoundSprite::scale(float factorX, float factorY) {
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->scale(factorX, factorY);
	}
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->scale(factorX, factorY);
	}
}

///<summary> moves all the components of the compound sprite by the same offset</summary>
///<param name = "offsetX"> X offset of new position. </param>
///<param name = "offsetY"> Y offset of new position. </param>
void CompoundSprite::move(float offsetX, float offsetY) {
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->move(offsetX, offsetY);
	}
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->scale(offsetX, offsetY);
	}
}

///<summary>updates each animated sprite in the compound sprite</summary>
///<param name = "currentTime"> game time of the update call </param>
void CompoundSprite::update(sf::Time currentTime) {
	for (size_t i = 0; i < animatedSprites.size(); i++) {
		animatedSprites[i]->update(currentTime);
	}
}

