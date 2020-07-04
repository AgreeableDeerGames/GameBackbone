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

	// Set the camera to the same as the window
	m_camera.reset(sf::FloatRect(0, 0, (float)getWindow().getSize().x, (float)getWindow().getSize().y));
}

/// <summary>
/// Handles all events
/// </summary>
/// <param name = "event">The event.</param>
void DemoCoreEventController::handleEvent(sf::Event& event)
{
	if (!handleGUIEvent(event)) {
		handleCoreEvent(event);
	}
	postHandleEvent();
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
/// Handles non GUI user/window events.
/// </summary>
/// <param name="event">The event.</param>
/// <returns></returns>
void DemoCoreEventController::handleCoreEvent(sf::Event& event) {

	// Handle events not handled by the GUI
	switch (event.type) {
		case sf::Event::Closed:
		{
			// Close the window, thus closing the game.
			getWindow().close();
			return;
		}
		case sf::Event::MouseMoved:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
			sf::Vector2f actualPosition = getWindow().mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleMouseMove(actualPosition);
			return;
		}
		case sf::Event::MouseButtonPressed:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2f actualPosition = getWindow().mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleMouseClick(actualPosition, event.mouseButton.button);
			return;
		}
		case sf::Event::MouseWheelScrolled:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleWheelScroll(event.mouseWheelScroll.delta);
			return;
		}
		case sf::Event::KeyPressed:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleKeyPress(event.key);
			return;
		}
		case sf::Event::KeyReleased:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleKeyRelease(event.key);
			return;
		}
		case sf::Event::Resized:
		{
			// Reset the camera to the same as the window
			m_camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
			// Set the view on the window to be the reset camera
			getWindow().setView(m_camera);
			// Set the view on the GUI to be the reset camera
			static_cast<DemoRegion*>(getActiveRegion())->getGUI().setView(m_camera);
			return;
		}
	}
}

/// <summary>
/// Handles the GUI event.
/// </summary>
/// <param name="event">The event.</param>
/// <returns>Returns true if the event was consumed by the GUI. Returns false otherwise.</returns>
bool DemoCoreEventController::handleGUIEvent(sf::Event& event) {
	if (!static_cast<DemoRegion*>(getActiveRegion())->getGUI().handleEvent(event)) {
		return false;
	}
	return true;
}

/// <summary>
/// A helper function performed after handleEvent that unfocuses all widgets. 
/// This frees keyboard focus to be used for control of the game.
/// </summary>
void DemoCoreEventController::postHandleEvent() {
	static_cast<DemoRegion*>(getActiveRegion())->getGUI().unfocusAllWidgets();
}

/// <summary>
/// A helper function performed after draw, which draws the GUI.
/// </summary>
void DemoCoreEventController::postDraw() {
	static_cast<DemoRegion*>(getActiveRegion())->getGUI().draw();
}
