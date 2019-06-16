#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Util/DebugIncludes.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace GB;

//ctr and dtr

/// <summary>
/// Create a new AnimatedSprite with an empty texture. All values are initialized to 0, nullptr, or false.
/// </summary>
AnimatedSprite::AnimatedSprite() : AnimatedSprite(sf::Texture{}) {
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimatedSprite"/> class. Texture set to passed value. Position set to 0.
/// </summary>
/// <param name="texture">The texture.</param>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture) : 
	AnimatedSprite(texture, nullptr) {
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimatedSprite"/> class. Initializes texture to first frame of first animation.
/// </summary>
/// <param name="texture"> texture representing the animation sheet.</param>
/// <param name="animations">The animations.</param>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture, AnimationSet::Ptr animations) : 
	sf::Sprite(texture),
	animating(false),
	isReverse(false),
	animationEnd(ANIMATION_END_TYPE::ANIMATION_LOOP),
	animationDelay(sf::Time::Zero),
	timeSinceLastUpdate(sf::Time::Zero),
	currentFrame(0),
	framesSpentInCurrentAnimation(0),
	currentAnimationId(0),
	currentAnimation(nullptr),
	animations(nullptr)
{
	setAnimations(std::move(animations));
}

//getters and setters

	//setters

///<summary> 
/// Whether or not the AnimatedSprite is currently playing an animation
/// </summary>
void AnimatedSprite::setAnimating(bool animating) {
	this->animating = animating;
}

/// <summary>
/// Sets the current frame (within the current animation) of the AnimatedSprite
/// </summary>
/// <param name="frame">The frame.</param>
void AnimatedSprite::setCurrentFrame(unsigned int frame) {
	currentFrame = frame;
}

/// <summary>
/// Updates the sprite to use the provided AnimationSet.
/// The current frame of the sprite is set to the first frame of the AnimationSet's first Animation
/// If the provided AnimationSet is empty an out_of_bounds exception is thrown.
/// </summary>
/// <param name="animations">The new AnimationSet to use.</param>
void AnimatedSprite::setAnimations(AnimationSet::Ptr animations) {
	if (animations) {
		this->animations = std::move(animations);
		// Initialize sprite to first frame of first animation
		setTextureRect(this->animations->at(0).at(0));
	}
}

/// <summary>
/// Sets the minimum time (as sf::Time) between two animation frames.
/// </summary>
/// <param name="delay">Minimum time (as sf::Time) between two animation frames.</param>
void AnimatedSprite::setAnimationDelay(sf::Time delay) {
	animationDelay = delay;
}

	//getters

///<summary>
/// Returns the current frame of the current animation
/// </summary>
unsigned int AnimatedSprite::getCurrentFrame() const {
	return currentFrame;
}

/// <summary>
/// Returns the ID of the current animation
/// </summary>
/// <returns>ID of the current animation.</returns>
unsigned int AnimatedSprite::getCurrentAnimationId() const {
	return currentAnimationId;
}

/// <summary>
/// Returns the minimum time (as sf::Time ) between two animation frames.
/// </summary>
/// <returns> The minimum time (as sf::Time) between two animation frames.</returns>
sf::Time AnimatedSprite::getAnimationDelay() const {
	return animationDelay;
}

/// <summary>
/// Returns the number of frames that have been displayed since the current animation has started.
/// </summary>
/// <returns> The minimum time (as sf::Time) between two animation frames.</returns>
unsigned int AnimatedSprite::getFramesSpentInCurrentAnimation() const {
	return framesSpentInCurrentAnimation;
}

/// <summary>
/// Determines whether this instance is animating.
/// </summary>
/// <returns>
///   <c>true</c> if this instance is animating; otherwise, <c>false</c>.
/// </returns>
bool AnimatedSprite::isAnimating() const {
	return animating;
}

//operations

/// <summary>
/// Begins a new animation from the first frame
/// </summary>
/// <param name="animationId">the index of the animation to begin.</param>
void AnimatedSprite::runAnimation(unsigned int animationId) {
	runAnimation(animationId, ANIMATION_END_TYPE::ANIMATION_LOOP);
}

/// <summary>
/// Begins a new animation from the first frame, allowing the caller to decide what happens when it ends.
/// Throws a std::out_of_range exception if the requested animation is empty.
/// </summary>
/// <param name="animationId">the index of the animation to begin.</param>
/// <param name="endStyle">What happens when the animation reaches the end.</param>
void AnimatedSprite::runAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle) {

	// Empty animations cannot be run. What frame would be displayed?
	if (animations->at(animationId).empty()) {
		throw std::out_of_range("AnimatedSprite cannot run an empty animation.");
	}

	this->animating = true;
	this->animationEnd = endStyle;
	this->currentAnimationId = animationId;
	this->currentAnimation = &animations->at(animationId);
	this->currentFrame = 0;
	this->framesSpentInCurrentAnimation = 0;
}

/// <summary>
/// Moves the next frame of the active animation if the sprite is animating
/// </summary>
/// <param name="elapsedTime">The elapsed time.</param>
void AnimatedSprite::update(sf::Int64 elapsedTime) {
	timeSinceLastUpdate = timeSinceLastUpdate + sf::microseconds(elapsedTime);
	if (animating && (timeSinceLastUpdate.asMicroseconds() > animationDelay.asMicroseconds())) {
		timeSinceLastUpdate = sf::Time::Zero;
		switch (animationEnd) {
		case ANIMATION_END_TYPE::ANIMATION_LOOP:
			setCurrentFrame((currentFrame + 1) % currentAnimation->size());
			break;
		case ANIMATION_END_TYPE::ANIMATION_REVERSE:
			// Only change the frame if the animation has more than one frame
			if (currentAnimation->size() > 1) {
				if (currentFrame >= currentAnimation->size() - 1 || (currentFrame == 0 && isReverse)) {
					isReverse = !isReverse;
				}

				if (!isReverse) {
					setCurrentFrame(currentFrame + 1);
				}
				else {
					setCurrentFrame(currentFrame - 1);
				}
			}
			break;
		case ANIMATION_END_TYPE::ANIMATION_STOP:
			if (currentFrame < currentAnimation->size() - 1) {
				setCurrentFrame(currentFrame + 1);
			}
			break;
		}

		framesSpentInCurrentAnimation++;

		// Update the displayed frame
		setTextureRect(currentAnimation->at(currentFrame));
	}
}