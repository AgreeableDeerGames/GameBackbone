#pragma once

#include <exception>

namespace GB {
	namespace Error {

		/// <summary>
		/// Exception thrown when a FileReader fails to open a file.
		/// </summary>
		/// <seealso cref="std::exception" />
		class FileManager_BadFile : public std::exception
		{
		public:
			virtual const char* what() const noexcept override {
				return "Cannot open the file.";
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
			virtual const char* what() const noexcept override {
				return "Function is Not Implemented.";
			}
		};
	}
}

