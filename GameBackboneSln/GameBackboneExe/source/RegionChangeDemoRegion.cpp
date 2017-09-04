#include "../header/RegionChangeDemoRegion.h"

#include <sfml/Graphics.hpp>
#include <sfml/Graphics/Sprite.hpp>

using namespace EXE;

/// <summary>
/// Handles the mouse click.
/// Changes regions to the first neighbor region if there is one.
/// </summary>
/// <param name="newPosition">The new position.</param>
/// <param name="button">The button.</param>
void RegionChangeDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	if (!neighborRegions.empty()) {
		if (neighborRegions[0] != nullptr) {
			setActiveRegionCB(neighborRegions.at(0));
		}
	}
}


/// <summary>
/// Initializes a new instance of the <see cref="RegionChangeDemoRegion"/> class.
/// </summary>
/// <param name="color">The color.</param>
RegionChangeDemoRegion::RegionChangeDemoRegion(sf::RenderWindow& window, sf::Color color) : DemoRegion(window) {
	spriteTexture = new sf::Texture();
	spriteTexture->loadFromFile("..//..//Textures//SmallArrow.png");
	sprite.setTexture(*spriteTexture);
	sprite.setColor(color);
	setDrawable(true, &sprite);
}

RegionChangeDemoRegion::~RegionChangeDemoRegion() {
	delete spriteTexture;
}
