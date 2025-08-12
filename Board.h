#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>
#include <string>
#include "Piece.h"
#include "Helpers/Position.h"

class Board {
    private:
        std::unique_ptr<Piece> board[8][8];

    public:
        void printBoard() const;
        Piece* getPieceAtIndex(int row, int col) const;
        Piece* getPieceAtPosition(Position position) const;
        void setBoardFromFEN(const std::string&);
        void movePiece(const Position& src, const Position& dest);
        std::string toFENBoard() const;
        void removePieceAtPosition(Position position);
        bool isInsideBoard(int row, int col) const;
        bool isInsideBoard(Position position) const;
        
};
#endif