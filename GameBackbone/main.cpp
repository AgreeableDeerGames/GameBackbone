#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(700, 700), "SpriteTests");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

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

		sf::Texture testSpriteTexture;
		testSpriteTexture.loadFromFile("..\\Textures\\testSprite.png");

		sf::Sprite s(testSpriteTexture);

		window.draw(s);
		


		//window.draw(shape);


		//end draw logic
		window.display();
	}

	return 0;
}