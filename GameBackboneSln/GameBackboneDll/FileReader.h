#pragma once
#include "stdafx.h"
#include "DllUtil.h"
#include "Array2D.h"


#include<random>
#include<string>

namespace GB {

	/// <summary>
	/// TODO: Update this thing.
	/// </summary>

	class libGameBackbone FileReader {
	public:
		FileReader();

		FileReader(const FileReader& generator) = default;
		FileReader(FileReader&& generator) = default;
		FileReader& operator= (const FileReader& generator) = default;
		FileReader& operator= (FileReader&& generator) = default;
		~FileReader() = default;


		Array2D<std::string> ReadFile(std::string filePath, unsigned int totalRows, unsigned int totalColumns, char delimiter);
	private:

	};
}
