#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <GameBackbone/Core/GameRegion.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>

namespace EXE {
	class RegionChangeDemoRegion : public DemoRegion {
	public:
		/// <summary>shared_ptr to RegionChangeDemoRegion</summary>
		using Ptr = std::shared_ptr<RegionChangeDemoRegion>;

		// Constructors
		RegionChangeDemoRegion(sf::RenderWindow& window, sf::Color color, sf::Vector2f position);
		~RegionChangeDemoRegion();

		RegionChangeDemoRegion() = delete;
		RegionChangeDemoRegion(const RegionChangeDemoRegion& other) = delete;
		RegionChangeDemoRegion(RegionChangeDemoRegion&& other) = delete;
		RegionChangeDemoRegion& operator=(const RegionChangeDemoRegion& other) = delete;
		RegionChangeDemoRegion& operator=(RegionChangeDemoRegion&& other) = delete;

		void setNeighbor(std::weak_ptr<GB::GameRegion> neighbor);

		// Handle sf::Events
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;

	protected:
		// Storage
		sf::Texture* spriteTexture;
		sf::Sprite sprite;
		std::weak_ptr<GB::GameRegion> neighbor;
	};
}

