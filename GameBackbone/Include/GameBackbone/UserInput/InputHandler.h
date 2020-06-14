#pragma once

#include <GameBackbone/Core/Updatable.h>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <string>
#include <iostream>



namespace GB {

	class InputHandler
	{
	public:
		virtual bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) = 0;
	};

}
