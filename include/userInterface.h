#pragma once
#include "pch.h"

class Ui
{
public:
	Ui();
	~Ui();

	void mainMenu();
	void timeLineUi();
private:
	void startScreen();

	void registerUi();
	void registerAsAdmin();

	void logInUi();

	User* user;
};