#include <cstdio>
#include "BoardView.h"

BoardView::BoardView(Board* board, bool silent = false) {
    _board = board;
    _silent = silent;
}

void BoardView::showBoard() const {
    for (int row = 0; row < _board->getRows(); row++) {
        for (int col = 0; col < _board->getColumns(); col++)
            printf("%c", _board->getCell(row, col));
        printf("\n");
    }
}

void BoardView::doGameCycle() const {
    char sign = 'O';
    while (_board->isWin() == Board::CONTINUE) {
        if (!_silent)
            showBoard();

        int r, c;
        while (true) {
            printf("%c move: ", sign);
            
            int read = scanf("%d%d", &r, &c);
            if (read == 2 && (_board->canMove(r, c) || (r == -1 && c == -1)))
                break;
            printf("Bad move!\n");
        }

        if (r == -1 && c == -1)
            break;
        _board->move(r, c, sign);
        sign ^= 'O' ^ 'X';
        printf("\n");
    }

    Board::game_status status = _board->isWin();
    if (status == Board::CONTINUE)
        return;

    showBoard();
    if (status == Board::DRAW)
        printf("Draw.\n");
    if (status == Board::FIRST)
        printf("O wins!\n");
    if (status == Board::SECOND)
        printf("X wins!\n");
}
