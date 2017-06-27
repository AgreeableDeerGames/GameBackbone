#pragma once

#include <Backbone\AnimationSet.h>
#include <Backbone\Updatable.h>
#include <Util\DllUtil.h>

#include <SFML\Graphics\Sprite.hpp>

#include <vector>

namespace GB {
	
	/// <summary>
	/// Animation behaviors after animation end is reached.
	/// </summary>
	enum ANIMATION_END_TYPE
	{
		ANIMATION_LOOP,
		ANIMATION_REVERSE,
		ANIMATION_STOP
	};
	
	/// <summary>
	/// Sprite with the ability to display several animation states.
	/// </summary>
	/// <seealso cref="sf::Sprite" />
	/// <seealso cref="Updatable" />
	class libGameBackbone AnimatedSprite :
		public virtual sf::Sprite, public virtual Updatable {
	public:
		//ctr and dtr
		//shallow copy and move are fine for this class
		AnimatedSprite();
		explicit AnimatedSprite(const sf::Texture &texture);
		AnimatedSprite(const sf::Texture &texture, AnimationSet * animations);
		AnimatedSprite(const AnimatedSprite& other) = default;
		AnimatedSprite(AnimatedSprite&& other) = default;
		AnimatedSprite& operator= (const AnimatedSprite& other) = default;
		AnimatedSprite& operator= (AnimatedSprite&& other) = default;
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
		void runAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle);
		virtual void update(sf::Time currentTime);

	protected:
		std::vector<std::vector<sf::IntRect>> * animations;
		bool animating;
		ANIMATION_END_TYPE animationEnd;
		unsigned int currentFrame;
		unsigned int currentAnimationId;
		std::vector<sf::IntRect>* currentAnimation;
		unsigned int animationDelay;
		bool isReverse;

		void AnimatedSpriteInit(AnimationSet * animations);

	};

}
