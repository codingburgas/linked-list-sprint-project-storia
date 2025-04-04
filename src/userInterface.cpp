#include "pch.h"

UI::UI()
{
    user = new User;
    startScreen();
}

UI::~UI() {
    delete user;
}


void UI::startScreen()
{
    SetColor(32);

    Utiles::displayFile("../assets/graphic/startScreen.txt");

    while (std::cin.get() == '\n') {
        mainMenu();
        break;
    }
    resetColor();
}


void UI::mainMenu() {

    //Clear console
    system("cls");
    Utiles::displayFile("../assets/graphic/header.txt");

    char choice;
    User* user = new User;
    std::cout << "Choice: ";

    //Loop until valid choice
    while (true) {
        std::cin >> choice;
            switch (choice) {
            case'1':
                registerUI();
                mainMenu();
                return;
            case'2':
                logInUi();
                mainMenu();
                return;
            case '3':
                stagesMenu();
                resetColor();
                return;
            case '5':
                user->eraseUser();
                return;
            default:
                std::cout << "You've entered an invalid option. Please try again." << std::endl;
                break;
            }
    }
}

void UI::registerUI() {
    std::string fileName = "../assets/graphic/register.txt";
    std::string fileToSave = "../assets/users.json";

    std::string line;
    std::string email;
    std::string userName;
    std::string password;
    std::string confurmPassword;

    std::ifstream file(fileName);

    if (!file.is_open() || Utiles::isFileEmpty(fileName)) {
        std::cerr << "Could not open file for reading!" << std::endl;
        return;
    }

    while (std::getline(file, line)) {

        if (line.find("Email") != std::string::npos) 
        {
            std::cout << line;

            std::cin >> email;
            while (!user->checkEmail(email, fileToSave)) {
                std::cin >> email;
            }
        }
        else if (line.find("Username") != std::string::npos) 
        {
            std::cout << line;

            std::cin >> userName;
            user->setUserName(userName);
        }
        else if (line.find("Password") != std::string::npos)
        {
            std::cout << line;

            std::cin >> password;
            while (!user->checkPassword(password)) {
                std::cin >> password;
            }
        }
        else if (line.find("Confirm Pass") != std::string::npos)
        {
            std::cout << line;
            std::cin >> confurmPassword;
            while (password != confurmPassword) {
                std::cout << "Wrong password try again\n";
                std::cin >> confurmPassword;
            }
        }
        else 
        {
            std::cout << line << std::endl;
        }
        
    }
    Utiles::saveToFile(fileToSave, user->saveAsJson());
    
    file.close();
}

void UI::logInUi() {


    std::string fileName = "../assets/graphic/login.txt";
    std::string fileToSave = "../assets/users.json";

    std::string line;
    std::string email;
    std::string password;

    std::ifstream file(fileName);

    if (!file.is_open() || Utiles::isFileEmpty(fileName)) {
        std::cerr << "Could not open file for reading!" << std::endl;
        return;
    }

    while (std::getline(file, line)) 
    {

        if (line.find("Email") != std::string::npos)
        {
            std::cout << line;

            std::cin >> email;
            while (!user->loadFromFile(fileToSave,email)) {
                std::cin >> email;
            }
        }
        else if (line.find("Password") != std::string::npos)
        {
            std::cout << line;

            std::cin >> password;
            while (user->getPassword() != password) {
                std::cout << "Wrong password\n";
                std::cin >> password;
            }
        }
        else
        {
            std::cout << line << std::endl;
        }
    }
    user->displayUser();

    file.close();
}