#pragma once

#include <exception>

namespace GB {
	namespace Error {

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

		/// <summary>
		/// Exception thrown when a FileReader fails to open a file.
		/// </summary>
		/// <seealso cref="std::exception" />
		class FileManager_BadFile : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "Cannot open the file.";
			}
		};

		/// <summary>
		/// Exception thrown when a FileManager is passed an empty key.
		/// </summary>
		/// <seealso cref="std::exception" />
		class FileManager_EmptyKey : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "Encryption key is empty";
			}
		};

		/// <summary>
		/// Exception thrown when a function is intentionally "Not Implemented".
		/// If a function is calling this exception, please use a different solution.
		/// </summary>
		/// <seealso cref="std::exception" />
		class Function_NotImplemented : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "Function is Not Implemented.";
			}
		};

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
		/// Exception thrown when Component an illegal or unexpected nullptr is found.
		/// </summary>
		/// <seealso cref="std::exception" />
		class Pointer_IllegalNull : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "Illegal nullptr.";
			}
		};

		/// <summary>
		/// Exception thrown when Component and RelativeOffset vectors passed into
		/// RelativeRotationSprite are not equal in size.
		/// </summary>
		/// <seealso cref="std::exception" />
		class RelativeRotationSprite_MismatchedSizes : public std::exception
		{
		public:
			virtual const char* what() const override {
				return "The passed in vectors are of incompatible sizes.";
			}
		};
	}
}

