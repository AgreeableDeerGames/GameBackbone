#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <GameBackbone/Core/AnimatedSprite.h>
#include <GameBackbone/Core/AnimationSet.h>
#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <vector>

namespace EXE {
	class AnimationDemoRegion : public DemoRegion {
	public:
		/// <summary>shared_ptr to RegionChangeDemoRegion</summary>
		using Ptr = std::shared_ptr<AnimationDemoRegion>;

		// Constructors
		AnimationDemoRegion(sf::RenderWindow& window);
		virtual ~AnimationDemoRegion() = default;

		AnimationDemoRegion() = delete;
		AnimationDemoRegion(const AnimationDemoRegion& other) = delete;
		AnimationDemoRegion(AnimationDemoRegion&& other) = delete;
		AnimationDemoRegion& operator=(const AnimationDemoRegion& other) = delete;
		AnimationDemoRegion& operator=(AnimationDemoRegion&& other) = delete;

		virtual void update(sf::Int64 elapsedTime) override;
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;


	protected:
		// Storage
		sf::Texture spriteSheet;
		std::vector<GB::AnimatedSprite::Ptr> animatedSprites;
	};
}