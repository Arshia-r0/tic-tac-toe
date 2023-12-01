#pragma once
#include <vector>
#include <ostream>


class Tictactoe
{
private:
    int size,
        grid_size,
        round = 1,
        winner = 0;
    std::vector<int> board;

    void getInput();
    void checkResult();
    friend std::ostream& operator<<(std::ostream& COUT, const Tictactoe& tic);

public:

    Tictactoe(int s);
    void startGame();
};