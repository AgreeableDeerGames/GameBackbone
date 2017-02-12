#pragma once
#include "DllUtil.h"
#include "updatable.h"
#include "AnimationSet.h"


#include<SFML/Graphics/Sprite.hpp>

#include <vector>

///<summary> Sprite with the ability to display several animation states. </summary>
libGameBackbone class AnimatedSprite :
	public virtual sf::Sprite, public virtual Updatable {
public:
	//ctr and dtr
	AnimatedSprite();
	explicit AnimatedSprite(const sf::Texture &texture);
	AnimatedSprite(const sf::Texture &texture, AnimationSet * animations);
	virtual ~AnimatedSprite();

	//getters and setters
		//setters
	void setAnimating(bool animating);
	void setCurrentFrame(unsigned int frame);
	void setAnimations(AnimationSet * animations);
	void setAnimationDelay(unsigned int speed);
		//getters
	unsigned int getCurrentFrame();
	unsigned int getCurrentAnimationId();
	unsigned int getAnimationDelay();
	bool isAnimating();
	
	//operations
	void runAnimation(unsigned int animationId);
	virtual void update(sf::Time currentTime);


protected:
	std::vector<std::vector<sf::IntRect>> * animations;
	bool animating;
	unsigned int currentFrame;
	unsigned int currentAnimationId;
	std::vector<sf::IntRect>* currentAnimation;
	unsigned int animationDelay;

	void AnimatedSpriteInit(AnimationSet * animations);

};

