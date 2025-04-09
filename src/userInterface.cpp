#include "pch.h"

//Constructor that initializes User object and displays startScreen function
Ui::Ui()
{
    this->user = new User;
    startScreen();
}

//Destructor that cleans memory 
Ui::~Ui() {
    delete user;
}

//Displays start screen
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

//Displays header.txt and given message
void Ui::displayMenuMsg(std::string msg)
{
    //Clear console
    system("cls");

    Utiles::displayFile("../assets/graphic/header.txt");
    std::cout << msg << std::endl;
}

void Ui::mainMenu() {
    //Clear console
    system("cls");
    Utiles::displayFile("../assets/graphic/header.txt");

    while (true) {

        int choice;
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            registerUi();
            displayMenuMsg("      Hello, " + user->getUserName() + ". Welcome to Storia!\n");
            break;
        case 2:
            logInUi();
            displayMenuMsg("Welcome back, " + user->getUserName() + "\n");
            break;
        case 4:
            timeLineUi();
            break;
        case 3:
            Stages::stagesMenu(*this);
            Utiles::resetColor();
            break;
        case 5:
            displayMenuMsg("You've logged out from: " + user->getUserName() + "\n");
            user->eraseUser();
            break;
        case 6:
            std::cout << "See you next time " << user->getUserName();
            return;
        default:
            displayMenuMsg("You've entered an invalid option. Please try again.");
            break;
        }
    }
}

void Ui::registerUi() {
    const char fileName[] = "../assets/graphic/register.txt";
    const char fileToSave[] = "../assets/users.json";

    std::string line, password, confirmPassword;

    //Clear console
    system("cls");

    std::ifstream file(fileName);

    if (!file.is_open() || Utiles::isFileEmpty(fileName)) {
        std::cout << "Could not open file for reading!" << std::endl;
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
            std::cin >> confirmPassword;
            while (password != confirmPassword) {
                std::cout << "     Wrong password try again";
                std::cin >> confirmPassword;
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
    const char adminKey[] = "932bf3229ff2398c92581d3abac8ae2def2ae338ee65b68e526659dc22f7569e";

    std::cout << "             Enter key: ";

    std::string keyToEnter;
    std::cin >> keyToEnter;

    while (Utiles::sha256FromString(keyToEnter) != adminKey) {
        std::cout << "             Wrong key: ";
        std::cin >> keyToEnter;
    }

    user->setAdmin();
}

void Ui::logInUi() {

    const char fileName[] = "../assets/graphic/login.txt";
    const char fileToSave[] = "../assets/users.json";

    //Clear console
    system("cls");

    std::string line, email, password;

    std::ifstream file(fileName);

    if (!file.is_open() || Utiles::isFileEmpty(fileName)) {
        std::cout << "Could not open file for reading!" << std::endl;
        return;
    }

    while (std::getline(file, line))
    {

        if (line.find("Email") != std::string::npos)
        {
            std::cout << line;
            std::cin >> email;

            while (!user->loadFromFile(fileToSave, Utiles::sha256FromString(email))) {
                std::cin >> email;
            }
        }
        else if (line.find("Password") != std::string::npos)
        {
            std::cout << line;

            std::cin >> password;
            while (user->getPassword() != Utiles::sha256FromString(password)) {
                std::cout << "Wrong password\nPassword: ";
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

void Ui::timeLineUi()
{
    const char fileName[] = "../assets/events.json";
    Timeline line;
    line.loadEventsFromJson(fileName);

    if (user->isUserEmpty())
    {
        std::cout << "Must login or register\n";
        return;
    }

    if (user->getIsAdmin())
    {
        adminTimeLine(fileName, line);
    }

    char choice;
    line.loadDefaultEvents();
    line.displayEvents();

    Utiles::displayFile("../assets/graphic/compareHeader.txt");

    while (true) {
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case'y':
        case'Y':
            line.chooseEventsToCompare(*this);
            break;
        case 's':
        case 'S':
            line.displayEvent();
            break;
        case'm':
        case'M':
            mainMenu();
            break;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}

void Ui::adminTimeLine(const std::string& fileName, Timeline& line)
{
    std::string name = user->getUserName();
    std::string title;
    int year, victims;
    std::string partOfBulgaria, leader, countries, description;

    std::cout << "Welcome back admin:" + user->getUserName() << std::endl;

    char choice;
    while (true) {
        std::cout << "[1]: Add new event" << std::endl;
        std::cout << "[2]: Edit an existing event:" << std::endl;
        std::cout << "Press N to go back" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case '1':
            std::cout << "Title";
            std::getline(std::cin, title);

            std::cout << "Year";
            std::cin >> year;

            std::cout << "Victims";
            std::cin >> victims;
            std::cin.ignore();

            std::cout << "Part of Bulgaria";
            std::getline(std::cin, partOfBulgaria);

            std::cout << "Countries";
            std::getline(std::cin, countries);

            std::cout << "Leader";
            std::getline(std::cin, leader);

            std::cout << "Description";
            std::getline(std::cin, description);

            line.addEvent(title, year, victims, partOfBulgaria, leader, countries, description, name);
            line.saveEventsToJson(fileName);
            break;
        case '2':
            std::cout << "\nyear";
            std::cin >> year;
            line.editEvent(fileName, year);
            line.saveEventsToJson(fileName);
            break;
        case'n':
        case'N':
            return;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
        system("cls");
    }
}