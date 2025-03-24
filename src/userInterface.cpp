#include "pch.h"  

void mainMenu() {
    std::ifstream f("../assets/graphic/header.txt");

    if (f.is_open())
        SetColor(31);
        std::cout << f.rdbuf();

}