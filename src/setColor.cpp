#include "pch.h"

void SetColor(int textColor)
{
    std::cout << "\033[" << textColor << "m";
}