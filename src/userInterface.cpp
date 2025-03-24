#include "pch.h"  
#include "userInterface.h"
#include <fstream>
#include <iostream>

void mainMenu() {
    std::ifstream f("../../assets/graphic/header.txt");

    if (f.is_open())
        std::cout << f.rdbuf();
}

