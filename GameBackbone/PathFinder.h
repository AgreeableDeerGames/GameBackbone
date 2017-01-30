#pragma once

#include <sfml/Graphics/Sprite.hpp>
#include <SFML\Graphics.hpp>

#include <vector>

class Pathfinder {
public:
	Pathfinder();

	virtual ~Pathfinder();

	void pathfind(sf::Vector2f start, sf::Vector2f finish);


private:
	std::vector<sf::Sprite*>* pathBlockers;
};

