#include <Util\FileReader.h>
#include <Backbone\BackboneBaseExceptions.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace GB;

/// <summary>
/// Reads the file and splits it up using the delimiter.
/// </summary>
/// <param name="filePath">The path to the file to be read. This can be relative or full.</param>
/// <param name="totalRows">The number of lines to be read.</param>
/// <param name="totalColumns">The number of columns to be read.</param>
/// <param name="delimiter">The delimiter for the table type.</param>
/// <returns>Returns an Array2D of size totalRows by totalColumns. Each row represents a new line in the input file. 
/// Each column represents a value within that row.
/// </returns>
Array2D<std::string> FileReader::readFile(std::string filePath, unsigned int totalRows, unsigned int totalColumns, char delimiter) {
	std::ifstream inFile(filePath);

	// Throw an error if the file could not be opened
	if (!inFile.good())
	{
		throw Error::FileReader_BadFile();
	}

	// Create the array that will be returned
	Array2D<std::string> fileArray = Array2D<std::string>(totalRows, totalColumns);

	// Setup for the rows/lines
	std::string row = "";
	unsigned int rowIndex = 0;

	// While not last line
	while (std::getline(inFile, row)){
		// Only read until the line that the user specified
		if (rowIndex < totalRows) {

			// Setup for the columns
			std::stringstream row_stream(row);
			std::string column = "";
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
		else{
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
std::string FileReader::readFileBinaryInput(std::string filePath) {
	std::ifstream inFile(filePath);

	// Throw an error if the file could not be opened
	if (!inFile.good())
	{
		throw Error::FileReader_BadFile();
	}

	std::string savedString;
	std::string tempString = "";
	
	// We need to do this line by line with a '\0' as the delimiter because normally '\0' splits the string.
	while (std::getline(inFile, tempString, '\0')) {
		savedString += tempString;
		tempString = "";

		// Add the '\0' that we removed back into the string
		savedString += '\0';
	}

	// NOTWORKING: This was my (michaels) attempt at trying to fix the issue with a file ending in '\0'
	//if (savedString[savedString.size() - 1] != '\0')
	//{
		// Remove the last '\0' from the string
		savedString.pop_back();
	//}
	
	return savedString;
}