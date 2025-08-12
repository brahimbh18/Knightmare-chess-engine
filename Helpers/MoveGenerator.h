#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "Position.h"
#include "Move.h"
#include "../GameState.h"
#include <vector>

class MoveGenerator {
    private:
        const GameState& gameState;
        
        std::vector<Position> getLegalPawnMoves(Position src);
        std::vector<Position> getLegalKingMoves(Position src);
        std::vector<Position> getLegalQueenMoves(Position src);
        std::vector<Position> getLegalRookMoves(Position src);
        std::vector<Position> getLegalBishopMoves(Position src);
        std::vector<Position> getLegalKnightMoves(Position src);
        
        std::vector<Position> getLinearMoves(Position src, int directions[][2], int directionsCount);
        std::vector<Position> getSingleStepMoves(Position src, int directions[][2], int directionsCount);
        
        bool emptySquare(Position position);
        bool isEnemyPiece(Position position);
        bool isInsideBoard(Position position);
        bool isSquareAttacked(Position position, std::string enemyColor);
        
    public:
        MoveGenerator(const GameState& gameState);
        
        std::vector<Position> getLegalMoves(Piece* piece, Position src);
};

#endif
