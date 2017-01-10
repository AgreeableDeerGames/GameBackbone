#pragma once

#include<SFML\System\Clock.hpp>
class Updatable {
public:

	Updatable() {
	}

	virtual ~Updatable() {
	}

	virtual void update(sf::Time currentTime) = 0;

protected:
	sf::Time lastUpdate;
};

