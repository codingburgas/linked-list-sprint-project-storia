#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Utiles
{
public:
	static void SetColor(int textColor);
	static void resetColor();

	static nlohmann::json loadFile(const std::string& fileName);
	static void displayFile(const std::string& fileName);

	static void saveToFile(const std::string& fileName, const nlohmann::json& data);
	static std::string sha256FromString(const std::string& input);

	static bool isFileEmpty(const std::string& fileName);
};