#include "AnimatedSprite.h"
#include "AnimationSet.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <vector>


int main() {
	sf::RenderWindow window(sf::VideoMode(700, 700), "SpriteTests");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//init game update clock
	sf::Clock updateClock;

	//create sprites and textures THIS PROB WONT BE HERE WHEN MAIN GAME LOGIC IS ADDED

		//create sprite
	sf::Texture testSpriteTexture;
	testSpriteTexture.loadFromFile("..\\Textures\\testSprite.png");
	sf::Sprite s(testSpriteTexture);

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

	//main logic loop
	while (window.isOpen()) {
		//close window
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//draw loop
		window.clear();
		//draw logic here

		

		window.draw(aSprite);
		
		aSprite.update(updateClock.getElapsedTime());


		//window.draw(shape);


		//end draw logic
		window.display();
	}

	return 0;
}