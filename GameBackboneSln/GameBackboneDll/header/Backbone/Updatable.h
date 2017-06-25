#pragma once

#include <Util\DllUtil.h>
#include <SFML\System\Clock.hpp>

namespace GB {

	/// <summary> Abstract class meant to be inherited. Class that is capable of being updated. </summary>
	class libGameBackbone Updatable {
	public:

		Updatable() {
		}

		virtual ~Updatable() {
		}

		virtual void update(sf::Time currentTime) = 0;

	protected:
		sf::Time lastUpdate;
	};

}
