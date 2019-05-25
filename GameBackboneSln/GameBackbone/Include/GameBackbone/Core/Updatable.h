#pragma once

#include <GameBackbone/Util/DllUtil.h>

#include <SFML/System/Clock.hpp>

namespace GB {

	/// <summary> Abstract class meant to be inherited. Class that is capable of being updated. </summary>
	class libGameBackbone Updatable {
	public:

		Updatable() {
		}

		virtual ~Updatable() {
		}

		/// <summary>Updates the instance.</summary>
		/// <param name="elapsedTime"> </param>
		virtual void update(sf::Int64 elapsedTime) = 0;
	};

}
