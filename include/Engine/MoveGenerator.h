#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "../Helpers/Position.h"
#include "../Helpers/Move.h"
#include "../Engine/GameState.h"
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
        

        bool validRook(const Piece *piece, const std::string& color);
        bool emptySquare(Position position);
        bool isEnemyPiece(Position position);
        bool isInsideBoard(Position position);
    public:
        MoveGenerator(const GameState& gameState);
        
        std::vector<Position> getLegalMoves(Piece* piece, Position src);
};

#endif
