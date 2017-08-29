#include <Backbone/AnimatedSprite.h>
#include <Backbone/BackboneBaseExceptions.h>
#include <Util/DebugIncludes.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

using namespace GB;

//ctr and dtr

/// <summary>Default Constructor. All values are initialized to 0 or nullptr.</summary>
AnimatedSprite::AnimatedSprite() {
	AnimatedSpriteInit(nullptr);
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimatedSprite"/> class. Texture set to passed value. Position set to 0.
/// </summary>
/// <param name="texture">The texture.</param>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture) : sf::Sprite(texture) {
	AnimatedSpriteInit(nullptr);
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimatedSprite"/> class. Initializes texture to first frame of first animation.
/// </summary>
/// <param name="texture"> texture representing the animation sheet.</param>
/// <param name="animations">The animations.</param>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture, AnimationSet * animations) : sf::Sprite(texture) {
	AnimatedSpriteInit(animations);
}

/// <summary>
/// Initializes properties to false, 0, or nullptr. Initializes animation set and sets texture to first animation frame if animation set is valid
/// </summary>
/// <param name="animations">animation set for the sprite. If this value is set to a valid animation then the texture of the sprite is set to the first frame of the first animation.</param>
void AnimatedSprite::AnimatedSpriteInit(AnimationSet * animations) {

	setAnimations(animations);
	if (animations) {
		//initialize sprite to first frame of first animation
		setTextureRect(this->animations->at(0).at(0));
	}

	animating = false;
	currentFrame = 0;
	currentAnimationId = 0;
	currentAnimation = nullptr;
	lastUpdate = lastUpdate.Zero;
	animationDelay = 0;
}

AnimatedSprite::~AnimatedSprite() {
}


//getters and setters

	//setters

///<summary> Whether or not the animated sprite is currently playing an animation</summary>
void AnimatedSprite::setAnimating(bool animating) {
	this->animating = animating;
}

/// <summary>
/// sets the current frame (within the current animation) of the animated sprite
/// </summary>
/// <param name="frame">The frame.</param>
void AnimatedSprite::setCurrentFrame(unsigned int frame) {
	currentFrame = frame;
}

/// <summary>
/// sets the animations of the sprite to the passed AnimationSet.
/// </summary>
/// <param name="animationSet">The animation set.</param>
void AnimatedSprite::setAnimations(AnimationSet * animationSet) {
	if (animationSet) {
		animations = animationSet->getAnimations();
	} else {
		animations = nullptr;
	}
}

/// <summary>
///Sets the minimum time (in ms) between two animation frames.
/// </summary>
/// <param name="delay">Minimum time (in ms) between two animation frames.</param>
void AnimatedSprite::setAnimationDelay(unsigned int delay) {
	animationDelay = delay;
}

	//getters

///<summary>returns the current frame of the current animation</summary>
unsigned int AnimatedSprite::getCurrentFrame() {
	return currentFrame;
}

/// <summary>
/// returns the ID of the current animation
/// </summary>
/// <returns>ID of the current animation.</returns>
unsigned int AnimatedSprite::getCurrentAnimationId() {
	return currentAnimationId;
}

/// <summary>
/// returns the minimum time (in ms) between two animation frames.
/// </summary>
/// <returns> The minimum time (in ms) between two animation frames.</returns>
unsigned int AnimatedSprite::getAnimationDelay() {
	return animationDelay;
}

/// <summary>
/// Determines whether this instance is animating.
/// </summary>
/// <returns>
///   <c>true</c> if this instance is animating; otherwise, <c>false</c>.
/// </returns>
bool AnimatedSprite::isAnimating() {
	return animating;
}

//operations

/// <summary>
/// begins a new animation from the first frame
/// </summary>
/// <param name="animationId">the index of the animation to begin.</param>
void AnimatedSprite::runAnimation(unsigned int animationId) {
	runAnimation(animationId, ANIMATION_END_TYPE::ANIMATION_LOOP);
}

/// <summary>
/// Begins a new animation from the first frame, allowing the caller to decide what happens when it ends.
///
/// Throws a AnimatedSprite_EmptyAnimation exception if the requested animation is empty.
/// </summary>
/// <param name="animationId">the index of the animation to begin.</param>
/// <param name="endStyle">What happens when the animation reaches the end.</param>
void AnimatedSprite::runAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle) {

	//Empty animations cannot be ran. What frame would be displayed?
	if (animations->at(animationId).empty()) {
		throw Error::AnimatedSprite_EmptyAnimation();
	}

	this->animating = true;
	this->animationEnd = endStyle;
	this->currentAnimationId = animationId;
	this->currentAnimation = &animations->at(animationId);
	this->currentFrame = 0;
}

/// <summary>
/// Moves the next frame of the active animation if the sprite is animating
/// </summary>
/// <param name="currentTime">The current time.</param>
void AnimatedSprite::update(sf::Time currentTime) {

	if (animating && (currentTime.asMilliseconds() - lastUpdate.asMilliseconds() > (int)animationDelay)) {
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


		setTextureRect(currentAnimation->at(currentFrame));
		lastUpdate = currentTime;
	}
}