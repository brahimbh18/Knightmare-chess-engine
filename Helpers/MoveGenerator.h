#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "Position.h"
#include "Move.h"
#include "../GameState.h"
#include <vector>

class MoveGenerator {
    private:
        const GameState& gameState;
        
        std::vector<Position> getLegalPawnMoves(Piece* piece, Position src);
        std::vector<Position> getLegalKingMoves(Piece* piece, Position src);
        std::vector<Position> getLegalQueenMoves(Piece* piece, Position src);
        std::vector<Position> getLegalRookMoves(Piece* piece, Position src);
        std::vector<Position> getLegalBishopMoves(Piece* piece, Position src);
        std::vector<Position> getLegalKnightMoves(Piece* piece, Position src);
        
        std::vector<Position> getLinearMoves(Position src, int directions[][2]);
        std::vector<Position> getSingleStepMoves(Position src, int directions[][2]);
        
        bool emptySquare(Position position);
        bool isEnemyPiece(Position position);
        bool isInsideBoard(Position position);
        bool isSquareAttacked(Position position, std::string enemyColor);
        
    public:
        MoveGenerator(const GameState& gameState);
        
        std::vector<Position> getLegalMoves(Piece* piece, Position src);
};

#endif
