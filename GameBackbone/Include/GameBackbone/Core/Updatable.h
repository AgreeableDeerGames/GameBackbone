#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/System/Clock.hpp>

namespace GB {

	/// @brief Interface representing objects that are capable of being updated over time.
	class libGameBackbone Updatable {
	public:
		Updatable() = default;
		Updatable(const Updatable&) = default;
		Updatable& operator=(const Updatable&) = default;
		Updatable(Updatable&&) noexcept = default;
		Updatable& operator=(Updatable&&) noexcept = default;
		virtual ~Updatable() = default;

		/// @brief Updates the instance.
		/// @param elapsedTime Time (in microseconds) since the instance was last updated.
		virtual void update(sf::Int64 elapsedTime) = 0;
	};

}
