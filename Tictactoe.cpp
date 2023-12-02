#include "Tictactoe.h"
#include <iostream>
#include <vector>
#include <limits>
#include "include/rang.hpp"


Tictactoe::Tictactoe(int s) :
    size{s},
    grid_size{ s*s } {
        board.resize(grid_size, 0);
        for(int i = 1; i < (grid_size + 1); i++) board[i-1] = i;
}

std::ostream& operator<<(std::ostream& COUT, const Tictactoe& tic) {
    std::cout << "round " << tic.round << ":\n";
    for(int i = 0; i < tic.grid_size; i++) {
        if(tic.board[i] == -2) {
            COUT << rang::fg::blue << " X" << rang::fg::reset;
        } else if(tic.board[i] == -1) {
            COUT << rang::fg::red << " O" << rang::fg::reset;
        } else {
            std::cout << " " << i+1;
        }
        if(i%tic.size != tic.size-1) COUT << " |";
        if(i%tic.size == tic.size-1 && i != tic.grid_size-1) {
            COUT << "\n" << std::string(4*tic.size-1, '-') << "\n";
        }
    }
    return COUT;
}

void Tictactoe::checkResult() {
    if(round < 2*size-1) return;                               // no need to calculate before 2n-1 rounds
    // check horizontal
    for(int i = 0; i < grid_size; i+=3 ) {
        for(int j = 1; j < size; j++) {
            if(board[i] != board[i+j]) break;
            if(j == size-1) {
                winner = board[i];
                return;
            }
        }
    }
    // check vertical
    for(int i = 0; i < size; i++) {
        for(int j = size; j < grid_size; j += size) {
            if(board[i] != board[i+j]) break;
            if(j == grid_size-size) {
                winner = board[i];
                return;
            }
        }
    }
    // check diagonal
    for(int i = size+1; i < grid_size; i+= size+1) {
        if(board[0] != board[i]) break;
        if(i == grid_size-1) {
            winner = board[0];
            return;
        }
    }
    // check antidiagonal
    for(int i = size-1; i < grid_size; i+= size-1) {
        if(board[size-1] != board[i]) break;
        if(i == grid_size-size) {
            winner = board[grid_size-1];
            return;
        }
    }
    if(round == grid_size+1) winner = -3;
}

void Tictactoe::getInput() {
    int q = round%2==1 ? -2 : -1;                // x starts -> odd rounds are x's turn
    char w = q==-2 ? 'X' : 'O';                  // O = -1, X = -2
    int I;
    std::cout << "\n" << w << "\'s turn: ";
    while(1) {
        std::cin >> I;
        if(std::cin.fail() || I < 1 || I > grid_size) {
            std::cout << "enter an element number in range: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(board[I-1] == -1 || board[I-1] == -2) {
            std::cout << "entered element is full, try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        board[I-1] = q;
        break;
    }
}

void Tictactoe::startGame() {
    while(winner == 0) {
        std::cout << *this;
        getInput();
        checkResult();
        round++;
    }
    std::cout << *this;
    if(winner == -3) {
        std::cout << "\nDraw\n";
        return;
    }
    char w = winner == -1 ? 'O' : 'X';
    std::cout << "\n" << w << " Wins!\n"; 
    if(winner == -1) {
        std::cout << rang::fg::red << "\n" << "O Wins!";
        return;
    }
    std::cout << rang::fg::blue << "\n" << "X Wins!";
}