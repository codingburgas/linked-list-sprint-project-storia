#pragma once
#include "pch.h"

class Ui
{
public:
	Ui();
	~Ui();

	void mainMenu();
	void timeLIneUi();
private:
	void startScreen();

	void registerUi();
	void registerAsAdmin();

	void logInUi();



	User* user;
};