#include <iostream>
#include <fstream>
#include <fmt/core.h>
// #include <fmt/os.h>
#include "Controller/controller.h"

#define pr fmt::print
int main()
{
    int option = 1 ;
    system("clear");
    std::ifstream f("resources/title2.txt");

    if (f.is_open())
        std::cout << "\033[38;5;39m" << f.rdbuf() << "\033[38;5;255m";

    pr("Game Mode\n");
    pr("1. Player vs Player\n");
    pr("2. Player vs Random\n");
    pr("3. Player vs Greedy\n");
    pr("4. Player vs Minimax\n");
    pr("5. Exit\n");

    std::cin >> option;
    if(option!=5)
        Controller controller(option);
    
}
