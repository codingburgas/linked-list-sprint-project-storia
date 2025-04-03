#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Utiles
{
public:
	static nlohmann::json loadFile(const std::string& fileName);

	static void saveToFile(const std::string& fileName, const nlohmann::json& data);
	static bool isFileEmpty(const std::string& fileName);
};