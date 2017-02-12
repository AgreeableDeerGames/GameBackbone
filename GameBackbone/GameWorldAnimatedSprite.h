#pragma once
#include "DllUtil.h"
#include "AnimatedSprite.h"
#include "GameWorldSprite.h"

libGameBackbone class GameWorldAnimatedSprite :
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

