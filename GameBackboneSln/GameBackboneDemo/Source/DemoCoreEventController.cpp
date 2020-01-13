#include <GameBackboneDemo/DemoCoreEventController.h>
#include <GameBackboneDemo/NavigationDemoRegion.h>

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

	// Register the MainMenuDemoRegion as the active region
	registerActiveRegion(*m_mainMenuDemoRegion.get());

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
			static_cast<DemoRegion*>(getActiveRegion())->handleMouseMove(actualPosition);
			return true;
		}
		case sf::Event::MouseButtonPressed:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2f actualPosition = m_window->mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleMouseClick(actualPosition, event.mouseButton.button);
			return true;
		}
		case sf::Event::MouseWheelScrolled:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleWheelScroll(event.mouseWheelScroll.delta);
			return true;
		}
		case sf::Event::KeyPressed:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleKeyPress(event.key);
			return true;
		}
		case sf::Event::KeyReleased:
		{
			// Pass the event to the active region to handle
			static_cast<DemoRegion*>(getActiveRegion())->handleKeyRelease(event.key);
			return true;
		}
		case sf::Event::Resized:
		{
			// Reset the camera to the same as the window
			m_camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
			// Set the view on the window to be the reset camera
			m_window->setView(m_camera);
			// Set the view on the GUI to be the reset camera
			getActiveRegion()->getGUI().setView(m_camera);
			return true;
		}
		default:
		{
			return false;
		}
	}
}

void DemoCoreEventController::postHandleEvent(sf::Event& /*event*/) {
	getActiveRegion()->getGUI().unfocusAllWidgets();
}