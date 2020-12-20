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
	
	/// @brief Interface for consuming user input produced by the GB event loop.
	class libGameBackbone InputHandler
	{
	public:

		/// @brief Handle and optionally consume a user event.
		/// @param elapsedTime The time since the last event was handled.
		/// @param event The event to handle.
		/// @return True if the event was consumed and should not be handled by a different handler
		///		False otherwise.
		virtual bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) = 0;

		InputHandler() = default;
		virtual ~InputHandler() = default;
		InputHandler(const InputHandler&) = default;
		InputHandler(InputHandler&&) = default;
		InputHandler& operator=(const InputHandler&) = default;
		InputHandler& operator=(InputHandler&&) = default;
	};

}
