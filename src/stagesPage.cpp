#include "pch.h"

//Displays stages menu
void Stages::stagesMenu(Ui& ui)
{
    //Clear console
    system("cls");

    char choice;

    Utiles::displayFile("../assets/graphic/stagesHeader.txt");
    Stages stages;

    while (true) {
        std::cout << "Choice: ";
        std::cin >> choice;
        
        //Switch case for every historical stage
        switch (choice) {
        case '1':
            stages.displayStage("../assets/graphic/maps/681-814.txt", "../assets/graphic/stages/681-814.txt");
            stages.choiceSwitch("../assets/graphic/stages/681-814Leaders.txt", ui);
            Utiles::resetColor();
            return;
        case '2':
            stages.displayStage("../assets/graphic/maps/814-983.txt", "../assets/graphic/stages/814-983.txt");
            stages.choiceSwitch("../assets/graphic/stages/814-983Leaders.txt", ui);
            Utiles::resetColor();
            return;
        case '3':
            stages.displayStage("../assets/graphic/maps/983-1018.txt", "../assets/graphic/stages/983-1018.txt");
            stages.choiceSwitch("../assets/graphic/stages/983-1018Leaders.txt", ui);
            Utiles::resetColor();
            return;
        case '4':
            stages.displayStage("../assets/graphic/maps/1019-1206.txt", "../assets/graphic/stages/1019-1206.txt");
            stages.choiceSwitch("../assets/graphic/stages/1019-1206Leaders.txt", ui);
            Utiles::resetColor;
            return;
        case '5':
            stages.displayStage("../assets/graphic/maps/1207-1877.txt", "../assets/graphic/stages/1207-1877.txt");
            stages.choiceSwitch("../assets/graphic/stages/1207-1877Leaders.txt", ui);
            Utiles::resetColor;
            return;
        case '6':
            stages.displayStage("../assets/graphic/maps/1878-1885.txt", "../assets/graphic/stages/1878-1885.txt");
            stages.choiceSwitch("../assets/graphic/stages/1878-1885Leaders.txt", ui);
            Utiles::resetColor;
            return;
        case '7':
            stages.displayStage("../assets/graphic/maps/1886-2025.txt", "../assets/graphic/stages/1886-2025.txt");
            stages.choiceSwitch("../assets/graphic/stages/1886-2025Leaders.txt", ui);
            Utiles::resetColor;
            return;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}

//Display the contents of txt files
void Stages::displayStage(const std::string& mapPath, const std::string& infoPath)
{
    system("cls");
    Utiles::displayFile(mapPath);
    Utiles::displayFile(infoPath);
    std::cout << "Choice: ";
}

//Manage choices and functions
void Stages::choiceSwitch(const std::string& Leaders,Ui& ui)
{
    char choice;

    std::cout << "Choice: ";
    //Loop until valid choice
    while (true) {
        std::cin >> choice;
        switch (choice) {
        case 'Y':
        case 'y':
            system("cls");
            Utiles::displayFile(Leaders);
            char goBack;
            std::cout << "Choice: ";
            while (true) {
                std::cin >> goBack;
                switch (goBack)
                {
                case 'N':
                case 'n':
                    system("cls");
                    stagesMenu(ui);
                    break;
                case 'M':
                case 'm':
                   ui.mainMenu();
                    break;
                default:
                    std::cout << "You've entered an invalid option. Please try again." << std::endl;
                    break;
                }
            }
        case 'N':
        case 'n':
            stagesMenu(ui);
            break;
        case 'M':
        case 'm':
            system("cls");
            ui.mainMenu();
            break;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}
