#pragma once

#include <Util\DllUtil.h>
#include <Util\Array2D.h>

#include<string>

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


		Array2D<std::string> readFile(std::string filePath, unsigned int totalRows, unsigned int totalColumns, char delimiter);
		std::string FileReader::readFileBinaryInput(std::string filePath);
	private:

	};
}
