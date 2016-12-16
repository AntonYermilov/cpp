#pragma once

class Board {
public:    
    Board();
    ~Board();

    enum game_status {
        CONTINUE,
        DRAW    ,
        FIRST   ,
        SECOND
    };

    void move(int row, int col, char sign);
    bool canMove(int row, int col) const;
    game_status isWin() const;

    char firstSign() const;
    char secondSign() const;

    int getRows() const;
    int getColumns() const;
    char getCell(int row, int col) const;

private:
    Board(const Board &other);
    Board& operator=(const Board &other);

    bool inARow(int row, int col, int dr, int dc) const;

    int _r;
    int _c;
    char** _field;
};
