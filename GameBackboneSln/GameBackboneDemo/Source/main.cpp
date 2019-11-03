#include <GameBackboneDemo/DemoCoreEventController.h>


#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

using namespace EXE;

static void draw(sf::RenderWindow& window, sf::RectangleShape& shape) 
{
	window.clear();
	window.draw(shape);
	window.display();

	std::cin.get();
}

int main() {
	// Initialize an instance of DemoCoreEventController
	DemoCoreEventController controller;
	// Start the loop on the DemoCoreEventController to start the Demo
	controller.runLoop();
	return 0;
}