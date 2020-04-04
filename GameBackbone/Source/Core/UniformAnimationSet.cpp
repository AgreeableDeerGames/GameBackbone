
#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/UniformAnimationSet.h>

#include <SFML/System/Vector2.hpp>

#include <exception>
#include <vector>

using namespace GB;

/// <summary>
/// Construct a new UniformAnimationSet object.
/// </summary>
/// <param name="frameSize"> The default frame size for an animation. </param>
UniformAnimationSet::UniformAnimationSet(sf::Vector2i frameSize) : defaultFrameSize(frameSize) {
}

/// <summary>
/// Construct a new UniformAnimationSet object.
/// The provided animations will all be added to the animation set.
/// </summary>
/// <param name="frameSize"> The default frame size for an animation. </param>
/// <param name="animations"> 
/// The animations to add. The UniformAnimation is a collection of sf::Vector2i pairs that act as (x, y) coordinates into the texture's frames.
/// </param>
UniformAnimationSet::UniformAnimationSet(sf::Vector2i frameSize, const std::vector<UniformAnimation>& animations)
	: defaultFrameSize(frameSize) {
	for (const UniformAnimation& animation : animations){
		addAnimation(animation);
	}
}

/// <summary>
/// Adds the UniformAnimation to the UniformAnimationSet.
/// The UniformAnimation is a collection of sf::Vector2i pairs that act as (x, y) coordinates into the texture's frames.
/// </summary>
/// <param name="animation"> The animation to add. </param>
void UniformAnimationSet::addAnimation(const UniformAnimation& animation){
	Animation baseAnimation;
	for (const sf::Vector2i& frameIndex : animation){
		const sf::Vector2i animationPosition(frameIndex.x*defaultFrameSize.x, frameIndex.y*defaultFrameSize.y);
		baseAnimation.emplace_back(sf::IntRect(animationPosition, defaultFrameSize));
	}

	addAnimation(std::move(baseAnimation));
}

/// <summary>
/// Returns the default size of UniformAnimation frames
/// </summary>
sf::Vector2i UniformAnimationSet::getDefaultFrameSize() const {
	return defaultFrameSize;
}