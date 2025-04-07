#include "pch.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

Timeline::Timeline() {
    head = nullptr;
}

void Timeline::loadDefaultEvents() {
    addEvent("Foundation of Bulgaria", 681, 0, "Balkans", "Khan Asparuh", "Bulgaria", "Establishment of the First Bulgarian State", "Default");
    addEvent("Christianization of Bulgaria", 864, 0, "Bulgaria", "Prince Boris I", "Bulgaria", "Official adoption of Christianity", "Default");
    addEvent("Beginning of the Golden Age", 886, 0, "Bulgaria", "Clement of Ohrid", "Bulgaria", "Spread of Slavic literacy", "Default");
}

void Timeline::addEvent(std::string title, int year, int victims, std::string partOfBulgaria, std::string leader, std::string countries, std::string description, std::string username)
{
    Event* newEvent = new Event{ title, year, victims, partOfBulgaria, leader, countries, description, username, nullptr };

    if (!head || year < head->year) {
        newEvent->next = head;
        head = newEvent;
    }
    else {
        Event* current = head;
        while (current->next && current->next->year < year) {
            current = current->next;
        }
        newEvent->next = current->next;
        current->next = newEvent;
    }
}

void Timeline::editEvent(const std::string& fileName, int year) {
    Event* current = head;
    while (current && current->year != year) {
        current = current->next;
    }
    if (!current || current->username == "Default") {
        cout << "The event cannot be edited!\n";
        return;
    }
    cout << "Editing event: " << current->title << "\n";
    cout << "New title: "; cin.ignore(); getline(cin, current->title);
    cout << "New year: "; cin >> current->year;
    cout << "Number of victims: "; cin >> current->victims;
    cin.ignore();
    cout << "Region: "; getline(cin, current->partOfBulgaria);
    cout << "Leader: "; getline(cin, current->leader);
    cout << "Countries involved: "; getline(cin, current->countries);
    cout << "Description: "; getline(cin, current->description);
}

void Timeline::saveEventsToJson(const std::string& fileName)
{
    Event* current = this->head;

    while (current != nullptr) {
        nlohmann::json data;
        data["title"] = current->title;
        data["year"] = current->year;
        data["victims"] = current->victims;
        data["partOfBulgaria"] = current->partOfBulgaria;
        data["leader"] = current->leader;
        data["countries"] = current->countries;
        data["description"] = current->description;
        data["username"] = current->username;

        Utiles::saveToFile(fileName, data);
        current = current->next;
    }
}

void Timeline::loadEventsFromJson(const std::string& fileName)
{
    nlohmann::json data;
    if (!Utiles::isFileEmpty(fileName)) {
        data = Utiles::loadFile(fileName);
    }

    for (const auto& item : data) {
        addEvent(
            item["title"],
            item["year"],
            item["victims"],
            item["partOfBulgaria"],
            item["leader"],
            item["countries"],
            item["description"],
            item["username"]
        );
    }
}

void Timeline::displayEvents() {
    system("cls");
    Event* current = head;
    cout << "\n|\n|\n|\n";
    while (current) {
        cout << " * " << current->year << " - " << current->title << "\n|\n|\n|\n|\n|\n";
        current = current->next;
    }
}

void Timeline::deleteEvent(const std::string& fileName, int yearToDelete) {
    Event* current = this->head;
    Event* prev = nullptr;

    while (current != nullptr) {
        if (current->year == yearToDelete) {
            if (prev == nullptr) {
                // Deleting head
                this->head = current->next;
            }
            else {
                prev->next = current->next;
            }

            delete current;
            break; // Delete only first matching event
        }

        prev = current;
        current = current->next;
    }

    nlohmann::json allData = nlohmann::json::array();
    current = this->head;

    while (current != nullptr) {
        nlohmann::json data;
        data["title"] = current->title;
        data["year"] = current->year;
        data["victims"] = current->victims;
        data["partOfBulgaria"] = current->partOfBulgaria;
        data["leader"] = current->leader;
        data["countries"] = current->countries;
        data["description"] = current->description;
        data["username"] = current->username;

        allData.push_back(data);
        current = current->next;
    }

    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << allData.dump(4);
        outFile.close();
        std::cout << "Event deleted and file updated: " << fileName << std::endl;
    }
    else {
        std::cerr << "Could not open file for rewriting." << std::endl;
    }
}

void Timeline::compareEvents(Event event1, Event event2,Ui& ui)
{
    system("cls");
    cout << event1.title << event2.title << endl << endl;
    cout << "Started: " << event1.year << event2.year << endl << endl;
    cout << "Victims: " << event1.victims << event2.victims << endl << endl;
    cout << "Part of Bulgaria: " << event1.partOfBulgaria << event2.partOfBulgaria << endl << endl;
    cout << "Leader: " << event1.leader << event2.leader << endl << endl;
    cout << "Countries it affected: " << event1.countries << event2.countries << endl << endl;

    cout << "Conclusion: " << endl;
    if (event1.year < event2.year) cout << event1.title << " happened before " << event2.title << ". ";
    else if (event1.year > event2.year) cout << event1.title << " happened after " << event2.title << ". ";
    else cout << "Both events started in " << event1.year << ". ";

    if (event1.victims < event2.victims) cout << event1.title << " had less victims than " << event2.title;
    else if (event1.year > event2.year) cout << event1.title << " had more victims than " << event2.title;
    else cout << "Both events had " << event1.victims << " victims" << endl;

    if (event1.partOfBulgaria != event2.partOfBulgaria) cout << event1.title << " happened in " << event1.partOfBulgaria << " whereas " << event2.title << " happened in " << event2.partOfBulgaria << endl;
    else cout << "Both events happened in " << event1.partOfBulgaria << ". ";

    if (event1.leader != event2.leader) cout << event1.title << " happened under the rule of " << event1.leader << " and " << event2.title << "happened under the rule of " << event2.leader << endl;
    else cout << "Both events happened under the rule of " << event1.leader << endl;

    if (event1.countries != event2.countries) cout << event1.title << " affected " << event1.countries << " while " << event2.title << " affected " << event2.countries << endl;
    else cout << "Both events affected " << event1.countries << endl << endl;

    std::cout << "Where to next?" << std::endl;
    std::cout << "Timeline[T]" << std::endl;
    std::cout << "Stay[S]" << std::endl;
    std::cout << "Main menu[M]" << std::endl;

    char choice;
    while (true) {
        std::cout << "Choice: ";
        std::cin.ignore();
        std::cin >> choice;

        switch (choice) {
        case'T':
        case't':
            ui.timeLineUi();
            break;
        case 'S':
        case 's':
            break;
        case'M':
        case'm':
            ui.mainMenu();
            break;
        default:
            std::cout << "You've entered an invalid option. Please try again." << std::endl;
            break;
        }
    }
}

void Timeline::chooseEventsToCompare(Ui& ui)
{
    bool event1Found = false;
    bool event2Found = false;
    Event event1, event2;
    std::string event1Title, event2Title;

    cin.ignore();
    std::cout << "Enter title of first event to compare: ";
    std::getline(std::cin, event1Title);
    std::cout << "Enter title of second event to compare: ";
    std::getline(std::cin, event2Title);

    Event* current = head;

    while (current && (!event1Found || !event2Found))
    {
        if (current->title == event1Title)
        {
            event1 = *current;
            event1Found = true;
        }
        else if (current->title == event2Title)
        {
            event2 = *current;
            event2Found = true;
        }

        current = current->next;
    }

    if (!event1Found || !event2Found)
    {
        std::cout << "One or both events not found!" << std::endl;
        return;
    }

    compareEvents(event1, event2,ui);
}