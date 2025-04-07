#include "pch.h"

Ui::Ui()
{
    startScreen();
    this->user = new User;
}

Ui::~Ui() {
    delete user;
}

void Ui::startScreen()
{
    Utiles::SetColor(32);

    Utiles::displayFile("../assets/graphic/startScreen.txt");

    while (std::cin.get() == '\n') {
        mainMenu();
        break;
    }
    Utiles::resetColor();
}

void Ui::mainMenu() {

    //Clear console
    system("cls");
    Utiles::displayFile("../assets/graphic/header.txt");

    char choice;

    //Loop until valid choice
    while (true) {
        std::cout << "Choice: ";
        std::cin >> choice;

            switch (choice) {
            case'1':
                registerUi();
                std::cout << "Registration successful\n";
                break;
            case'2':
                logInUi();
                std::cout << "Welcome back\n";
                break;
            case'4':
                timeLIneUi();
                break;
            case '3':
                Stages::stagesMenu(*this);
                Utiles::resetColor();
                break;
            case '5':
                user->eraseUser();
                return;
            default:
                std::cout << "You've entered an invalid option. Please try again." << std::endl;
                break;
            }
    }
}

void Ui::registerUi() {
    const char fileName[] = "../assets/graphic/register.txt";
    const char fileToSave[] = "../assets/users.json";

    std::string line;
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

            std::string email;
            std::cin >> email;
            while (!user->checkEmail(email, fileToSave)) {
                std::cin >> email;
            }
        }
        else if (line.find("Username") != std::string::npos) 
        {
            std::cout << line;

            std::string userName;
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
        else if (line.find("Confirm Password") != std::string::npos)
        {
            std::cout << line;
            std::cin >> confurmPassword;
            while (password != confurmPassword) {
                std::cout << "     Wrong password try again";
                std::cin >> confurmPassword;
            }
        }
        else if (line.find("Registering as Admin? ") != std::string::npos)
        {
            char choise;
            std::cout << line;
            std::cin >> choise;

            if (choise == 'y' || choise == 'Y')
            {
                registerAsAdmin();
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

void Ui::registerAsAdmin()
{
    const char adminKey[] = "Storia22";

    std::cout << "     Enter key: ";

    std::string keyToEnter;
    std::cin >> keyToEnter;

    while (keyToEnter != adminKey) {
        std::cout << "     Wrong key: ";
        std::cin >> keyToEnter;
    }

    user->setAdmin();
}

void Ui::logInUi() {


    const char fileName[] = "../assets/graphic/login.txt";
    const char fileToSave[] = "../assets/users.json";

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

void Ui::timeLIneUi() 
{
    char choice;
    if (!user->isUserEmpty())
    {
        const char fileName[] = "../assets/events.json";
        Timeline line;
        line.loadDefaultEvents();
        line.loadEventsFromJson(fileName);
        line.displayEvents();

        std::cout << "Would you like to compare some of these events?" << std::endl;
        std::cout << "Yes[Y]" << std::endl;
        std::cout << "No[N]" << std::endl;
        std::cout << "Main menu[M]" << std::endl;

        while (true) {
            std::cout << "Choice: ";
            std::cin.ignore();
            std::cin >> choice;

            switch (choice) {
            case'Y':
            case'y':
                line.chooseEventsToCompare();
                break;
            case 'N':
            case 'n':
                break;
            case'M':
            case'm':
                mainMenu();
                break;
            default:
                std::cout << "You've entered an invalid option. Please try again." << std::endl;
                break;
            }
        }
    }
    else
    {
        std::cout << "Must login or register\n";
        return;
    }
}