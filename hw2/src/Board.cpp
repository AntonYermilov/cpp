#include "Board.h"
#include <cstring>
#include <algorithm>

Board::Board() {
    _r = 10;
    _c = 10;
    _field = new char*[10];
    for (int i = 0; i < 10; i++) {
        _field[i] = new char[10];
        memset(_field[i], '.', 10);
    }
}

Board::~Board() {
    for (int i = 0; i < 10; i++)
        delete []_field[i];
    delete []_field;
}

void Board::move(int row, int col, char sign) {
    _field[row][col] = sign;
}

bool Board::canMove(int row, int col) const {
    if (row < 0 || row > 9 || col < 0 || col > 9)
        return false;
    return _field[row][col] == '.';
}

Board::game_status Board::isWin() const {
    bool exists_move = false;
    for (int row = 0; row < 10; row++)
        for (int col = 0; col < 10; col++)
            exists_move |= _field[row][col] == '.';
    if (!exists_move)
        return DRAW;

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            if ((row + 5 <= 10 && inARow(row, col, 1, 0)) ||                    //five in row
                (col + 5 <= 10 && inARow(row, col, 0, 1)) ||                    //five in column
                (std::max(row, col) + 5 <= 10 && inARow(row, col, 1, 1)) ||     //five in main diagonal
                (std::max(row, col) + 5 <= 10 && inARow(row + 4, col, -1, 1)))  //five in secondary diagonal
                    return _field[row][col] == 'O' ? FIRST : SECOND;
        }
    }

    return CONTINUE;
}

bool Board::inARow(int row, int col, int dr, int dc) const { //checks if five equal signs stand together
    if (_field[row][col] == '.')
        return false;
    bool wins = true;
    for (int i = 1; i < 5 && wins; i++)
        wins &= _field[row][col] == _field[row + i * dr][col + i * dc];
    return wins;
}

int Board::getRows() const {
    return _r;
}

int Board::getColumns() const {
    return _c;
}

char Board::getCell(int row, int col) const {
    return _field[row][col];
}
