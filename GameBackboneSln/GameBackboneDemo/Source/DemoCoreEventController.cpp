#include <GameBackboneDemo/DemoCoreEventController.h>
#include <GameBackboneDemo/NavigationDemoRegion.h>

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

	// Set set the icon of the window to the loaded icon
	this->m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Initialize the MainMenuDemoRegion
	m_mainMenuDemoRegion = std::make_unique<MainMenuDemoRegion>(*m_window);
	// Register setActiveRegion with m_mainMenuDemoRegion so that it can swap regions when needed
	// Pass a lambda 
	m_mainMenuDemoRegion->registerSetActiveRegionCB([this](GB::GameRegion* activeRegion){
		setActiveRegion(activeRegion);
	});
	// Set m_mainMenuDemoRegion as the activeRegion on DemoCoreEventController
	m_activeRegion = m_mainMenuDemoRegion.get();

	// Set the camera to the same as the window
	m_camera.reset(sf::FloatRect(0, 0, (float)m_window->getSize().x, (float)m_window->getSize().y));
}

//events

/// <summary>
/// Handles non gui user/window events.
/// </summary>
/// <param name="event">The event.</param>
/// <returns></returns>
bool DemoCoreEventController::handleCoreEvent(sf::Event & event) {

	// Handle events not handled by the GUI
	switch (event.type) {
		case sf::Event::Closed:
		{
			// Close the window, thus closing the game.
			m_window->close();
			return true;
		}
		case sf::Event::MouseMoved:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
			sf::Vector2f actualPosition = m_window->mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(m_activeRegion)->handleMouseMove(actualPosition);
			return true;
		}
		case sf::Event::MouseButtonPressed:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2f actualPosition = m_window->mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(m_activeRegion)->handleMouseClick(actualPosition, event.mouseButton.button);
			return true;
		}
		case sf::Event::MouseWheelScrolled:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(m_activeRegion)->handleWheelScroll(event.mouseWheelScroll.delta);
			return true;
		}
		case sf::Event::KeyPressed:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(m_activeRegion)->handleKeyPress(event.key);
			return true;
		}
		case sf::Event::KeyReleased:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(m_activeRegion)->handleKeyRelease(event.key);
			return true;
		}
		case sf::Event::Resized:
		{
			// Reset the camera to the same as the window
			m_camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
			// Set the view on the window to be the reset camera
			m_window->setView(m_camera);
			// Set the view on the GUI to be the reset camera
			static_cast<DemoRegion*>(m_activeRegion)->getGUI().setView(m_camera);
			return true;
		}
		default:
		{
			return false;
		}
	}
}

void DemoCoreEventController::postHandleEvent(sf::Event& /*event*/) {
	static_cast<DemoRegion*>(m_activeRegion)->getGUI().unfocusAllWidgets();
}

void DemoCoreEventController::postDraw() {
	static_cast<DemoRegion*>(m_activeRegion)->getGUI().draw();
}

/// <summary>
/// Handles the GUI event.
/// </summary>
/// <param name="event">The event.</param>
/// <returns>Returns true if the event was consumed by the GUI. Returns false otherwise.</returns>
bool DemoCoreEventController::handleGuiEvent(sf::Event& event) {
	if (!static_cast<DemoRegion*>(m_activeRegion)->getGUI().handleEvent(event)) {
		return false;
	}
	return true;
}

// <summary>
// Handles all events
// </summary>
// <param name = "event">The event.< / param>
// 'handleGuiEvent' function is a function of TGUI.
// It can be replaced if you want to use a different GUI handler.
void DemoCoreEventController::handleEvent(sf::Event & event)
{
	if (!handleGuiEvent(event)) {
		handleCoreEvent(event);
	}
}