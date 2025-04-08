#pragma once
#include "pch.h"

class Timeline;

class Ui
{
public:
	Ui();
	~Ui();

	void mainMenu();
	void timeLineUi();
private:
	void startScreen();
	void displeyMenuMsg(std::string msg);

	void registerUi();
	void registerAsAdmin();

	void logInUi();
	void adminTimeLine(const std::string& fileName, Timeline& timeline);

	User* user;
};