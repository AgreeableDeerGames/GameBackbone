#include "stdafx.h"
#include "FileReader.h"

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
/// <param name="totalColumns">The number of columns to be read</param>
/// <param name="delimiter">The delimiter for the table type.</param>
/// <returns></returns>
Array2D<std::string> FileReader::readFile(std::string filePath, unsigned int totalRows, unsigned int totalColumns, char delimiter) {
	std::ifstream inFile(filePath);

	Array2D<std::string> fileArray = Array2D<std::string>(totalRows, totalColumns);

	std::string row = "";
	unsigned int rowIndex = 0;
	while (std::getline(inFile, row))
	{
		if (rowIndex < totalRows) {
			std::stringstream row_stream(row);

			std::string column = "";

			unsigned int columnIndex = 0;
			while (std::getline(row_stream, column, delimiter)) {
				if (columnIndex < totalColumns) {

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