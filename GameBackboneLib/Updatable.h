#pragma once
#include "GameBackboneLib.h"
#include<SFML\System\Clock.hpp>
class GAMEBACKBONELIB_API Updatable {
public:

	Updatable() {
	}

	virtual ~Updatable() {
	}

	virtual void update(sf::Time currentTime) = 0;

protected:
	sf::Time lastUpdate;
};

