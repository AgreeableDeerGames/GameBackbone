#include <Backbone/AnimationSet.h>

using namespace GB;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~AnimationSet~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AnimationSet::AnimationSet(AnimationFrameIndexVectorPtr animationFrames,
                           sf::Vector2u textureSize,
                           sf::Vector2u animationFrameDimensions) {
    calculateAnimations(std::move(animationFrames), textureSize, animationFrameDimensions);
}

AnimationSet::AnimationSet(AnimationFrameIndexVectorPtr animationFrames, sf::Texture texture,
                           sf::Vector2u animationFrameDimensions) {
    calculateAnimations(std::move(animationFrames), texture.getSize(), animationFrameDimensions);
}

AnimationVectorPtr AnimationSet::getAnimations() {
    return AnimationVectorPtr();
}


void AnimationSet::clearAnimations() {
    animations->clear();
}

void AnimationSet::calculateAnimations(AnimationFrameIndexVectorPtr animationFrameIndices,
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
    unsigned int rectWidth = textureWidth / animationFrameCols;
    unsigned int rectHeight = textureHeight / animationFrameRows;

    //find the rectangle for each frame number in each animation
    for (const AnimationFrameIndex& frameAnimation : *animationFrameIndices) {
        Animation rectAnimation;
        for (unsigned int frameNumber : frameAnimation) {
            const unsigned int newRectY = (frameNumber / animationFrameCols) * rectHeight;
            const unsigned int newRectX = (frameNumber % animationFrameRows) * rectWidth;
            rectAnimation.emplace_back(sf::IntRect(newRectX, newRectY, rectWidth, rectHeight));
        }
        animations->emplace_back(std::move(rectAnimation));
    }
}



//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~AnimationSet End~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DynamicAnimationSet~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

DynamicAnimationSet::DynamicAnimationSet() : AnimationSet(nullptr, {0,0}, {0,0}) {}

DynamicAnimationSet::DynamicAnimationSet(sf::Vector2u animationFrameDimensions)
    : AnimationSet(nullptr, {0, 0}, animationFrameDimensions){}

DynamicAnimationSet::DynamicAnimationSet(GB::AnimationFrameIndexVectorPtr animationFrameIndices,
                                         sf::Vector2u textureSize,
                                         sf::Vector2u animationFrameDimensions)

                                         : AnimationSet(std::move(animationFrameIndices),
                                                        textureSize,
                                                        animationFrameDimensions) {}

DynamicAnimationSet::DynamicAnimationSet(GB::AnimationFrameIndexVectorPtr animationFrameIndices,
                                         const sf::Texture &texture,
                                         sf::Vector2u animationFrameDimensions)

                                         : DynamicAnimationSet(std::move(animationFrameIndices),
                                                               texture.getSize(),
                                                               animationFrameDimensions) {}

// Getters and setters


    // setters
void DynamicAnimationSet::setAnimationFrameDimensions(sf::Vector2u dimensions) {
    this->animationFrameDimensions = dimensions;
    calculateAnimations(animationFrameIndices, textureSize, animationFrameDimensions);
}

void DynamicAnimationSet::setTextureSize(sf::Vector2u size) {
    this->textureSize = size;
    calculateAnimations(animationFrameIndices, textureSize, animationFrameDimensions);
}

void DynamicAnimationSet::setAnimationFrameIndices(AnimationFrameIndexVectorPtr animationFrames) {
    this->animationFrameIndices = std::move(animationFrames);
    calculateAnimations(animationFrameIndices, textureSize, animationFrameDimensions);
}

AnimationVectorPtr DynamicAnimationSet::getAnimations() {
    return animations;
}


    // getters
sf::Vector2u DynamicAnimationSet::getTextureSize() {
    return this->textureSize;
}

sf::Vector2u DynamicAnimationSet::getAnimationFrameDimensions() {
    return this->animationFrameDimensions;
}

AnimationFrameIndexVectorPtr DynamicAnimationSet::getAnimationFrameIndices() {
    return this->animationFrameIndices;
}

// internal operations


//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DynamicAnimationSet End~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
