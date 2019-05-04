#include <GameBackboneDemo/RegionChangeDemoRegion.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="RegionChangeDemoRegion"/> class.
/// </summary>
/// <param name="color">The color of the arrow in this region.</param>
RegionChangeDemoRegion::RegionChangeDemoRegion(sf::RenderWindow& window, sf::Color color, sf::Vector2f position) : DemoRegion(window) {
	// Initialize the arrow texture for the region
	spriteTexture = new sf::Texture();
	spriteTexture->loadFromFile("Textures/SmallArrow.png");

	// Set the texture on the arrow
	sprite.setTexture(*spriteTexture);
	// Set the color and position of the arrow
	sprite.setColor(color);
	sprite.setPosition(position);

	// Set the sprite to be drawn by the GameRegion
	setDrawable(true, &sprite);

	// Remove the "Reset" button from Region Change Demo, since there is nothing to reset
	// Loop through all tgui Widgets and remove any with the text "Reset"
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

/// <summary>
/// Handles the mouse click.
/// Changes regions to the first neighbor region if there is one.
/// </summary>
/// <param name="newPosition">The position that was clicked.</param>
/// <param name="button">The button that was clicked.</param>
void RegionChangeDemoRegion::handleMouseClick(sf::Vector2f newPosition, sf::Mouse::Button button) {
	// Ensure that neighborRegions is not empty
	if (!neighborRegions.empty()) {
		// Ensure that the first neighborRegion is not nullptr
		if (neighborRegions.at(0) != nullptr) {
			// Set this region as the activeRegion on the DemoCoreEventController
			setActiveRegionCB(neighborRegions.at(0));
		}
	}
}
