#pragma once

#include "../../SFML/SFML-2.4.1/include/SFML/Graphics/Sprite.hpp"
#include "updatable.h"
#include "AnimationSet.h"

#include <vector>


class AnimatedSprite :
	public sf::Sprite, public Updatable {
public:
	//ctr and dtr
	AnimatedSprite();
	AnimatedSprite(const sf::Texture &texture);
	AnimatedSprite(const sf::Texture &texture, AnimationSet * animations);
	virtual ~AnimatedSprite();

	//getters and setters
		//setters
	void setAnimating(bool animating);
	void setCurrentFrame(unsigned int frame);
	void setAnimations(AnimationSet * animations);
		//getters
	unsigned int getCurrentFrame();
	unsigned int getCurrentAnimationId();
	bool isAnimating();
	
	//operations
	void runAnimation(unsigned int animationId);
	virtual void update();


protected:
	std::vector<std::vector<sf::IntRect>> * animations;
	bool animating;
	unsigned int currentFrame;
	unsigned int currentAnimationId;
	//std::vector<sf::IntRect>* currentAnimation;

private:
	void init();

};

