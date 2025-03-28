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

    std::ifstream f("../assets/graphic/header.txt");

    if (f.is_open()) std::cout << f.rdbuf();

    char choice;

    //Loop until valid choice
    while (true) {
        std::cin >> choice;
            switch (choice) {
            case '3':
                stagesMenu();
                resetColor();
                return;
            default:
                std::cout << "You've entered an invalid option. Please try again." << std::endl;
                break;
            }
    }
}