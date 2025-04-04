#pragma once
#include "pch.h"

class UI
{
public:
	UI();
	~UI();

	void mainMenu();
private:
	void startScreen();
	void registerUI();
	void logInUi();

	User* user;
};

