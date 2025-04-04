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


