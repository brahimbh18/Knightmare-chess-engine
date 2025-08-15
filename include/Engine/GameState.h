#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <sstream>
#include "Board.h"
#include "../Piece.h"
#include "../Helpers/Position.h"
#include "../Helpers/Move.h"


class GameState {
    private:
        Board board;
        std::string currentPlayer; //black or white
        Position *enpassantTarget;
        int castlingRights;
        int halfMoveClock;
        int fullMoveNumber;

        void setCurrentPlayer();
        void setCurrentBoard();
        
        
        std::vector<std::string> splitFEN(const std::string&);
        std::string castlingToFEN() const;
        bool isSquareAttackedByPawn(const Position sq, const std::string attacker) const;
        bool isSquareAttackedByKnight(const Position sq, const std::string attacker) const;
        bool isSquareAttackedByRay(const Position sq, const std::string attacker) const;
        bool isSquareAttackedByKing(const Position sq, const std::string attacker) const;
    public:
        GameState(std::string);
        enum CastlingRights {
            WHITE_KINGSIDE  = 1 << 0,  // 0001  → 1
            WHITE_QUEENSIDE = 1 << 1,  // 0010  → 2
            BLACK_KINGSIDE  = 1 << 2,  // 0100  → 4
            BLACK_QUEENSIDE = 1 << 3   // 1000  → 8
        };
        const Board& getBoard() const;
        bool validateMove(Move) const;
        const std::string getCurrentPlayer() const;
        void applyMove(const Move& move);
        std::string toFEN() const;
        Position* getEnPassant() const;
        Piece* getPieceAtPosition(Position position) const;
        void removePieceAtPosition(Position position);
        bool isSquareAttacked(const Position sq, const std::string attacker) const;
        int getCastlingRights() const;
        bool emptySquare(Position position) const;
};
#endif