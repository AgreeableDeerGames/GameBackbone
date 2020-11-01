#include <GameBackbone/Core/AnimatedSprite.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <stdexcept>

using namespace GB;

//ctr and dtr

AnimatedSprite::AnimatedSprite() : AnimatedSprite(sf::Texture{}) {
}

AnimatedSprite::AnimatedSprite(const sf::Texture & texture) : 
	AnimatedSprite(texture, nullptr) {
}

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

void AnimatedSprite::setAnimating(bool animating) {
	this->animating = animating;
}

void AnimatedSprite::setCurrentFrame(unsigned int frame) {
	if (!currentAnimation) {
		throw std::runtime_error("Cannot set the frame of an animation without an active animation (calling runAnimation).");
	}
	currentFrame = frame;
	setTextureRect(currentAnimation->at(currentFrame));
}

void AnimatedSprite::setAnimations(AnimationSet::Ptr animations) {
	if (animations) {
		this->animations = std::move(animations);
		// Initialize sprite to first frame of first animation
		setTextureRect(this->animations->at(0).at(0));
	}
}

void AnimatedSprite::setAnimationDelay(sf::Time delay) {
	animationDelay = delay;
}

unsigned int AnimatedSprite::getCurrentFrame() const {
	return currentFrame;
}

const Animation* AnimatedSprite::getCurrentAnimation() const {
	return currentAnimation;
}

std::size_t AnimatedSprite::getCurrentAnimationId() const {
	return currentAnimationId;
}

sf::Time AnimatedSprite::getAnimationDelay() const {
	return animationDelay;
}

unsigned int AnimatedSprite::getFramesSpentInCurrentAnimation() const {
	return framesSpentInCurrentAnimation;
}

bool AnimatedSprite::isAnimating() const {
	return animating;
}

void AnimatedSprite::runAnimation(unsigned int animationId) {
	runAnimation(animationId, ANIMATION_END_TYPE::ANIMATION_LOOP);
}

void AnimatedSprite::runAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle) {
	setCurrentAnimation(animationId, endStyle);
	setAnimating(true);
}

void AnimatedSprite::setCurrentAnimation(unsigned int animationId) {
	setCurrentAnimation(animationId, ANIMATION_END_TYPE::ANIMATION_LOOP);
}

void AnimatedSprite::setCurrentAnimation(unsigned int animationId, ANIMATION_END_TYPE endStyle) {
	// Empty animations cannot be run. What frame would be displayed?
	if (animations->at(animationId).empty()) {
		throw std::out_of_range("The requested Animation does not exist.");
	}
	this->animationEnd = endStyle;
	this->currentAnimationId = animationId;
	this->currentAnimation = &animations->at(animationId);
	this->currentFrame = 0;
	this->framesSpentInCurrentAnimation = 0;
}

void AnimatedSprite::update(sf::Int64 elapsedTime) {
	timeSinceLastUpdate = timeSinceLastUpdate + sf::microseconds(elapsedTime);
	if (animating && (timeSinceLastUpdate.asMicroseconds() > animationDelay.asMicroseconds())) {
		timeSinceLastUpdate = sf::Time::Zero;
		switch (animationEnd) {
		case ANIMATION_END_TYPE::ANIMATION_LOOP:
			setCurrentFrame((currentFrame + 1ULL) % currentAnimation->size());
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
	}
}