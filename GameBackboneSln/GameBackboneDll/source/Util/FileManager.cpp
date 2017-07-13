
#include <Backbone\BackboneBaseExceptions.h>
#include <Util\FileManager.h>
#include <Util\FileReader.h>

#include <string>

using namespace GB;

FileManager::FileManager()
{
	reader = new FileReader;
}

FileManager::~FileManager()
{
	delete reader;
}

std::string FileManager::encryptDecryptString(std::string stringToChange, const std::string key){
	std::string output = stringToChange;

	for (int i = 0; i < stringToChange.size(); i++)
	{
		output[i] = stringToChange[i] ^ key[(i % key.size())];
	}

	return output;
}