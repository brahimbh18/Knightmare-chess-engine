#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>
#include "Piece.h"
#include "Helpers/Move.h"

class Board {
    private:
        std::unique_ptr<Piece> board[8][8];

    public:
        void printBoard() const;
        Piece * getPieceAtIndex(int row, int col) const;
        void setBoardFromFEN(const std::string&);
};
#endif