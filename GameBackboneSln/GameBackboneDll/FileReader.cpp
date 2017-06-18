#include "stdafx.h"
#include "FileReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace GB;

FileReader::FileReader() {

}

Array2D<std::string> FileReader::ReadFile(std::string filePath, unsigned int totalRows, unsigned int totalColumns, char delimiter) {
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