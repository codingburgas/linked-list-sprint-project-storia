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
    void addEvent(std::string title, int year, int victims, std::string partOfBulgaria, std::string leader, std::string countries, std::string description, std::string username);
    void editEvent(const std::string& fileName, int year);
    void saveEventsToJson(const std::string& fileName);
    void loadEventsFromJson(const std::string& fileName);
    void displayEvents();
    void deleteEvent(const std::string& fileName, int year);

    void compareEvents(Event event1, Event event2);
private:
    Event* head;
};

