#pragma once

#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/Util/Array2D.h>

#include <string>

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

		std::string createWritableString(Array2D<std::string>* dataArray, char delimiter) const;
		void writeString(const std::string& inString, const std::string& filePath) const;

	private:

	};
}
