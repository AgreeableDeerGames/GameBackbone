#include <Util\FileReader.h>
#include <Backbone\BackboneBaseExceptions.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace GB;


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