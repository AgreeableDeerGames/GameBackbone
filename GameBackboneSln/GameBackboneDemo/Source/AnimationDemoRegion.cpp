#include <GameBackboneDemo/AnimationDemoRegion.h>

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/Core/UniformAnimationSet.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>

using namespace EXE;


/// <summary>
/// Construct a new AnimationDemoRegion.
/// </summary>
/// <param name="window">The window to draw to.</param>
AnimationDemoRegion::AnimationDemoRegion(sf::RenderWindow& window) : DemoRegion(window) {
    // Load a texture for the animated sprite
    spriteSheet.loadFromFile(R"(Textures/testSprite.png)");

	// Each frame of the animation will be half the width and height of the texture
	int frameDimX = spriteSheet.getSize().x / 2;
	int frameDimY = spriteSheet.getSize().y / 2;

	// Create an UniformAnimationSet
	// This is an animation where every frame has the same size
	GB::UniformAnimationSet::Ptr uniformAnimationSet = std::make_shared<GB::UniformAnimationSet>(sf::Vector2i(frameDimX, frameDimY));
	// Add an animation to the UniformAnimationSet
	uniformAnimationSet->addAnimation({
		{0, 0},		// Top left of the texture
		{1, 0},		// Top right of the texture
		{0, 1},		// Bottom left of the texture
		{1, 1},		// Bottom right of the texture
		});

	// Create an AnimatedSprite to display the UniformAnimation
	GB::AnimatedSprite::Ptr animatedSprite1 = std::make_shared<GB::AnimatedSprite>(spriteSheet, uniformAnimationSet);
	// Move the AnimatedSprite
	animatedSprite1->move(50, 50);
	// Tell the AnimatedSprite to update every one second
	animatedSprite1->setAnimationDelay(sf::seconds(1));
	// Tell the AnimatedSprite to begin running its second animation
	// The animation will reverse directions every time it reaches the beginning or end
	animatedSprite1->runAnimation(0, GB::ANIMATION_END_TYPE::ANIMATION_REVERSE);
	// Tell the region to draw the AnimatedSprite
	setDrawable(true, animatedSprite1.get());
	// Store the animatedSprite in the animatedSprites vector
	animatedSprites.push_back(animatedSprite1);

	// Create an AnimatedSprite that will only advance frames when the mouse is clicked
	GB::AnimatedSprite::Ptr animatedSprite2 = std::make_shared<GB::AnimatedSprite>(spriteSheet, uniformAnimationSet);
	// Move the AnimatedSprite
	animatedSprite2->move(300, 50);
	// Set the current animation
	animatedSprite2->setCurrentAnimation(0);
	// Tell the region to draw the AnimatedSprite
	setDrawable(true, animatedSprite2.get());
	// Store the animatedSprite in the animatedSprites vector
	animatedSprites.push_back(animatedSprite2);

	// Create an animation.
	// An animation is a series of sf::IntRects. Each IntRect is a frame of the animation.
	// Each IntRect represents the subset of the AnimatedSprite's texture that should be displayed for that frame.
	GB::Animation anim = {
		sf::IntRect(0, 0, frameDimX, frameDimY),									// Top left of the texture
		sf::IntRect(0, frameDimY, spriteSheet.getSize().x, frameDimY),				// Bottom row of the texture
		sf::IntRect(0, 0, frameDimX, spriteSheet.getSize().y),						// Left column of the texture
		sf::IntRect(0, 0, spriteSheet.getSize().x, spriteSheet.getSize().y)			// Entirety of the texture
	};

	// Create an AnimationSet
	GB::AnimationSet::Ptr animationSet = std::make_shared<GB::AnimationSet>();

	// Add the animation to the AnimationSet
	// The animation is copied into the AnimationSet
	animationSet->addAnimation(anim);

	// Create an AnimatedSprite using the sprite sheet and the AnimationSet we constructed above
	GB::AnimatedSprite::Ptr animatedSprite3 = std::make_shared<GB::AnimatedSprite>(spriteSheet, animationSet);
	// Move the AnimatedSprite
	animatedSprite3->move(50, 200);
	// Tell the AnimatedSprite to update every two seconds
	animatedSprite3->setAnimationDelay(sf::seconds(1.5));
	// Tell the AnimatedSprite to begin running its first animation
	// The Animation will loop when it reaches the end
	animatedSprite3->runAnimation(0, GB::ANIMATION_END_TYPE::ANIMATION_LOOP);
	// Tell the region to draw the AnimatedSprite
	setDrawable(true, animatedSprite3.get());
	// Store the animatedSprite in the animatedSprites vector
	animatedSprites.push_back(animatedSprite3);

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

/// <summary>
/// Handles the mouse click.
/// Changes the frame of the 0th animated sprite
/// </summary>
/// <param name="newPosition">The position that was clicked.</param>
/// <param name="button">The button that was clicked.</param>
void AnimationDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	// Get the second animated sprite
	GB::AnimatedSprite::Ptr& targetSprite = animatedSprites[1];
	// Get the size of the current animation so we know when to loop
	auto animationSize = targetSprite->getCurrentAnimation()->size();
	// Advance the animation by one. Start the animation over if its at the end.
	targetSprite->setCurrentFrame((targetSprite->getCurrentFrame() + 1ULL) % animationSize);
}
