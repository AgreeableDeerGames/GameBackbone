#include <GameBackbone/Core/BackboneBaseExceptions.h>
#include <GameBackbone/Util/FileReader.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace GB;

Array2D<std::string> FileReader::createArray2D(const std::string& inString, unsigned int totalRows, unsigned int totalColumns, char delimiter) const {
	// Create the array that will be returned
	Array2D<std::string> fileArray = Array2D<std::string>(totalRows, totalColumns);

	std::stringstream stringStream;
	stringStream.str(inString);
	

	// Setup for the rows/lines
	std::string row;
	unsigned int rowIndex = 0;

	// While not last line
	while (std::getline(stringStream, row, '\n')) {
		// Only read until the line that the user specified
		if (rowIndex < totalRows) {

			// Setup for the columns
			std::stringstream row_stream(row);
			std::string column;
			unsigned int columnIndex = 0;

			// Split the line up based on the delimiter until the last one
			while (std::getline(row_stream, column, delimiter)) {
				// Only read until the column that the user specified
				if (columnIndex < totalColumns) {

					// Set the fileArray's string at the given indices
					fileArray[rowIndex][columnIndex] = column;
					columnIndex++;
				}
				else {
					break;
				}
			}
			rowIndex++;
		}
		else {
			break;
		}
	}

	return fileArray;
}

/// <summary>
/// Reads the file as a binary.
/// </summary>
/// <param name="filePath">The file path.</param>
/// <returns></returns>
std::string FileReader::readFile(const std::string& filePath) const {
	std::ifstream inFile(filePath);

	// Throw an error if the file could not be opened
	if (!inFile.good())
	{
		throw Error::FileManager_BadFile();
	}

	std::string savedString((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	
	return savedString;
}