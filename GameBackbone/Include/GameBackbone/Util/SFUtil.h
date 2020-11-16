#pragma once

#include <GameBackbone/Util/UtilMath.h>

#include <SFML/System/Vector2.hpp>

#include <math.h>


namespace GB {
	
	/// @brief Used to compare which of two sf::Vector2 is less
	///		Designed to facilitate map and set use of sf::Vector2
	/// @tparam T The type stored by the sf::Vector2. Must support operator<.
	template <typename T>
	class IsVector2Less {
	public:
		constexpr bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
			return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
		}
	};

	/// @brief Moves the transformable in the direction of the destination.
	///		The transformable will never overshoot the destination.
	/// @tparam Transformable Any class implementing the interface of sf::Transformable
	/// @param transformable The transformable to move.
	/// @param destination The destination.
	/// @param maxStepLength Maximum length that the transformable can move.
	/// @param shouldRotate Whether or not transformables should rotate towards their destination. If true, they will be rotated.
	template <class Transformable>
	void stepTowardsPoint(Transformable& transformable,
		const sf::Vector2f& destination,
		const float maxStepLength,
		const bool shouldRotate = true)
	{
		// Calculate the angle to the destination
		const sf::Vector2f currentPosition = transformable.getPosition();
		float angleToDest = atan2f(destination.y - currentPosition.y, destination.x - currentPosition.x);

		// Calculate the distance to the destination
		float distanceToDestination = calcDistance2D<float, sf::Vector2f>(currentPosition, destination);

		// Move directly to the destination if it's within reach
		if (distanceToDestination <= maxStepLength) {
			transformable.setPosition(destination);
		}
		// Move the Transformable as close as possible to the destination
		else {
			float xProgress = cosf(angleToDest) * maxStepLength;
			float yProgress = sinf(angleToDest) * maxStepLength;

			transformable.move(xProgress, yProgress);
		}

		// Rotate the Transformable if rotation is on
		if (shouldRotate && distanceToDestination != 0) {
			transformable.setRotation(angleToDest * 180.0f / (float)M_PI);
		}
	}

}
