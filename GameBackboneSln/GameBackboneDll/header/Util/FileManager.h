#pragma once

#include <Util\DllUtil.h>
#include <Util\Array2D.h>
#include <Util\FileReader.h>

#include<string>

namespace GB {

	/// <summary>
	/// Use this to read in a file.
	/// </summary>
	class libGameBackbone FileManager {
	public:
		FileManager();
		FileManager(const FileManager& generator) = default;
		FileManager(FileManager&& generator) = default;
		FileManager& operator= (const FileManager& generator) = default;
		FileManager& operator= (FileManager&& generator) = default;
		~FileManager();


		std::string encryptDecryptString(std::string stringToChange, const std::string key);
	private:
		FileReader* reader;

	};
}