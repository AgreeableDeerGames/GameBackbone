#include "../header/RegionChangeDemoRegion.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>

using namespace EXE;


// ctr / dtr

/// <summary>
/// Initializes a new instance of the <see cref="RegionChangeDemoRegion"/> class.
/// </summary>
/// <param name="color">The color.</param>
RegionChangeDemoRegion::RegionChangeDemoRegion(sf::RenderWindow& window, sf::Color color) : DemoRegion(window) {
	spriteTexture = new sf::Texture();
	spriteTexture->loadFromFile("Textures/SmallArrow.png");
	sprite.setTexture(*spriteTexture);
	sprite.setColor(color);
	sprite.setPosition(300, 300);
	setDrawable(true, &sprite);

	std::vector<std::shared_ptr<tgui::Widget>> widgets = regionGUI->getWidgets();
	for (auto& widget : widgets) {
		auto button = std::dynamic_pointer_cast<tgui::Button>(widget);
		if (button != nullptr && button->getText() == "Reset") {
			regionGUI->remove(widget);
		}
	}
}



/// <summary>
/// Finalizes an instance of the <see cref="RegionChangeDemoRegion"/> class.
/// </summary>
RegionChangeDemoRegion::~RegionChangeDemoRegion() {
	delete spriteTexture;
}

// handles and callbacks

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
