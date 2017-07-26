
#include <Backbone\BackboneBaseExceptions.h>
#include <Util\FileManager.h>
#include <Util\FileReader.h>

#include <string>
#include <sys/stat.h>

using namespace GB;

FileManager::FileManager()
{
	reader = new FileReader;
}

FileManager::~FileManager()
{
	delete reader;
}

/// <summary>
/// Encrypts or decrypts a string.
/// </summary>
/// <param name="stringToChange">The string to be encrypted.</param>
/// <param name="key">The key for the encryption.</param>
/// <returns></returns>
std::string FileManager::encryptDecryptString(const std::string& stringToEncrypt, const std::string& key) {
	if (key.empty()){
		throw Error::FileManager_EmptyKey();
	}

	std::string output = stringToEncrypt;

	for (unsigned int ii = 0; ii < stringToEncrypt.size(); ++ii)
	{
		// XOR the char in stringToChange with the corresponding char from the key.
		output[ii] = stringToEncrypt[ii] ^ key[(ii % key.size())];
	}

	return output;
}


/**
* Get the size of a file.
* @param filename The name of the file to check size for
* @return The file size, or 0 if the file does not exist.
*/
size_t FileManager::getFileSize(const std::string& filename) {
	struct stat st;
	if (stat(filename.c_str(), &st) != 0) {
		return 0;
	}
	return st.st_size;
}

size_t FileManager::getFileHash(const std::string& filename) {


	size_t hashed = std::hash<std::string>{}(filename);
	return hashed;
}