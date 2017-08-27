#pragma once

#include <Util\DllUtil.h>
#include <Util\Array2D.h>

#include<string>

namespace GB {

	/// <summary>
	/// Use this to write in a file.
	/// </summary>
	class libGameBackbone FileWriter {
	public:
		FileWriter() = default;
		FileWriter(const FileWriter& reader) = default;
		FileWriter(FileWriter&& reader) = default;
		FileWriter& operator= (const FileWriter& reader) = default;
		FileWriter& operator= (FileWriter&& reader) = default;
		~FileWriter() = default;


		void createWritableString(Array2D<std::string>* dataArray, char delimiter, std::string* outString);
		void writeString(std::string inString, std::string filePath);


	private:

	};
}
