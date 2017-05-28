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

void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
	std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
	std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
}

void loadWidgets(tgui::Gui& gui)
{
	// Load the black theme
	auto theme = tgui::Theme::create("TGUI_Widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	auto picture = tgui::Picture::create("..\\..\\Textures\\Backbone2.png");
	picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(200, windowHeight / 10.0f));
	gui.add(picture);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
	editBoxUsername->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxUsername->setPosition(windowWidth / 6, windowHeight / 6);
	editBoxUsername->setDefaultText("Username");
	gui.add(editBoxUsername, "Username");

	//// Create the password edit box
	//tgui::EditBox::Ptr editBoxPassword = theme->load("EditBox");
	//editBoxPassword->setSize(windowWidth * 2 / 3, windowHeight / 8);
	//editBoxPassword->setPosition(windowWidth / 6, windowHeight * 5 / 12);
	//editBoxPassword->setPasswordCharacter('*');
	//editBoxPassword->setDefaultText("Password");
	//gui.add(editBoxPassword, "Password");

	//// Create the login button
	//tgui::Button::Ptr button = theme->load("Button");
	//button->setSize(windowWidth / 2, windowHeight / 6);
	//button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	//button->setText("Login");
	//gui.add(button);

	// Call the login function when the button is pressed
	//button->connect("pressed", login, editBoxUsername, editBoxPassword);
}

int main() {
	//Init Window
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 700;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SpriteTests");
	
	tgui::Gui gui(window);
	
	try {
		// Load the widgets
		loadWidgets(gui);
	} catch (const tgui::Exception& e) {
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
		return 1;
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
                //camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				gui.setView(window.getView());
                break;
			default:
				break;
			}
			gui.handleEvent(event);
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
		gui.draw();


		//end draw logic
		window.display();
	}


	return 0;
}