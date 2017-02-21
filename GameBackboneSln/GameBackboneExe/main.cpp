#include "stdafx.h"

#include "AnimatedSprite.h"
#include "AnimationSet.h"
#include "GameWorldSprite.h"
#include "GameWorldAnimatedSprite.h"
#include "GameRegion.h"
#include "Updatable.h"
#include "CompoundSprite.h"
#include "GameWorldCompoundSprite2.h"
#include "GameWorldAnchor.h"

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

	//create sprites and textures THIS PROB WONT BE HERE WHEN MAIN GAME LOGIC IS ADDED

	//create sprite
	sf::Texture testSpriteTexture;
	testSpriteTexture.loadFromFile("..\\..\\Textures\\testSprite.png");
	sf::Sprite s(testSpriteTexture);

	//create GameWorldSprite
	GameWorldSprite gameWorldSprite(testSpriteTexture);
	gameWorldSprite.gMove(100, 100);

	//create animation set
	sf::Vector2u textureDim = testSpriteTexture.getSize();
	std::vector<std::vector<unsigned int>> aSpriteAnims;
	std::vector<unsigned int> aSpriteAnim1 = { 0, 1, 2, 3 };
	aSpriteAnims.push_back(aSpriteAnim1);
	AnimationSet* animSet = new AnimationSet(aSpriteAnims, textureDim.x, textureDim.y, 2, 2);

	//create animatedSprite
	AnimatedSprite aSprite(testSpriteTexture, animSet);
	aSprite.setAnimationDelay(1000);
	aSprite.runAnimation(0);

	//add objects to game region
	GameRegion testGameRegion;
	testGameRegion.setDrawable(true, &aSprite);
	testGameRegion.setUpdatable(true, &aSprite);

	testGameRegion.setDrawable(true, &s);


	//view
	sf::View camera(sf::FloatRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(camera);

	//main logic loop
	GameRegion* activeRegion = &testGameRegion;
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

	delete animSet;

	return 0;
}