#include <NavigationDemoRegion.h>
#include <BackboneExeCoreEventController.h>

using namespace GB;


// ctr / dtr


/// <summary>
/// Initializes a new instance of the <see cref="BackboneExeCoreEventController"/> class. Window width, height, and name are default.
/// </summary>
BackboneExeCoreEventController::BackboneExeCoreEventController() : CoreEventController() {
	//init region and camera
	activeRegion = new GB::NavigationDemoRegion(*window);
	camera.reset(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));

	//initialize the mouse origin to the center of the window.
	oldMouseX = window->getSize().x / 2;
	oldMouseY = window->getSize().y / 2;
}

/// <summary>
/// Finalizes an instance of the <see cref="BackboneExeCoreEventController"/> class.
/// </summary>
BackboneExeCoreEventController::~BackboneExeCoreEventController() {
	delete activeRegion;
}

//events

/// <summary>
/// Handles non gui user / window events.
/// </summary>
/// <param name="event">The event.</param>
/// <returns></returns>
bool BackboneExeCoreEventController::handleCoreEvent(sf::Event & event) {
	//Handle events not handled by the GUI
	switch (event.type) {
	case sf::Event::Closed:
		window->close();
		return true;
	case sf::Event::MouseMoved:
	{
		//pan camera with mouse
		window->setView(camera);
		camera.move((float)(event.mouseMove.x - oldMouseX), (float)(event.mouseMove.y - oldMouseY));
		oldMouseX = event.mouseMove.x;
		oldMouseY = event.mouseMove.y;

		sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f actualPosition = window->mapPixelToCoords(mousePos);
		static_cast<NavigationDemoRegion*>(activeRegion)->handleMouseDrag(actualPosition);
		return true;
	}
	case sf::Event::MouseButtonPressed:
	{
		sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f actualPosition = window->mapPixelToCoords(mousePos);
		static_cast<NavigationDemoRegion*>(activeRegion)->handleMouseClick(actualPosition, event.mouseButton.button);
		return true;
	}
	case sf::Event::Resized:
		camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
		window->setView(camera);
		activeRegion->getGUI()->setView(camera);
		return true;
	default:
		return false;
	}

}