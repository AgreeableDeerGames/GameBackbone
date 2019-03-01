#pragma once

#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/Util/Array2D.h>

#include <string>

namespace GB {

	/// <summary>
	/// Use this to read in a file.
	/// </summary>
	class libGameBackbone FileReader {
	public:
		FileReader() = default;
		FileReader(const FileReader& reader) = default;
		FileReader(FileReader&& reader) = default;
		FileReader& operator= (const FileReader& reader) = default;
		FileReader& operator= (FileReader&& reader) = default;
		~FileReader() = default;


		Array2D<std::string> createArray2D(const std::string& inString, unsigned int totalRows, unsigned int totalColumns, char delimiter) const;
		std::string readFile(const std::string& filePath) const;

	private:

	};
}
