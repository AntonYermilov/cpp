#include "Board.h"
#include "BoardView.h"
#include <cstring>

int main(int argc, char** argv) {
    bool silent = false;
    if (argc > 1 && strcmp(argv[1], "silent") == 0)
        silent = true;

    Board* board = new Board();
    BoardView view(board, silent);
    view.doGameCycle();
    delete board;

    return 0;
}
