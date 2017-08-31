#include "Board.h"
#include <cstring>
#include <algorithm>

Board::Board() {
    for (int i = 0; i < _r; i++)
        memset(_field[i], '.', _c);
}

void Board::move(int row, int col, char sign) {
    _field[row][col] = sign;
}

bool Board::canMove(int row, int col) const {
    if (row < 0 || row >= _r || col < 0 || col >= _c)
        return false;
    return _field[row][col] == '.';
}

Board::game_status Board::isWin() const {
    for (int row = 0; row < _r; row++) {
        for (int col = 0; col < _c; col++) {
            if ((row + 5 <= _r && inARow(row, col, 1, 0)) ||                      //five in row
                (col + 5 <= _c && inARow(row, col, 0, 1)) ||                      //five in column
                (row + 5 <= _r && col + 5 <= _c && inARow(row, col, 1, 1)) ||     //five in main diagonal
                (row - 4 >=  0 && col + 5 <= _c && inARow(row, col, -1, 1)))  //five in secondary diagonal
                    return _field[row][col] == 'O' ? FIRST : SECOND;
        }
    }

    bool exists_move = false;
    for (int row = 0; row < _r; row++)
        for (int col = 0; col < _c; col++)
            exists_move |= _field[row][col] == '.';
    if (!exists_move)
        return DRAW;

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
