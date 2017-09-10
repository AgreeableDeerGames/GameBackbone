#include <Util\FileWriter.h>
#include <Backbone\BackboneBaseExceptions.h>
#include <Util\DllUtil.h>
#include <Util\Array2D.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace GB;


/// <summary>
/// Creates the writable string from an existing GB::Array2D populated with data.
/// </summary>
/// <param name="dataArray">The array populated with data.</param>
/// <param name="delimiter">The delimiter for the output string.</param>
/// <returns></returns>
std::string FileWriter::createWritableString(GB::Array2D<std::string>* dataArray, char delimiter) {
	//Ensure the 2D array exists and at least has something in it.
	if (dataArray == nullptr || dataArray->getArraySizeX() == 0) {
		throw Error::FileWriter_EmptyArray2D();
	}
	
	std::string outString = "";

	unsigned int columns = dataArray->getArraySizeX();
	unsigned int rows = dataArray->getArraySizeY();

	//Transfer the Array2D to string
	//For as many rows...
	for (unsigned int currentRow = 0; currentRow < rows; currentRow++) {
		//And as many columns
		for (unsigned int currentColumn = 0; currentColumn < columns; currentColumn++) {
			//Append the array value to the string. Don't check for row end before placing delimiter becasue it's quicker to just replace the last character in one operation than check every loop.
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
/// </summary>
/// <param name="inString">The formatted string to be written.</param>
/// <param name="filePath">The file path to write to.</param>
void FileWriter::writeString(std::string outString, std::string filePath) {
	//Initialize File Writer in binary mode.
	std::ofstream outFile(filePath, std::ofstream::binary);
	size_t stringSize = outString.size();

	// Throw an error if the file could not be opened.
	if (!outFile.good())
	{
		throw Error::FileReader_BadFile();
	}

	//Interpret file as binary.
	char const * binaryText = outString.c_str();

	//Write binary string to file.
	outFile.write(binaryText, stringSize);
}