#pragma once

#include <GameBackboneDemo/DemoRegion.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace EXE {

	class RegionChangeDemoRegion : public DemoRegion {
	public:

		// ctr / dtr
		RegionChangeDemoRegion() = delete;
		RegionChangeDemoRegion(const RegionChangeDemoRegion& other) = delete;
		RegionChangeDemoRegion(RegionChangeDemoRegion&& other) = delete;
		RegionChangeDemoRegion& operator=(const RegionChangeDemoRegion& other) = delete;
		RegionChangeDemoRegion& operator=(RegionChangeDemoRegion&& other) = delete;
		RegionChangeDemoRegion(sf::RenderWindow& window, sf::Color color, sf::Vector2f position);
		~RegionChangeDemoRegion();

		// Handle sf::Events
		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;

	private:
		sf::Texture* spriteTexture;
		sf::Sprite sprite;
	};
}

