#include "pch.h"

namespace Utiles
{
	//Set color to text
	void SetColor(int textColor)
	{
		std::cout << "\033[" << textColor << "m";
	}

	//Reset color to default
	void resetColor()
	{
		std::cout << "\033[0m";
	}

	//Returns data from JSON file 
	nlohmann::json loadFile(const std::string& fileName)
	{
		nlohmann::json dataToSave;
		std::ifstream file(fileName);

		if (file.is_open()) {
			file >> dataToSave;
			file.close();
		}
		else {
			std::cerr << "Could not open file for reading!" << std::endl;
		}

		return dataToSave;
	}

	//Displays the contents of a txt file
	void displayFile(const std::string& fileName) {
		std::ifstream file(fileName);

		if (file.is_open() || !isFileEmpty(fileName)) {
			std::cout << file.rdbuf() << std::endl;
			file.close();
		}
		else {
			std::cerr << "Could not open file for reading!" << std::endl;
		}
	}

	//Saves data to JSON file
	void saveToFile(const std::string& fileName, const nlohmann::json& data) {
		nlohmann::json existingData;
		nlohmann::json inData = data;

		if (!isFileEmpty(fileName)) {
			existingData = loadFile(fileName);
		}

		if (!existingData.is_array()) {
			existingData = nlohmann::json::array();
		}

		inData["id"] = existingData.size() + 1;
		existingData.push_back(inData);

		std::ofstream outFile(fileName);
		if (outFile.is_open()) {
			outFile << existingData.dump(4);
			outFile.close();
		}
		else {
			std::cerr << "Could not open file for writing!" << std::endl;
		}
	}

	//Checks if the given file can open
	bool isFileEmpty(const std::string& fileName) {
		std::ifstream file(fileName);

		if (!file.is_open()) {
			std::cerr << "Could not open the file!" << std::endl;
			return false;
		}

		file.seekg(0, std::ios::end);
		std::streampos fileSize = file.tellg();

		file.close();
		return fileSize == 0;
	}

	//Returns hash of a given string
	std::string sha256FromString(const std::string& input) {
		BYTE hash[32];
		SHA256_CTX ctx;

		Crypto::sha256_init(&ctx);
		Crypto::sha256_update(&ctx, reinterpret_cast<const BYTE*>(input.c_str()), input.size());
		Crypto::sha256_final(&ctx, hash);

		std::stringstream ss;
		for (int i = 0; i < 32; i++) {
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
		}

		return ss.str();
	}

}