#pragma once
#include "pch.h"

class Ui
{
public:
	Ui();
	~Ui();

	void mainMenu();
	void timeLineUi();
	static void listenForEscape(Ui& ui);
private:
	void startScreen();
	void displeyMenuMsg(std::string msg);

	void registerUi();
	void registerAsAdmin();

	void logInUi();

	User* user;
};