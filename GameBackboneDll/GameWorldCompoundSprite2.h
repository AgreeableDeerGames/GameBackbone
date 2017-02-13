#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "CompoundSprite.h"
#include "GameWorldObject.h"

/// <summary> A CompoundSprite that exists withing a game world and tracks its position withing the game world. </summary>
class libGameBackbone GameWorldCompoundSprite2 :
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

