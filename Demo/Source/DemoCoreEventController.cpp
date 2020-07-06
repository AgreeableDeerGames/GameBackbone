#include <GameBackboneDemo/DemoCoreEventController.h>

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

using namespace EXE;

/// <summary>
/// Initializes a new instance of the <see cref="BackboneExeCoreEventController"/> class. Window width, height, and name are default.
/// </summary>
DemoCoreEventController::DemoCoreEventController() : CoreEventController("GameBackbone Demos") {
	// get icon image
	sf::Image icon;
	icon.loadFromFile(R"(Textures/Backbone2_small.png)");

	// Set the icon of the window to the loaded icon
	this->getWindow().setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Initialize the MainMenuDemoRegion
	m_mainMenuDemoRegion = std::make_unique<MainMenuDemoRegion>(getWindow());

	// Register the MainMenuDemoRegion as the active region
	setActiveRegion(m_mainMenuDemoRegion.get());
}

/// <summary>
/// Draws the active game region and then the GUI.
/// </summary>
/// <param name = "event">The event.</param>
void DemoCoreEventController::draw()
{
	CoreEventController::draw();
	postDraw();
}

/// <summary>
/// A helper function performed after draw, which draws the GUI.
/// </summary>
void DemoCoreEventController::postDraw() {
	static_cast<DemoRegion*>(getActiveRegion())->getGUI().draw();
}
