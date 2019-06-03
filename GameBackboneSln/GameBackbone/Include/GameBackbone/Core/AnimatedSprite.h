#pragma once

#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Sprite.hpp>

#include <cstddef>
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
	class libGameBackbone AnimatedSprite : public sf::Sprite, public Updatable {
	public:
		/// <summary>shared_ptr to an AnimatedSprite</summary>
		using Ptr = std::shared_ptr<AnimatedSprite>;

		//ctr and dtr
		//shallow copy and move are fine for this class
		AnimatedSprite();
		explicit AnimatedSprite(const sf::Texture& texture);
		AnimatedSprite(const sf::Texture& texture, AnimationSet::Ptr animations);
		AnimatedSprite(const AnimatedSprite& other) = default;
		AnimatedSprite& operator=(const AnimatedSprite& other) = default;
		AnimatedSprite(AnimatedSprite&& other) noexcept = default;
		AnimatedSprite& operator=(AnimatedSprite&& other) noexcept = default;
		virtual ~AnimatedSprite() = default;

		//getters and setters
			//setters
		void setAnimating(bool animating);
		void setCurrentFrame(unsigned int frame);
		void setAnimations(AnimationSet::Ptr animations);
		void setAnimationDelay(sf::Time delay);

			//getters
		unsigned int getCurrentFrame() const;
		unsigned int getCurrentAnimationId() const;
		sf::Time getAnimationDelay() const;
		unsigned int getFramesSpentInCurrentAnimation() const;
		bool isAnimating() const;
		bool willFitToFrame() const;

		//operations
		void runAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle);
		void runAnimation(unsigned int animationId);
		virtual void update(sf::Int64 elapsedTime);

	protected:
		bool animating;
		bool isReverse;
		ANIMATION_END_TYPE animationEnd;
		sf::Time animationDelay;
		sf::Time timeSinceLastUpdate;
		
		unsigned int currentFrame;
		unsigned int framesSpentInCurrentAnimation;
		std::size_t currentAnimationId;
		const Animation* currentAnimation;
		AnimationSet::Ptr animations;
	};
}