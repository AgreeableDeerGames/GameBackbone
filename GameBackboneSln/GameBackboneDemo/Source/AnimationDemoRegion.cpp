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

    // Create an AnimationSet
    GB::AnimationSet::Ptr animationSet = std::make_shared<GB::AnimationSet>();

    // Add the animation to the AnimationSet
    // The animation is copied into the AnimationSet
    animationSet->addAnimation(simpleAnim);

    // Add another animation to the AnimationSet
    animationSet->addAnimation({
        sf::IntRect(0, 0, frameDimX, frameDimY),                // Top left of the texture
        sf::IntRect(0, 0, spriteSheet.getSize().x, frameDimY),  // Top row of the texture
        sf::IntRect(0, 0, frameDimX, spriteSheet.getSize().y)   // Left column of the texture
    });

    // Create an AnimatedSprite using the sprite sheet and the AnimationSet we constructed above
    GB::AnimatedSprite::Ptr animatedSprite = std::make_shared<GB::AnimatedSprite>(spriteSheet, animationSet);
    // Move the AnimatedSprite
    animatedSprite->move(150, 150);
    // Tell the AnimatedSprite to update every second
    animatedSprite->setAnimationDelay(sf::seconds(1));
    // Tell the AnimatedSprite to begin running its first animation
    // The animation will reverse directions every time it reaches the beginning or end
    animatedSprite->runAnimation(0, GB::ANIMATION_END_TYPE::ANIMATION_REVERSE);
    // Tell the region to draw the AnimatedSprite
    setDrawable(true, animatedSprite.get());
    // Store the animatedSprite in the animatedSprites vector
    animatedSprites.push_back(animatedSprite);

    // Create another animated sprite to display the other animation
    GB::AnimatedSprite::Ptr animatedSprite2 = std::make_shared<GB::AnimatedSprite>(spriteSheet, animationSet);
    // Move the AnimatedSprite
    animatedSprite2->move(300, 300);
    // Tell the AnimatedSprite to update every two seconds
    animatedSprite2->setAnimationDelay(sf::seconds(2));
    // Tell the AnimatedSprite to begin running its second animation
    // The animation will reverse directions every time it reaches the beginning or end
    animatedSprite2->runAnimation(1, GB::ANIMATION_END_TYPE::ANIMATION_LOOP);
    // Tell the region to draw the AnimatedSprite
    setDrawable(true, animatedSprite2.get());
    // Store the animatedSprite in the animatedSprites vector
    animatedSprites.push_back(animatedSprite2);

    // Remove the "Reset" button from Animation Demo, since there is nothing to reset
	// Loop through all tgui Widgets and remove any with the text "Reset"
	const std::vector<tgui::Widget::Ptr>& widgets = regionGUI.getWidgets();
	for (auto& widget : widgets) {
		auto button = std::dynamic_pointer_cast<tgui::Button>(widget);
		if (button != nullptr && button->getText() == "Reset") {
			regionGUI.remove(widget);
		}
	}
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