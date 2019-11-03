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
	

	// Create the main window
	/*sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");


	sf::RectangleShape shape({ 50, 50 });
	shape.setPosition({ 50, 50 });
	shape.setFillColor(sf::Color::Red);
	draw(window, shape);

	shape.setOrigin(50, 0);
	draw(window, shape);

	shape.setPosition(50, 0);
	draw(window, shape);*/

	return 0;
}