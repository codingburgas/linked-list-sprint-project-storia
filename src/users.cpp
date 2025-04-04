#include "../include/User.h"
#include "../include/Utiles.h"

#include <iostream>
#include <cstdlib>
#include <regex>
#include <fstream>

using std::string;
using std::cout;

User::User() {
	this->isAdmin = false;
}

bool User::checkEmail(const string& email, const string& fileName)
{
	nlohmann::json data;
	if (!Utiles::isFileEmpty(fileName)) {
		data = Utiles::loadFile(fileName);
	}

	for (const auto& item : data) {
		if (item["email"] == email) {
			cout << "     Email already exists: "  ;
			return false;
		}
	}
	std::regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
	if (!std::regex_match(email, email_regex)) {
		cout << "     Invalid email: ";
		return false;
	}

	string domain = email.substr(email.find('@') + 1);
	string command = "nslookup -type=MX " + domain + " > nul 2>&1";

	if (std::system(command.c_str()) == 0) {
		this->email = email;
		return true;
	}
	else {
		cout << "     Invalid email domain: ";
		return false;
	}
}

bool User::checkPassword(const string& password)
{
	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	if (password.size() < 6)
	{
		cout << "     Password must be at least 6 characters long: ";
		return false;
	}
	for (size_t i = 0; i < 10; i++)
	{
		if (password.find(specialCharacters[i]) != string::npos) {
			this->password = password;
			return true;
		}
	}
	cout << "     Password must contain at least one special character: ";
	return false;
}

nlohmann::json User::saveAsJson() {
	nlohmann::json data;
	data["email"] = this->email;
	data["password"] = this->password;
	data["userName"] = this->userName;
	data["isAdmin"] = this->isAdmin;
	return data;
}

bool User::loadFromFile(const string& fileName, const string& emailToFind)
{
	nlohmann::json data;
	if (!Utiles::isFileEmpty(fileName)) {
		data = Utiles::loadFile(fileName);
	}

	for (const auto& item : data) {
		if (item["email"] == emailToFind) {
			this->id = item["id"];
			this->email = item["email"];
			this->userName = item["userName"];
			this->password = item["password"];
			return true;
		}
	}
	std::cerr << "User not found!";
	return false;
}

void User::displayUser()
{
	cout << "id: " << this->id << "\n";
	cout << "Email: " << this->email << "\n";
	cout << "Username: " << this->userName << "\n";
	cout << "Password: " << this->password << "\n";
}

void User::eraseUser() {
	this->email = "";
	this->userName ="";
	this->password = "";
	this->isAdmin = false;
}

string User::getEmail()
{
	return this->email;
}

string User::getPassword()
{
	return this->password;
}

string User::getUserName()
{
	return this->userName;
}

size_t User::getId()
{
	return this->id;
}

bool User::getIsAdmin() 
{
	return this->isAdmin;
}

void User::setAdmin() 
{
	this->isAdmin = true;
}

void User::setUserName(std::string name) {
	this->userName = name;
}
