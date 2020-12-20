
#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/UniformAnimationSet.h>

#include <SFML/System/Vector2.hpp>

#include <exception>
#include <vector>

using namespace GB;

UniformAnimationSet::UniformAnimationSet(sf::Vector2i frameSize) : defaultFrameSize(frameSize) {
}

UniformAnimationSet::UniformAnimationSet(sf::Vector2i frameSize, const std::vector<UniformAnimation>& animations)
	: defaultFrameSize(frameSize) {
	for (const UniformAnimation& animation : animations){
		addAnimation(animation);
	}
}

void UniformAnimationSet::addAnimation(const UniformAnimation& animation){
	Animation baseAnimation;
	for (const sf::Vector2i& frameIndex : animation){
		const sf::Vector2i animationPosition(frameIndex.x*defaultFrameSize.x, frameIndex.y*defaultFrameSize.y);
		baseAnimation.emplace_back(sf::IntRect(animationPosition, defaultFrameSize));
	}

	addAnimation(std::move(baseAnimation));
}

sf::Vector2i UniformAnimationSet::getDefaultFrameSize() const {
	return defaultFrameSize;
}