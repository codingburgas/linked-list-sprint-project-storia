#pragma once

#include <nlohmann/json.hpp>
#include <string>

class User
{
public:
	User();

	size_t getId();
	bool getIsAdmin();
	std::string getEmail();
	std::string getPassword();
	std::string getUserName();

	void setUserName(std::string name);
	void setAdmin();

	bool checkEmail(const std::string& email, const std::string& fileName);
	bool checkPassword(const std::string& password);
	bool isUserEmpty();

	nlohmann::json saveAsJson();
	bool loadFromFile(const std::string& fileName, const std::string& emailToFind);

	void displayUser();
	void eraseUser();
private:

	size_t id;
	bool isAdmin;
	std::string email;
	std::string password;
	std::string userName;
};