#include <GameBackbone/Core/AnimationSet.h>

using namespace GB;


/// <summary>
/// Initializes a new instance of the <see cref="AnimationSet"/> class.
/// </summary>
/// <param name="frameIndexAnimations">The consecutive frame indices for each animation.</param>
/// <param name="textureSize">The size of the texture that the animation set will be using.</param>
/// <param name="animationFrameDimensions">The dimensions of the frames (rows, cols) in the sprite sheet.</param>
AnimationSet::AnimationSet(FrameIndexAnimationVectorPtr frameIndexAnimations,
                           sf::Vector2u textureSize,
                           sf::Vector2u animationFrameDimensions) {
    calculateAnimations(std::move(frameIndexAnimations), textureSize, animationFrameDimensions);
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimationSet"/> class.
/// </summary>
/// <param name="frameIndexAnimations">The consecutive frame indices for each animation.</param>
/// <param name="texture">The texture that the animation set will be using.</param>
/// <param name="animationFrameDimensions">The dimensions of the frames (rows, cols) in the sprite sheet.</param>
AnimationSet::AnimationSet(FrameIndexAnimationVectorPtr frameIndexAnimations,
                           const sf::Texture& texture,
                           sf::Vector2u animationFrameDimensions) {
    calculateAnimations(std::move(frameIndexAnimations), texture.getSize(), animationFrameDimensions);
}

/// <summary>
/// Returns all of the animations in this AnimationSet.
/// </summary>
AnimationVectorPtr AnimationSet::getAnimations() const {
    return animations;
}

/// <summary>
/// Clears all animations.
/// </summary>
void AnimationSet::clearAnimations() {
    animations->clear();
}


/// <summary> Determines the rects that represent each frame of animation from
/// the texture and animation dimensions and the indices of the sprite sheet that make up
/// each animation.
/// </summary>
/// <param name="animationFrameIndicies">The consecutive frame indices for each animation.</param>
/// <param name="textureSize"> The pixel size of the sprite sheet.</param>
/// <param name="animationFrameDimensions"> The dimensions of the sprite sheet (in frames) rows X cols</param>
void AnimationSet::calculateAnimations(FrameIndexAnimationVectorPtr animationFrameIndices,
                                       sf::Vector2u textureSize,
                                       sf::Vector2u animationFrameDimensions)  {

    // start fresh
    clearAnimations();

    // cant create animations if no indices are provided
    if (animationFrameIndices == nullptr) {
        return;
    }
    auto [textureWidth, textureHeight] = textureSize;

    //find the dimensions of the rectangles
    auto [animationFrameRows, animationFrameCols] = animationFrameDimensions;

    const unsigned int rectWidth = textureWidth / animationFrameCols;
    const unsigned int rectHeight = textureHeight / animationFrameRows;

    //find the rectangle for each frame number in each animation
    for (const FrameIndexAnimation& frameAnimation : *animationFrameIndices) {
        Animation rectAnimation;
        for (unsigned int frameNumber : frameAnimation) {
            const unsigned int newRectY = (frameNumber / animationFrameCols) * rectHeight;
            const unsigned int newRectX = (frameNumber % animationFrameCols) * rectWidth;
            rectAnimation.emplace_back(sf::IntRect(newRectX, newRectY, rectWidth, rectHeight));
        }
        animations->emplace_back(std::move(rectAnimation));
    }
}
