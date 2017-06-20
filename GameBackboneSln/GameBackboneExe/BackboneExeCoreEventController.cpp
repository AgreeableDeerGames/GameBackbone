#include "stdafx.h"
#include "BackboneExeCoreEventController.h"
#include "NavigationDemoRegion.h"

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


//events

void BackboneExeCoreEventController::handleEvent(sf::Event & event) {

	//Handle events not handled by the GUI
	switch (event.type) {
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::MouseMoved:
	{
		//pan camera with mouse
		window->setView(camera);
		camera.move((float)(event.mouseMove.x - oldMouseX), (float)(event.mouseMove.y - oldMouseY));
		oldMouseX = event.mouseMove.x;
		oldMouseY = event.mouseMove.y;

		sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f actualPosition = window->mapPixelToCoords(mousePos);
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f actualPosition = window->mapPixelToCoords(mousePos);
		static_cast<NavigationDemoRegion*>(activeRegion)->handleMouseClick(actualPosition, event.mouseButton.button);
		break;
	}
	case sf::Event::Resized:
		camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
		window->setView(camera);
		activeRegion->getGUI()->setView(camera);
		break;
	default:
		break;
	}

}