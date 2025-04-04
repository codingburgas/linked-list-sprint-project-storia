#pragma once

#include <nlohmann/json.hpp>
#include <string>

class User
{
public:

	size_t getId();
	std::string getEmail();
	std::string getPassword();
	std::string getUserName();

	void setUserName(std::string name);
	bool checkEmail(const std::string& email, const std::string& fileName);
	bool checkPassword(const std::string& password);

	nlohmann::json saveAsJson();
	bool loadFromFile(const std::string& fileName, const std::string& emailToFind);

	void displayUser();
	void eraseUser();
private:
	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	size_t id;
	std::string email;
	std::string password;
	std::string userName;
};