#pragma once

#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/DllUtil.h>

#include <SFML/Graphics/Sprite.hpp>

#include <cstddef>
#include <vector>

namespace GB {

	/// @brief Animation behaviors after animation end is reached.
	enum ANIMATION_END_TYPE
	{
		ANIMATION_LOOP,
		ANIMATION_REVERSE,
		ANIMATION_STOP
	};

	/// @brief Sprite with the ability to display several animation states.
	class libGameBackbone AnimatedSprite : public sf::Sprite, public Updatable {
	public:
		
		/// @brief y>shared_ptr to an AnimatedSprite
		using Ptr = std::shared_ptr<AnimatedSprite>;

		/// @brief Create a new AnimatedSprite with an empty texture. All values are initialized to 0, nullptr, or false.
		AnimatedSprite();

		/// @brief Initializes a new instance of the <see cref="AnimatedSprite"/> class. Texture set to passed value. Position set to 0.
		/// @param texture The texture.
		explicit AnimatedSprite(const sf::Texture& texture);

		/// @brief Initializes a new instance of the <see cref="AnimatedSprite"/> class. Initializes texture to first frame of first animation.
		/// @param texture A texture representing the animation sheet.
		/// @param animations The animations.
		AnimatedSprite(const sf::Texture& texture, AnimationSet::Ptr animations);

		/// @brief Copy construct an AnimatedSprite
		/// @param other The AnimatedSprite to copy
		AnimatedSprite(const AnimatedSprite& other) = default;

		/// @brief Copy assign an AnimatedSprite
		/// @param other The AnimatedSprite to copy
		/// @return This
		AnimatedSprite& operator=(const AnimatedSprite& other) = default;

		/// @brief Move construct an AnimatedSprite
		/// @param other The AnimatedSprite to move
		AnimatedSprite(AnimatedSprite&& other) noexcept = default;

		/// @brief Move assign an AnimatedSprite
		/// @param other The AnimatedSprite to move
		/// @return This
		AnimatedSprite& operator=(AnimatedSprite&& other) noexcept = default;

		/// @brief Destroy the AnimatedSprite
		~AnimatedSprite() override = default;

		/// @brief Whether or not the AnimatedSprite is currently playing an animation
		/// @param animating True if the AnimatedSprite should animate. False otherwise.
		void setAnimating(bool animating);

		/// @brief Sets the current frame (within the current animation) of the AnimatedSprite.
		///		Immediately updates the texture displayed on the sprite.
		/// @param frame The frame.
		/// @throws std::runtime_error if there is no active animation (runAnimation has not been called).
		void setCurrentFrame(unsigned int frame);

		/// @brief Updates the sprite to use the provided AnimationSet.
		///		The current frame of the sprite is set to the first frame of the AnimationSet's first Animation
		///		If the provided AnimationSet is empty an out_of_bounds exception is thrown.
		/// @param animations The new AnimationSet to use.
		void setAnimations(AnimationSet::Ptr animations);

		/// @brief Sets the minimum time (as sf::Time) between two animation frames.
		/// @param delay Minimum time (as sf::Time) between two animation frames.
		void setAnimationDelay(sf::Time delay);

		/// @brief Returns the current frame of the current animation
		unsigned int getCurrentFrame() const;

		/// @brief Returns the current animation set on this instance.
		///		Returns nullptr if no animation has been set.
		std::size_t getCurrentAnimationId() const;

		/// @brief Returns the ID of the current animation
		/// @return ID of the current animation.
		const Animation* getCurrentAnimation() const;

		/// @brief Returns the minimum time (as sf::Time ) between two animation frames.
		/// @return The minimum time (as sf::Time) between two animation frames.
		sf::Time getAnimationDelay() const;

		/// @brief Returns the number of frames that have been displayed since the current animation has started.
		/// @return The minimum time (as sf::Time) between two animation frames.
		unsigned int getFramesSpentInCurrentAnimation() const;

		/// @brief Determines whether this instance is animating.
		/// @return True if this instance is animating; otherwise, false
		bool isAnimating() const;

		/// @brief Sets the animation that will be displayed by the animated sprite.
		/// @param animationId The index of the animation to begin.
		/// @param endStyle 
		///	@throws std::out_of_range exception if the requested animation is empty.
		void setCurrentAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle);

		/// @brief Sets the animation that will be displayed by the animated sprite. The animation will loop when it ends.
		/// @param animationId The index of the animation to begin.
		/// @param endStyle What happens when the animation reaches the end.
		/// @throws Throws a std::out_of_range exception if the requested animation is empty.
		void setCurrentAnimation(unsigned int animationId);

		/// @brief Begins a new animation from the first frame, allowing the caller to decide what happens when it ends.
		/// @param animationId The index of the animation to begin.
		/// @param endStyle What happens when the animation reaches the end.
		/// @throws a std::out_of_range exception if the requested animation is empty.
		void runAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle);

		/// @brief  Begins a new animation from the first frame
		/// @param animationId The index of the animation to begin.
		/// @throws std::out_of_range exception if the requested animation is empty.
		void runAnimation(unsigned int animationId);

		/// @brief Moves the next frame of the active animation if the sprite is animating
		/// @param elapsedTime The elapsed time.
		void update(sf::Int64 elapsedTime) override;

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