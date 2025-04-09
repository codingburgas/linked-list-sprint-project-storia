#pragma once
#include"pch.h"

class Stages
{
public:
	static void stagesMenu(Ui& ui);
private:
	void displayStage(const std::string& mapPath, const std::string& infoPath);
	void choiceSwitch(const std::string& Leaders, Ui& ui);
};
