#include "AnimationSet.h"

/// <summary>
/// Initializes a new instance of the <see cref="AnimationSet"/> class.
/// </summary>
/// <param name="rows">The number of rows in the sprite sheet.</param>
/// <param name="cols">The number of columns in the sprite sheet.</param>
AnimationSet::AnimationSet(unsigned int rows, unsigned int cols) {
	this->rows = rows;
	this->cols = cols;
}

/// <summary>
/// Initializes a new instance of the <see cref="AnimationSet"/> class.
/// </summary>
/// <param name="frameAnimations">Arrays of frame numbers for each animation in the set. Each array corresponds to the animation of the same index.</param>
/// <param name="textureWidth">Width of the texture.</param>
/// <param name="textureHeight">Height of the texture.</param>
/// <param name="rows">The number of rows in the sprite sheet.</param>
/// <param name="cols">The number of columns in the sprite sheet.</param>
AnimationSet::AnimationSet(std::vector<std::vector<unsigned int>> frameAnimations, unsigned int textureWidth, unsigned int textureHeight, unsigned int rows, unsigned int cols) {
	this->rows = rows;
	this->cols = cols;
	framesToRects(frameAnimations, textureWidth, textureHeight);
}

AnimationSet::~AnimationSet() {
}

/// <summary>
/// Converts a full set of animations in the frame number format to the textureRect format
/// </summary>
/// <param name="frameAnimations">Animation represented by frame numbers.</param>
/// <param name="textureWidth">Width of the sprite sheet texture.</param>
/// <param name="textureHeight">Height of the sprite sheet texture.</param>
void AnimationSet::framesToRects(std::vector<std::vector<unsigned int>> frameAnimations, unsigned int textureWidth, unsigned int textureHeight) {

	//find the dimensions of the rectangles
	unsigned int rectWidth = textureWidth / cols;
	unsigned int rectHeight = textureHeight / rows;

	//find the rectangle for each frame number in each animation
	for each (std::vector<unsigned int> frameAnimation in frameAnimations) {
		std::vector<sf::IntRect> rectAnimation;
		for each (unsigned int frameNumber in frameAnimation) {
			unsigned int newRectY = (frameNumber / cols) * rectHeight;
			unsigned int newRectX = (frameNumber % cols) * rectWidth;
			sf::IntRect frameRect(newRectX, newRectY, rectWidth, rectHeight);
			rectAnimation.push_back(frameRect);
		}
		animations.push_back(rectAnimation);
	}
}


/// <summary>
/// Clears all animations.
/// </summary>
void AnimationSet::clearAnimations() {
	animations.clear();
}

/// <summary>
/// returns a const pointer to the vector of animations
/// </summary>
/// <returns></returns>
std::vector<std::vector<sf::IntRect>>* AnimationSet::getAnimations() {
	return &animations;
}

