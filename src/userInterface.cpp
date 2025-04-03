#include "pch.h"  

void startScreen()
{
    SetColor(32);

    Utiles::displayFile("../assets/graphic/startScreen.txt");

    while (std::cin.get() == '\n') {
        mainMenu();
        break;
    }
    resetColor();
}


void mainMenu() {

    //Clear console
    system("cls");
    Utiles::displayFile("../assets/graphic/header.txt");

    char choice;
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
                return;
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

void registerUI() {
    std::string fileName = "../assets/graphic/register.txt";
    std::string fileToSave = "../assets/users.json";

    std::string line;
    std::string email;
    std::string userName;
    std::string password;
    std::string confurmPassword;
    User user;

    std::ifstream file(fileName);

    if (!file.is_open() || Utiles::isFileEmpty(fileName)) {
        std::cerr << "Could not open file for reading!" << std::endl;
        return;
    }

    while (std::getline(file, line)) {

        std::cout << line << std::endl;

        if (line.find("Email") != std::string::npos) 
        {
            std::cin >> email;
            while (!user.checkEmail(email, fileToSave)) {
                std::cin >> email;
            }
        }
        if (line.find("Username") != std::string::npos) 
        {
            std::cin >> userName;
            user.setUserName(userName);
        }
        if (line.find("Password") != std::string::npos) 
        {
            std::cin >> password;
            while (!user.checkPassword(password)) {
                std::cin >> password;
            }
        }
        if (line.find("Confirm Pass") != std::string::npos) 
        {
            std::cin >> confurmPassword;
            while (password != confurmPassword) {
                std::cout << "Wrong password try again\n";
                std::cin >> confurmPassword;
            }
        }
    }
    Utiles::saveToFile(fileToSave, user.saveAsJson());
    
    file.close();

}