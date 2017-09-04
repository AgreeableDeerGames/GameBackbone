#pragma once

#include <DemoRegion.h>

#include <sfml/Graphics.hpp>
#include <sfml/Graphics/Sprite.hpp>

namespace EXE {

	class RegionChangeDemoRegion : public DemoRegion {
	public:
		RegionChangeDemoRegion() = delete;
		RegionChangeDemoRegion(sf::RenderWindow& window, sf::Color color);
		~RegionChangeDemoRegion();

		virtual void handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) override;

	private:
		sf::Texture* spriteTexture;
		sf::Sprite sprite;
	};
}

