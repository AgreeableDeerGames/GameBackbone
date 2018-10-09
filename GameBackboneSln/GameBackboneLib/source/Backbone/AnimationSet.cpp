#include <Backbone/AnimationSet.h>

using namespace GB;

AnimationSet::AnimationSet(sf::Vector2u animationFrameDimensions)
    : animationFrameDimensions(animationFrameDimensions) {}

AnimationSet::AnimationSet(GB::AnimationFrameIndexVectorPtr animationFrameIndices,
                           sf::Vector2u textureSize,
                           sf::Vector2u animationFrameDimensions)
                           : animationFrameIndices(std::move(animationFrameIndices)),
                           textureSize(textureSize),
                           animationFrameDimensions(animationFrameDimensions) {}

AnimationSet::AnimationSet(GB::AnimationFrameIndexVectorPtr animationFrameIndices,
                           const sf::Texture &texture,
                           sf::Vector2u animationFrameDimensions)

                           : AnimationSet(std::move(animationFrameIndices),
                                   texture.getSize(),
                                   animationFrameDimensions) {}

// Getters and setters



void AnimationSet::setAnimationFrameDimensions(sf::Vector2u dimensions) {
    this->animationFrameDimensions = dimensions;
}

void AnimationSet::setTextureSize(sf::Vector2u size) {
    this->textureSize = size;
}

void AnimationSet::setAnimationFrameIndices(AnimationFrameIndexVectorPtr animationFrames) {
    this->animationFrameIndices = animationFrames;
}

AnimationVectorPtr AnimationSet::getAnimations() {
    return animations;
}

sf::Vector2u AnimationSet::getTextureSize() {
    return this->textureSize;
}

sf::Vector2u AnimationSet::getAnimationFrameDimensions() {
    return this->animationFrameDimensions;
}

AnimationFrameIndexVectorPtr AnimationSet::getAnimationFrameIndices() {
    return this->animationFrameIndices;
}


// internal operations







/*

/// <summary>
/// Initializes a new instance of the <see cref="AnimationSet"/> class.
/// </summary>
/// <param name="rows">The number of rows in the sprite sheet.</param>
/// <param name="cols">The number of columns in the sprite sheet.</param>
AnimationSet::AnimationSet(unsigned int rows, unsigned int cols) {
	this->rows = rows;
	this->cols = cols;
	this->animations = new std::vector<std::vector<sf::IntRect>>;
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimationSet"/> class.
/// </summary>
/// <param name="frameAnimations">Arrays of frame numbers for each animation in the set. Each array corresponds to the animation of the same index.</param>
/// <param name="textureWidth">Width of the texture.</param>
/// <param name="textureHeight">Height of the texture.</param>
/// <param name="rows">The number of rows in the sprite sheet.</param>
/// <param name="cols">The number of columns in the sprite sheet.</param>
AnimationSet::AnimationSet(const std::vector<std::vector<unsigned int>>& frameAnimations, unsigned int textureWidth, unsigned int textureHeight, unsigned int rows, unsigned int cols) {
	this->rows = rows;
	this->cols = cols;
	this->animations = new std::vector<std::vector<sf::IntRect>>;
	framesToRects(frameAnimations, textureWidth, textureHeight);
}

AnimationSet::~AnimationSet() {
	delete this->animations;
	this->animations = nullptr;
}

/// <summary>
/// Converts a full set of animations in the frame number format to the textureRect format
/// </summary>
/// <param name="frameAnimations">Animation represented by frame numbers.</param>
/// <param name="textureWidth">Width of the sprite sheet texture.</param>
/// <param name="textureHeight">Height of the sprite sheet texture.</param>
void AnimationSet::framesToRects(const std::vector<std::vector<unsigned int>>& frameAnimations, unsigned int textureWidth, unsigned int textureHeight) {

	//find the dimensions of the rectangles
	unsigned int rectWidth = textureWidth / cols;
	unsigned int rectHeight = textureHeight / rows;

	//find the rectangle for each frame number in each animation
	for (std::vector<unsigned int> frameAnimation : frameAnimations) {
		std::vector<sf::IntRect> rectAnimation;
		for (unsigned int frameNumber : frameAnimation) {
			unsigned int newRectY = (frameNumber / cols) * rectHeight;
			unsigned int newRectX = (frameNumber % cols) * rectWidth;
			sf::IntRect frameRect(newRectX, newRectY, rectWidth, rectHeight);
			rectAnimation.push_back(frameRect);
		}
		animations->push_back(rectAnimation);
	}
}


/// <summary>
/// Clears all animations.
/// </summary>
void AnimationSet::clearAnimations() {
	animations->clear();
}

/// <summary>
/// returns a pointer to the vector of animations
/// </summary>
/// <returns></returns>
std::shared_ptr<std::vector<std::vector<sf::IntRect>>> AnimationSet::getAnimations() {
	// return animations;
}

*/