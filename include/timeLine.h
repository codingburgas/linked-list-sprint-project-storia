#pragma once
#include "pch.h"

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
public:
    Timeline();

    void loadDefaultEvents();
    void loadEventsFromJson(const std::string& fileName);

    void addEvent(std::string title, int year, int victims, std::string partOfBulgaria, std::string leader, std::string countries, std::string description, std::string username);
    void saveEventsToJson(const std::string& fileName);

    void editEvent(const std::string& fileName, int year);
    void deleteEvent(const std::string& fileName, int year);

    void displayEvents();
    void displayEvent();
    void chooseEventsToCompare(Ui& ui);
private:
    void compareEvents(Event event1, Event event2, Ui& ui);

    Event* head;
};

