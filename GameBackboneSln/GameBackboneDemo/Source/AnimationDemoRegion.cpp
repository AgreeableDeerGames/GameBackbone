#include <GameBackboneDemo/AnimationDemoRegion.h>

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/Core/UniformAnimationSet.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>

using namespace EXE;


/// <summary>Construct a new AnimationDemoRegion.</summary>
/// <param name="window">The window to draw to.</param>
AnimationDemoRegion::AnimationDemoRegion(sf::RenderWindow& window) : DemoRegion(window) {
    // Load a texture for the animated sprite
    spriteSheet.loadFromFile(R"(Textures/testSprite.png)");

    // Each frame of the animation will be half the width and height of the texture
    int frameDimX = spriteSheet.getSize().x / 2;
    int frameDimY = spriteSheet.getSize().y / 2;

    /* Create an animation.
     * An animation is a series of SF::IntRects. Each IntRect is a frame of the animation.
     * Each IntRect represents the subset of the AnimatedSprite's texture that should be
     * displayed for that frame.
     */
    GB::Animation simpleAnim = {
        sf::IntRect(0, 0, frameDimX, frameDimY),                // Top left of the texture
        sf::IntRect(frameDimX, 0, frameDimX, frameDimY),        // Top right of the texture
        sf::IntRect(0, frameDimY, frameDimX, frameDimY),        // Bottom left of the texture
        sf::IntRect(frameDimX, frameDimY, frameDimX, frameDimY) // Bottom right of the texture
    };

    // create an AnimationSet
    GB::AnimationSet::Ptr animationSet = std::make_shared<GB::AnimationSet>();

    // Add the animation to the AnimationSet
    // The animation is coppied into the AnimationSet
    animationSet->addAnimation(simpleAnim);

    // Create an AnimatedSprite using the sprite sheet and the AnimationSet we constructed above
    GB::AnimatedSprite::Ptr animatedSprite = std::make_shared<GB::AnimatedSprite>(spriteSheet, animationSet);

    // Move the AnimatedSprite
    animatedSprite->move(400, 400);

    // Tell the AnimatedSprite to update every second
    animatedSprite->setAnimationDelay(sf::seconds(1));

    // Tell the AnimatedSprite to begin running its first animation
    // The animation will reverse directions every time it reaches the beginning or end
    animatedSprite->runAnimation(0, GB::ANIMATION_END_TYPE::ANIMATION_REVERSE);

    // Tell the region to draw the AnimatedSprite
    setDrawable(true, animatedSprite.get());

    // Store the animatedSprite in the animatedSprites vector
    animatedSprites.push_back(animatedSprite);
}

/// <summary>
/// Update the AnimationDemoRegion
/// Update all the AnimatedSprites owned by the AnimationDemoRegion
/// </summary>
/// <param name="elapsedTime"> </param>
void AnimationDemoRegion::update(sf::Int64 elapsedTime) {
    // Update all the AnimatedSprites
    for (auto& animatedSprite : animatedSprites) {
        animatedSprite->update(elapsedTime);
    }
}
