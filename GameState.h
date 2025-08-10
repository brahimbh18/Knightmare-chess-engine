#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <sstream>
#include "Board.h"
#include "Piece.h"
#include "Helpers/Position.h"
#include "Helpers/Move.h"


class GameState {
    private:
        Board board;
        std::string currentPlayer; //black or white
        std::unique_ptr<Position> enpassantTarget;
        int castlingRights;
        int halfMoveClock;
        int fullMoveNumber;

        void setCurrentPlayer();
        void setCurrentBoard();
        enum CastlingRights {
            WHITE_KINGSIDE  = 1 << 0,  // 0001  → 1
            WHITE_QUEENSIDE = 1 << 1,  // 0010  → 2
            BLACK_KINGSIDE  = 1 << 2,  // 0100  → 4
            BLACK_QUEENSIDE = 1 << 3   // 1000  → 8
        };
        
        std::vector<std::string> splitFEN(const std::string&);
    public:
        GameState(std::string);
        const Board& getBoard() const;
        bool validateMove(Move) const;
        const std::string getCurrentPlayer() const;
};
#endif