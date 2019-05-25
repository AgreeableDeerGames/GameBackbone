#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/System/Clock.hpp>

namespace GB {

	/// <summary> Abstract class meant to be inherited. Class that is capable of being updated. </summary>
	class libGameBackbone Updatable {
	public:
		Updatable() = default;
		Updatable(const Updatable&) = default;
		Updatable& operator=(const Updatable&) = default;
		Updatable(Updatable&&) noexcept = default;
		Updatable& operator=(Updatable&&) noexcept = default;
		virtual ~Updatable() = default;

		virtual void update(sf::Int64 elapsedTime) = 0;
	};

}
