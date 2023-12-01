#include "Tictactoe.h"  
#include <iostream>
#include <vector>
#include <limits>

int greet() {
    std::cout << "size(>2) : ";
    int n;
    while(1) {
        std::cin >> n;
        if(!std::cin.fail() && n > 2) break;
        std::cout << "grid size must be greater than 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return n;
}

int main() {
    Tictactoe game1(greet());
    game1.startGame();
}