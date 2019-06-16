#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Util/Array2D.h>
#include <GameBackbone/Util/DllUtil.h>
#include <GameBackbone/Util/FileWriter.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace GB;


/// <summary>
/// Creates the writable string from an existing GB::Array2D populated with data.
/// </summary>
/// <param name="dataArray">The array populated with data. std::invalid_argument exception thrown if null or empty.</param>
/// <param name="delimiter">The delimiter for the output string.</param>
/// <returns></returns>
std::string FileWriter::createWritableString(GB::Array2D<std::string>* dataArray, char delimiter) const {
	//Ensure the 2D array exists and at least has something in it.
	if (dataArray == nullptr || dataArray->getArraySizeX() == 0) {
		throw std::invalid_argument("FileWriter::createWritableString data array null or empty.");
	}
	
	std::string outString;

	unsigned int columns = dataArray->getArraySizeX();
	unsigned int rows = dataArray->getArraySizeY();

	//Transfer the Array2D to string
	//For as many rows...
	for (unsigned int currentRow = 0; currentRow < rows; currentRow++) {
		//And as many columns
		for (unsigned int currentColumn = 0; currentColumn < columns; currentColumn++) {
			//Append the array value to the string. Don't check for row end before placing delimiter because it's quicker to just replace the last character in one operation than check every loop.
			outString.append( dataArray->at(currentRow, currentColumn) +  delimiter);
		}
		//Once a row is completed, replace last delimiter with newline. Same non-checking rationale as above.
		outString.replace(outString.end() - 1, outString.end(), "\n");
	}
	//Once the file is complete, remove the last newline.
	outString.pop_back();

	return outString;
}

/// <summary>
/// Writes the string to a file.
/// Throws a GB::Error::FileManager_BadFile exception if the file cannot be opened.
/// </summary>
/// <param name="inString">The formatted string to be written.</param>
/// <param name="filePath">The file path to write to.</param>
void FileWriter::writeString(const std::string& inString, const std::string& filePath) const{
	//Initialize File Writer in binary mode.
	std::ofstream outFile(filePath, std::ofstream::binary);
	std::size_t stringSize = inString.size();

	// Throw an error if the file could not be opened.
	if (!outFile.good())
	{
		throw Error::FileManager_BadFile();
	}

	//Interpret file as binary.
	char const * binaryText = inString.c_str();

	//Write binary string to file.
	outFile.write(binaryText, stringSize);
}