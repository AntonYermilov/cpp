#pragma once

#include "Board.h"

class BoardView {
public:
    BoardView(Board *board, bool silent);

    void showBoard() const;
    void doGameCycle() const;

private:
    Board* _board;
    bool _silent;
};

