#include "pch.h"

void stagesMenu()
{
    //Clear console
    system("cls");

    int choice;

    std::ifstream f("../assets/graphic/stagesHeader.txt");

    if (f.is_open()) std::cout << f.rdbuf();

    std::cin >> choice;
}