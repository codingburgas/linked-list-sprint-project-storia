#include "pch.h"

void formation681()
{
    system("cls");

    char choice;

    std::ifstream Info("../assets/graphic/stages/681-814.txt");
    std::ifstream Leaders("../assets/graphic/stages/681-814Leaders.txt");

    if (Info.is_open()) std::cout << Info.rdbuf() << std::endl;

    std::cout << "Choice: ";
    //Loop until valid choice
    while (true) {
        std::cin >> choice;
        switch (choice) {
        case 'Y':
            system("cls");
            if (Leaders.is_open()) std::cout << Leaders.rdbuf() << std::endl;
            char goBack;
            std::cout << "Choice: ";
            while (true) {
                std::cin >> goBack;
                switch (goBack)
                {
                case 'N':
                    system("cls");
                    formation681();
                    break;
                case 'M':
                    system("cls");
                    mainMenu();
                    break;
                default:
                    std::cout << "You've entered an invalid option. Please try again." << std::endl;
                    break;
                }
            }
        case 'N':
            stagesMenu();
            break;
        case 'M':
            system("cls");
            mainMenu();
            break;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }

}

void goldenAge814()
{
    system("cls");

    char choice;

    std::ifstream Info("../assets/graphic/stages/814-983.txt");
    std::ifstream Leaders("../assets/graphic/stages/814-983Leaders.txt");

    if (Info.is_open()) std::cout << Info.rdbuf() << std::endl;

    std::cout << "Choice: ";

    //Loop until valid choice
    while (true) {

        std::cin >> choice;
        switch (choice) {
        case 'Y':
            system("cls");
            if (Leaders.is_open()) std::cout << Leaders.rdbuf() << std::endl;
            char goBack;
            std::cout << "Choice: ";
            while (true) {
                std::cin >> goBack;

                switch (goBack)
                {
                case 'N':
                    system("cls");
                    formation681();
                    break;
                case 'M':
                    system("cls");
                    mainMenu();
                    break;
                default:
                    std::cout << "You've entered an invalid option. Please try again." << std::endl;
                    break;
                }
            }

        case 'N':
            stagesMenu();
            break;
        case 'M':
            system("cls");
            mainMenu();
            break;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}

void byzantineConquest983(){
    system("cls");

    char choice;

    std::ifstream Info("../assets/graphic/stages/983-1018.txt");
    std::ifstream Leaders("../assets/graphic/stages/983-1018Leaders.txt");

    if (Info.is_open()) std::cout << Info.rdbuf() << std::endl;

    std::cout << "Choice: ";

    //Loop until valid choice
    while (true) {

        std::cin >> choice;
        switch (choice) {
        case 'Y':
            system("cls");
            if (Leaders.is_open()) std::cout << Leaders.rdbuf() << std::endl;
            char goBack;
            std::cout << "Choice: ";
            while (true) {
                std::cin >> goBack;

                switch (goBack)
                {
                case 'N':
                    system("cls");
                    formation681();
                    break;
                case 'M':
                    system("cls");
                    mainMenu();
                    break;
                default:
                    std::cout << "You've entered an invalid option. Please try again." << std::endl;
                    break;
                }
            }

        case 'N':
            stagesMenu();
            break;
        case 'M':
            system("cls");
            mainMenu();
            break;
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

    std::ifstream Menu("../assets/graphic/stagesHeader.txt");

    if (Menu.is_open()) std::cout << Menu.rdbuf() << std::endl;

    while (true) {
        std::cout << "Choice: ";
        std::cin >> choice;
        switch (choice) {
        case '1':
            formation681();
            resetColor();
            return;
        case '2':
            goldenAge814();
            resetColor();
            return;
        case '3':
            byzantineConquest983();
            resetColor();
            return;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}