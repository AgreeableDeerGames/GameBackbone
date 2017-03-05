#include "stdafx.h"

#include "AnimatedSprite.h"
#include "AnimationSet.h"
#include "GameRegion.h"
#include "Updatable.h"
#include "CompoundSprite.h"
#include "NavigationDemoRegion.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>


int main() {
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 700;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SpriteTests");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//init game update clock
	sf::Clock updateClock;


	//create game regions

	NavigationDemoRegion* demoRegion = new NavigationDemoRegion();


	//view
	sf::View camera(sf::FloatRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(camera);

	//main logic loop
	GameRegion* activeRegion = demoRegion;
	int oldMouseX = WINDOW_WIDTH / 2;
	int oldMouseY = WINDOW_HEIGHT / 2;
	while (window.isOpen()) {
		//close window
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				//pan camera with mouse
				window.setView(camera);
				camera.move(event.mouseMove.x - oldMouseX, event.mouseMove.y - oldMouseY);
				oldMouseX = event.mouseMove.x;
				oldMouseY = event.mouseMove.y;
				break;
			default:
				break;
			}
		}

		activeRegion->behave(updateClock.getElapsedTime());

		//draw loop
		window.clear();

		//draw logic here
		for (sf::Sprite* drawObject : *(activeRegion->getDrawables())) {
			window.draw(*drawObject);
		}

		//update logic here
		for (Updatable* updateObject : *(activeRegion->getUpdatables())) {
			updateObject->update(updateClock.getElapsedTime());
		}

		//end draw logic
		window.display();
	}


	return 0;
}