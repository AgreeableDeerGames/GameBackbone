#pragma once
#include <Util\stdafx.h>

#include <exception>

namespace GB {
	namespace Error {

		/// <summary>
		/// Exception thrown when a GameRegion attempts to disassociate a
		/// non-associated GameRegion.
		/// </summary>
		/// <seealso cref="std::exception" />
		class GameRegion_BadDissociation : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "Attempting to remove a non-associated object is not allowed";
			}
		};

		/// <summary>
		/// Exception thrown when an AnimatedSprite tries to run an empty animation.
		/// </summary>
		/// <seealso cref="std::exception" />
		class AnimatedSprite_EmptyAnimation : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "Cannot run an empty animation.";
			}
		};
	}
}

