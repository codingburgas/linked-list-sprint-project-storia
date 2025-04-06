#pragma once
#include "pch.h"

class Ui
{
public:
	Ui();
	~Ui();

	void mainMenu();
private:
	void startScreen();

	void registerUi();
	void registerAsAdmin();

	void logInUi();

	void timeLIneUi();

	User* user;
};