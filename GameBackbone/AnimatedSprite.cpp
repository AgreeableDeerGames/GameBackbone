#include "AnimatedSprite.h"



//ctr and dtr

///<summary>Default Constructor. Values initialized to 0</summary>
AnimatedSprite::AnimatedSprite() {
	init(0, 0, 0);
}

///<summary>Constructor. Texture set to passed value. Position set to 0.</summary>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture) : sf::Sprite(texture) {
	init(0, 0, 0);
}

///<summary>Constructor</summary>
///<param name = rows> the number of rows in the animated sprite animation sheet</param>
///<param name = cols> the number of columns in the animated sprite animation sheet</param>
///<param name = totalFrames> the total number of frames in the animated sprite animation sheet</param>
AnimatedSprite::AnimatedSprite(const sf::Texture & texture, unsigned int rows, unsigned int cols, unsigned int totalFrames) : sf::Sprite(texture){
	init(rows, cols, totalFrames);
}

///<summary>Initializes the row, column and frame count of the animated sprite. Initializes animating property to false Should only be called in constructors.</summary>
///<param name = rows> the number of rows in the animated sprite animation sheet</param>
///<param name = cols> the number of columns in the animated sprite animation sheet</param>
///<param name = totalFrames> the total number of frames in the animated sprite animation sheet</param>
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


//operations

void AnimatedSprite::update() {

}