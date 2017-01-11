#pragma once
#include "AnimatedSprite.h"
#include "GameWorldSprite.h"
class GameWorldAnimatedSprite :
	 public GameWorldSprite, public AnimatedSprite {
public:
	GameWorldAnimatedSprite();
	GameWorldAnimatedSprite(const sf::Texture &texture);
	GameWorldAnimatedSprite(const sf::Texture &texture, AnimationSet * animations);
	virtual ~GameWorldAnimatedSprite();

	virtual void update(sf::Time currentTime);

};

