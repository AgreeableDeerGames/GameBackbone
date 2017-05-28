#include "stdafx.h"

#include "AnimatedSprite.h"
#include "AnimationSet.h"
#include "GameRegion.h"
#include "Updatable.h"
#include "CompoundSprite.h"
#include "NavigationDemoRegion.h"
#include "SampleGuiInterface.h"

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

using namespace GB;

int main() {
	//Init Window
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 700;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SpriteTests");
	try
	{
		//init GUI
		auto theme = tgui::Theme::create("TGUI_Widgets/Black.txt");
		tgui::Gui* gui = new tgui::Gui(window);

		//get window width and height
		auto windowWidth = tgui::bindWidth(*gui);
		auto windowHeight = tgui::bindHeight(*gui);

		tgui::EditBox::Ptr editBoxSearch = theme->load("EditBox");
		editBoxSearch->setSize(windowWidth * 2 / 3.0f, windowHeight / 10.0f);
		editBoxSearch->setDefaultText("test text");
		editBoxSearch->setPosition(0, windowHeight);
		gui->add(editBoxSearch);

	}
	catch (const tgui::Exception e)
	{
		std::cout << e.what() << std::endl;
	}

	sf::CircleShape shape(10.0f);
	shape.setFillColor(sf::Color::Green);

	//init game update clock
	sf::Clock updateClock;


	//create game regions

	NavigationDemoRegion* demoRegion = new NavigationDemoRegion();


	//view
	sf::View camera(sf::FloatRect(0,0,(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	window.setView(camera);

	//main logic loop
	NavigationDemoRegion* activeRegion = demoRegion;
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
			{
				//pan camera with mouse
				window.setView(camera);
				camera.move((float)(event.mouseMove.x - oldMouseX), (float)(event.mouseMove.y - oldMouseY));
				oldMouseX = event.mouseMove.x;
				oldMouseY = event.mouseMove.y;

				sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
				sf::Vector2f actualPosition = window.mapPixelToCoords(mousePos);
				shape.setPosition(actualPosition);
				break;
			}
			case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f actualPosition = window.mapPixelToCoords(mousePos);
                activeRegion->handleMouseClick(actualPosition, event.mouseButton.button);
                break;
            }
            case sf::Event::Resized:
                camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
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

		window.draw(shape);

		//end draw logic
		window.display();
	}


	return 0;
}