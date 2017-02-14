#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "AnimatedSprite.h"
#include "GameWorldSprite.h"

/// <summary> An AnimatedSprite that exists in a game world and tracks its position within the game world. </summary>
 class libGameBackbone GameWorldAnimatedSprite :
			public GameWorldSprite, public AnimatedSprite {
public:
	GameWorldAnimatedSprite();
	explicit GameWorldAnimatedSprite(const sf::Texture &texture);
	GameWorldAnimatedSprite(const sf::Texture &texture, AnimationSet * animations);
	virtual ~GameWorldAnimatedSprite();

	//getters / setters
	virtual void gMove(double xOffset, double yOffset);
	virtual void setActive(bool active);

	//operations
	virtual void update(sf::Time currentTime);
};

