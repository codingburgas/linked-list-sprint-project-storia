#pragma once
#include "pch.h"

#include <iostream>
#include <fstream>
#include <std::string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

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
    void editEvent(int year);
    void saveEventsToJson();
    void loadEventsFromJson();
    void displayEvents();
    void deleteEvent(int year);
private:
    Event* head;
};

