#pragma once

#include <GameBackbone/Util/DllUtil.h>
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

	class libGameBackbone InputHandler
	{
	public:
		virtual bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) = 0;

		InputHandler() = default;
		virtual ~InputHandler() = default;
		InputHandler(const InputHandler&) = default;
		InputHandler(InputHandler&&) = default;
		InputHandler& operator=(const InputHandler&) = default;
		InputHandler& operator=(InputHandler&&) = default;
	};

}
