#include "pch.h"

void formation681()
{
    system("cls");

    char choice;

    std::ifstream f("../assets/graphic/stages/681-814.txt");
    std::ifstream Leaders("../assets/graphic/stages/681-814Leaders.txt");

    if (f.is_open()) std::cout << f.rdbuf() << std::endl;

    std::cout << "Choice: ";
    //Loop until valid choice
    while (true) {
        std::cin >> choice;
        switch (choice) {
        case 'Y':
            if (Leaders.is_open()) std::cout << Leaders.rdbuf() << std::endl;
            resetColor();
            return;
        case 'N':
            stagesMenu();
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }

}

void stagesMenu()
{
    //Clear console
    system("cls");

    char choice;

    std::ifstream f("../assets/graphic/stagesHeader.txt");

    if (f.is_open()) std::cout << f.rdbuf() << std::endl;

    while (true) {
        std::cout << "Choice: ";
        std::cin >> choice;
        switch (choice) {
        case '1':
            // func
            resetColor();
            return;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}