#pragma once
#include "DllUtil.h"
#include "CompoundSprite.h"
#include "GameWorldObject.h"
libGameBackbone class GameWorldCompoundSprite2 :
	public CompoundSprite, GameWorldObject {
public:
public:
	GameWorldCompoundSprite2();
	GameWorldCompoundSprite2(const std::vector<sf::Sprite*>& sprites, const std::vector<AnimatedSprite*>& animatedSprites);
	virtual ~GameWorldCompoundSprite2();


	//operations
	virtual void update(sf::Time currentTime);
	virtual void gMove(double xOffset, double yOffset);
	virtual void setActive(bool active);
};

