#include "pch.h"  

void startScreen()
{
    std::ifstream f("../assets/graphic/startScreen.txt");

    if (f.is_open())
        SetColor(32);
    std::cout << f.rdbuf() << std::endl;

    while (std::cin.get() == '\n') {
        mainMenu();
        break;
    }
    resetColor();
}

void mainMenu() {

    //Clear console
    system("cls");

    int choice;

    std::ifstream f("../assets/graphic/header.txt");

    if (f.is_open()) std::cout << f.rdbuf();

    std::cin >> choice;

    resetColor();
}