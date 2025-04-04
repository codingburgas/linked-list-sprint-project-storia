#include "pch.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

struct Event {
    std::string title;
    int year;
    int victims;
    std::string partOfBulgaria;
    std::string leader;
    std::string countries;
    std::string description;
    std::string username;
    Event* next;
};

class Timeline {
private:
    Event* head;
public:
    Timeline() {
        head = nullptr;
        loadDefaultEvents();
        loadEventsFromJson();
    }

    void loadDefaultEvents() {
        addEvent("Foundation of Bulgaria", 681, 0, "Balkans", "Khan Asparuh", "Bulgaria", "Establishment of the First Bulgarian State", "Default");
        addEvent("Christianization of Bulgaria", 864, 0, "Bulgaria", "Prince Boris I", "Bulgaria", "Official adoption of Christianity", "Default");
        addEvent("Beginning of the Golden Age", 886, 0, "Bulgaria", "Clement of Ohrid", "Bulgaria", "Spread of Slavic literacy", "Default");
    }

    void addEvent(std::string title, int year, int victims, std::string partOfBulgaria, std::string leader, std::string countries, std::string description, std::string username) {
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
        saveEventsToJson();
    }

    void editEvent(int year) {
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
        saveEventsToJson();
    }

    void saveEventsToJson();

    void loadEventsFromJson();

    void displayEvents() {
        system("cls");
        Event* current = head;
        cout << "\n|\n|\n|\n";
        while (current) {
            cout << " * " << current->year << " - " << current->title << "\n|\n|\n|\n|\n|\n";
            current = current->next;
        }
    }

    void deleteEvent(int year) {
        if (!head) return;
        if (head->year == year && head->username != "Default") {
            Event* temp = head;
            head = head->next;
            delete temp;
            saveEventsToJson();
            return;
        }
        Event* current = head;
        while (current->next && current->next->year != year) {
            current = current->next;
        }
        if (current->next && current->next->username != "Default") {
            Event* temp = current->next;
            current->next = current->next->next;
            delete temp;
            saveEventsToJson();
        }
    }
};
