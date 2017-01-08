#include "AnimatedSprite.h"

//TODO: add animation update rate
//TODO: create animation frame rectangles


//ctr and dtr

///<summary>Default Constructor. Values initialized to 0</summary>
AnimatedSprite::AnimatedSprite() {
	init(0, 0, 0);
}

///<summary>Constructor. Texture set to passed value. Position set to 0.</summary>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture) : sf::Sprite(texture) {
	init(0, 0, 0);
}

/**
<summary>Constructor</summary>
<param name = "texture"> texture representing the animation sheet </param>
<param name = "rows"> the number of rows in the animated sprite animation sheet</param>
<param name = "cols"> the number of columns in the animated sprite animation sheet</param>
<param name = "totalFrames"> the total number of frames in the animated sprite animation sheet</param>*/
AnimatedSprite::AnimatedSprite(const sf::Texture & texture, unsigned int rows, unsigned int cols, unsigned int totalFrames) : sf::Sprite(texture){
	init(rows, cols, totalFrames);
}

/**
<summary>Initializes the row, column and frame count of the animated sprite. Initializes animating property to false Should only be called in constructors.</summary>
<param name = "rows"> the number of rows in the animated sprite animation sheet</param>
<param name = "cols"> the number of columns in the animated sprite animation sheet</param>
<param name = "totalFrames"> the total number of frames in the animated sprite animation sheet</param>*/
void AnimatedSprite::init(unsigned int rows, unsigned int cols, unsigned int totalFrames) {
	this->rows = rows;
	this->cols = cols;
	this->totalFrames = totalFrames;
	this->animating = false;
	this->currentAnimation = nullptr;
	this->currentFrame = 0;
	this->currentAnimationId = 0;
}



AnimatedSprite::~AnimatedSprite() {
}


//getters and setters
	//setters

/**
<summary>sets the number of rows in the animation sheet to a new value</summary>
<param name = "rows">new number of rows in the sprite sheet</param>
*/
void AnimatedSprite::setRows(unsigned int rows) {
	this->rows = rows;
}

/**
<summary>sets the number of columns in the animation sheet to a new value</summary>
<param name = "cols">new number of columns in the sprite sheet</param>
*/
void AnimatedSprite::setCols(unsigned int cols) {
	this->cols = cols;
}

/**
<summary>sets the value for the total animation frame count of the animated sprite</summary>
<param name = "totalFrames">the new total number of animation frames in the sprite sheet</param>
*/
void AnimatedSprite::setTotalFrames(unsigned int totalFrames) {
	this->totalFrames = totalFrames;
}

///<summary> Whether or not the animated sprite is currently playing an animation</summary>
void AnimatedSprite::setAnimating(bool animating) {
	this->animating = animating;
}

///<summary>sets the current frame (within the current animation) of the animated sprite</summary>
void AnimatedSprite::setCurrentFrame(unsigned int frame) {
}

	//getters
///<summary>sets the number of rows in the animation sheet to a new value</summary>
unsigned int AnimatedSprite::getRows() {
	return rows;
}

///<summary>sets the number of columns in the animation sheet to a new value</summary>
unsigned int AnimatedSprite::getCols() {
	return cols;
}

///<summary>sets the value for the total animation frame count of the animated sprite</summary>
unsigned int AnimatedSprite::getTotalFrames() {
	return totalFrames;
}

///<summary>returns the current frame of the current animation</summary>
unsigned int AnimatedSprite::getCurrentFrame() {
	return currentFrame;
}

///<summary>returns the ID of the current animation</summary>
unsigned int AnimatedSprite::getCurrentAnimationId() {
	return currentAnimationId;
}

///<summary>Whether or not the animated sprite is currently playing an animation.</summary>
bool AnimatedSprite::isAnimating() {
	return animating;
}

//operations

/**
<summary>adds an animation (vector of animation frames) to the AnimatedSprite's vector of animations</summary>
<param name = "animation">vector containing the animation frame indexes for the new animation</param>
*/
void AnimatedSprite::addAnimation(std::vector<unsigned int> animation) {
	animations.push_back(animation);
}

///<summary>removes all animations</summary>
void AnimatedSprite::clearAnimations() {
	animations.clear();
}

/**
<summary>replaces the animation at the given index with the passed animation</summary>
<param name = "animationId"> index of the animation to be replaced</param>
<param name "animation"> new animation to place at index</param>
*/
void AnimatedSprite::changeAnimationFrames(unsigned int animationId, std::vector<unsigned int> animation) {
	animations[animationId] = animation;
}

/**
<summary>begins a new animation from the first frame</summary>
<param name = "animationId"> the index of the animation to begin </param>
*/
void AnimatedSprite::runAnimation(unsigned int animationId) {
	this->animating = true;
	this->currentAnimationId = animationId;
	this->currentAnimation = &animations[animationId];
	this->currentFrame = 0;
}


///<summary>Moves the next frame of the active animation</summary>
void AnimatedSprite::update() {
	currentFrame = (currentFrame + 1) % currentAnimation->size();
}