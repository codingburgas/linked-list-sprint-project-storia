#include "pch.h"
#include "CppUnitTest.h"
#include "../include/user.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UserTests)
	{
	public:
		TEST_METHOD_INITIALIZE(SetUp)
		{
			nlohmann::json testData = nlohmann::json::array();
			nlohmann::json user1;
			user1["id"] = 1;
			user1["email"] = "test@example.com";
			user1["userName"] = "TestUser";
			user1["password"] = "Password123!";
			user1["isAdmin"] = false;
			testData.push_back(user1);

			std::ofstream testFile("test_users.json");
			testFile << testData.dump(4);
			testFile.close();

			std::ofstream emptyFile("empty_test.json");
			emptyFile.close();
		}
		TEST_METHOD(Constructor_SetsDefaultValues)
		{
			User user;
			Assert::IsFalse(user.getIsAdmin());
			Assert::IsTrue(user.isUserEmpty());
		}

		TEST_METHOD(GetterSetter_AdminStatus)
		{
			User user;
			Assert::IsFalse(user.getIsAdmin());
			user.setAdmin();
			Assert::IsTrue(user.getIsAdmin());
		}

		TEST_METHOD(GetterSetter_UserName)
		{
			User user;
			std::string testName = "TestUser";
			user.setUserName(testName);
			Assert::AreEqual(testName, user.getUserName());
		}

		TEST_METHOD(CheckEmail_ValidEmail_ReturnsTrue)
		{
			User user;
			bool result = user.checkEmail("unique@example.com", "empty_test.json");
			Assert::IsTrue(result);
			Assert::AreEqual(std::string("unique@example.com"), user.getEmail());
		}

		TEST_METHOD(CheckEmail_InvalidFormat_ReturnsFalse)
		{
			User user;
			bool result = user.checkEmail("invalid-email", "empty_test.json");
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckEmail_DuplicateEmail_ReturnsFalse)
		{
			User user;
			bool result = user.checkEmail("test@example.com", "test_users.json");
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckPassword_ValidPassword_ReturnsTrue)
		{
			User user;
			std::string testPassword = "Password123!";
			bool result = user.checkPassword(testPassword);
			Assert::IsTrue(result);
			Assert::AreEqual(testPassword, user.getPassword());
		}

		TEST_METHOD(CheckPassword_TooShort_ReturnsFalse)
		{
			User user;
			bool result = user.checkPassword("Pw!");
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckPassword_NoSpecialChar_ReturnsFalse)
		{
			User user;
			bool result = user.checkPassword("Password123");
			Assert::IsFalse(result);
		}

		TEST_METHOD(IsUserEmpty_NewUser_ReturnsTrue)
		{
			User user;
			Assert::IsTrue(user.isUserEmpty());
		}

		TEST_METHOD(IsUserEmpty_AfterSettingEmail_ReturnsFalse)
		{
			User user;
			user.checkEmail("test@example.com", "empty_test.json");
			Assert::IsFalse(user.isUserEmpty());
		}

		TEST_METHOD(EraseUser_ClearsAllUserData)
		{
			User user;
			user.checkEmail("test@example.com", "empty_test.json");
			user.checkPassword("Password123!");
			user.setUserName("TestUser");
			user.setAdmin();

			user.eraseUser();

			Assert::IsTrue(user.isUserEmpty());
			Assert::AreEqual(std::string(""), user.getEmail());
			Assert::AreEqual(std::string(""), user.getPassword());
			Assert::AreEqual(std::string(""), user.getUserName());
			Assert::IsFalse(user.getIsAdmin());
		}
		TEST_METHOD(SaveAsJson_CreatesCorrectJsonObject)
		{
			User user;
			user.checkEmail("test@example.com", "empty_test.json");
			user.checkPassword("Password123!");
			user.setUserName("TestUser");

			nlohmann::json userData = user.saveAsJson();

			Assert::IsTrue(userData.contains("email"));
			Assert::IsTrue(userData.contains("password"));
			Assert::IsTrue(userData.contains("userName"));
			Assert::IsTrue(userData.contains("isAdmin"));
			Assert::AreEqual(std::string("TestUser"), userData["userName"].get<std::string>());
			Assert::IsFalse(userData["isAdmin"].get<bool>());
		}
		TEST_METHOD(LoadFromFile_ExistingUser_ReturnsTrue)
		{
			User user;
			bool result = user.loadFromFile("test_users.json", "test@example.com");

			Assert::IsTrue(result);
			Assert::AreEqual(std::string("test@example.com"), user.getEmail());
			Assert::AreEqual(std::string("TestUser"), user.getUserName());
		}

		TEST_METHOD(LoadFromFile_NonExistingUser_ReturnsFalse)
		{
			User user;
			bool result = user.loadFromFile("test_users.json", "nonexistent@example.com");

			Assert::IsFalse(result);
		}

		TEST_METHOD(LoadFromFile_EmptyFile_ReturnsFalse)
		{
			User user;
			bool result = user.loadFromFile("empty_test.json", "test@example.com");

			Assert::IsFalse(result);
		}
	};
}