#pragma once
#include "GameBackboneLib.h"
#include "AnimatedSprite.h"

#include<SFML/Graphics/Sprite.hpp>

#include<vector>

class GAMEBACKBONELIB_API CompoundSprite {
public:

	//ctr / dtr
	CompoundSprite();
	CompoundSprite(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
	virtual ~CompoundSprite();

	//getters
	std::vector<sf::Sprite*>* getSfSprites();
	std::vector<AnimatedSprite*>* getaAnimatedSprites();

	//add / remove
	void addSprite(sf::Sprite* component);
	void addAnimatedSprite(AnimatedSprite* component);
	void removeSprite(sf::Sprite* component);
	void removeAnimatedSprite(AnimatedSprite* component);
	void clearComponents();

	//operations
	void scale(float factorX, float factorY);
	void move(float offsetX, float offsetY);

protected:
	std::vector<sf::Sprite*> sprites;
	std::vector<AnimatedSprite*> animatedSprites;
};

