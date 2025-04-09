#include "pch.h"

//Constructor that creates empty timeline
Timeline::Timeline() {
    head = nullptr;
}

//Add default events to timelike
void Timeline::loadDefaultEvents() {
    addEvent("Foundation of Bulgaria", 681, 0, "Balkans", "Khan Asparuh", "Bulgaria", "Establishment of the First Bulgarian State", "Default");
    addEvent("Christianization of Bulgaria", 864, 0, "Bulgaria", "Prince Boris I", "Bulgaria", "Official adoption of Christianity", "Default");
    addEvent("Beginning of the Golden Age", 886, 0, "Bulgaria", "Clement of Ohrid", "Bulgaria", "Spread of Slavic literacy", "Default");
}

//Add new event to timeline
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

//Edit an event
void Timeline::editEvent(const std::string& fileName, int year) {
    Event* current = head;
    while (current && current->year != year) {
        current = current->next;
    }
    if (!current || current->username == "Default") {
        std::cout << "The event cannot be edited!\n";
        return;
    }
    std::cout << "Editing event: " << current->title << "\n";
    std::cout << "New title: "; std::cin.ignore(); std::getline(std::cin, current->title);
    std::cout << "New year: "; std::cin >> current->year;
    std::cout << "Number of victims: "; std::cin >> current->victims;
    std::cin.ignore();
    std::cout << "Region: "; std::getline(std::cin, current->partOfBulgaria);
    std::cout << "Leader: "; std::getline(std::cin, current->leader);
    std::cout << "Countries involved: "; std::getline(std::cin, current->countries);
    std::cout << "Description: "; std::getline(std::cin, current->description);
}

//Saves the events to JSON format
void Timeline::saveEventsToJson(const std::string& fileName)
{
    Event* current = this->head;
    nlohmann::json existingData;

    if (!existingData.is_array()) {
        existingData = nlohmann::json::array();
    }

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

        existingData.push_back(data);
        current = current->next;
    }

    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << existingData.dump(4);
        outFile.close();
    }
    else {
        std::cout << "Could not open file for writing!" << std::endl;
    }
}

//Loads data from JSON format
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

//Display the header for events
void Timeline::displayEvents() {
    system("cls");
    Utiles::displayFile("../assets/graphic/timelineHeader.txt");

    Event* current = head;
    std::cout << "\n|\n|\n|\n";
    while (current) {
        std::cout << "[*] " << current->year << " - " << current->title << "\n|\n|\n";
        current = current->next;
    }
}

//Displays events
void Timeline::displayEvent() {

    std::string title;
    std::cout << "Title";
    std::cin.ignore();
    std::getline(std::cin, title);


    Event* current = head;
    while (current) {
        if (current->title == title)
        {
            std::cout << "Title: " << current->title << std::endl;
            std::cout << "Year: " << current->year << std::endl;
            std::cout << "Number of victims: " << current->victims << std::endl;
            std::cout << "Leader: " << current->leader << std::endl;
            std::cout << "Countries involved: " << current->countries << std::endl;
            std::cout << "Description: " << current->description << std::endl;
            break;
        }
        current = current->next;
    }
}

//Delete event from timeline
void Timeline::deleteEvent(const std::string& fileName, int yearToDelete) {
    Event* current = this->head;
    Event* prev = nullptr;

    while (current != nullptr) {
        if (current->year == yearToDelete) {
            if (prev == nullptr) {
                // Delete head
                this->head = current->next;
            }
            else {
                prev->next = current->next;
            }

            // Delete only first matching event
            delete current;
            break; 
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
        std::cout << "Could not open file for rewriting." << std::endl;
    }
}

//Compare two events
void Timeline::compareEvents(Event event1, Event event2,Ui& ui)
{
    system("cls");
    Utiles::displayFile("../assets/graphic/eventsComparisonHeader.txt");

    std::cout << std::endl << std::endl;
    std::cout << std::left << std::setw(event1.title.size() + 10) << event1.title << event2.title << std::endl << std::endl;
    std::cout << "Started: " << std::left << std::setw(std::to_string(event1.year).size() + 5) << event1.year << event2.year << std::endl << std::endl;
    std::cout << "Victims: " << std::left << std::setw(std::to_string(event1.victims).size() + 5) << event1.victims << event2.victims << std::endl << std::endl;
    std::cout << "Part of Bulgaria: " << std::left << std::setw(event1.partOfBulgaria.size() + 5) << event1.partOfBulgaria << event2.partOfBulgaria << std::endl << std::endl;
    std::cout << "Leader: " << std::left << std::setw(event1.leader.size() + 5) << event1.leader << event2.leader << std::endl << std::endl;
    std::cout << "Countries it affected: " << std::left << std::setw(event1.countries.size() + 5) << event1.countries << event2.countries << std::endl << std::endl;

    std::cout << "Conclusion: " << std::endl;

    if (event1.year < event2.year) std::cout << event1.title << " happened before " << event2.title << ". ";
    else if (event1.year > event2.year) std::cout << event1.title << " happened after " << event2.title << ". ";
    else std::cout << "Both events started in " << event1.year << ". ";

    if (event1.victims < event2.victims) std::cout << event1.title << " had less victims than " << event2.title;
    else if (event1.year > event2.year) std::cout << event1.title << " had more victims than " << event2.title;
    else std::cout << "Both events had " << event1.victims << " victims" << std::endl;

    if (event1.partOfBulgaria != event2.partOfBulgaria) std::cout << event1.title << " happened in " << event1.partOfBulgaria << " whereas " << event2.title << " happened in " << event2.partOfBulgaria << std::endl;
    else std::cout << "Both events happened in " << event1.partOfBulgaria << ". ";

    if (event1.leader != event2.leader) std::cout << event1.title << " happened under the rule of " << event1.leader << " and " << event2.title << "happened under the rule of " << event2.leader << std::endl;
    else std::cout << "Both events happened under the rule of " << event1.leader << std::endl;

    if (event1.countries != event2.countries) std::cout << event1.title << " affected " << event1.countries << " while " << event2.title << " affected " << event2.countries << std::endl;
    else std::cout << "Both events affected " << event1.countries << std::endl << std::endl;

    std::cout << "Where to next?" << std::endl;
    std::cout << "[T] Timeline" << std::endl;
    std::cout << "[S] Stay" << std::endl;
    std::cout << "[M] Main Menu" << std::endl;

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

//Choose from events in timeline to compare
void Timeline::chooseEventsToCompare(Ui& ui)
{
    bool event1Found = false;
    bool event2Found = false;
    Event event1, event2;
    std::string event1Title, event2Title;

    std::cin.ignore();
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