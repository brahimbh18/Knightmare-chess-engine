#include "MoveValidator.h"
#include "MoveGenerator.h"
#include "Position.h"
#include <vector>

MoveValidator::MoveValidator(const GameState& gameState, Move move): gameState(gameState), move(move) {}

bool MoveValidator::validateMove() {
    Position srcPos = move.source;

    Piece* srcPiece = gameState.getBoard().getPieceAtIndex(srcPos.getRow(), srcPos.getColumn());

    if (srcPiece == nullptr || srcPiece->getColor() != gameState.getCurrentPlayer()) {
        return false;
    }

    MoveGenerator moveGenerator(gameState);
    std::vector<Position> legalMoves = moveGenerator.getLegalMoves(srcPiece, srcPos);
    
    // Check if destination is in legal moves
    for (Position& legalPos : legalMoves) {
        if (legalPos.getRow() == move.destination.getRow() && 
            legalPos.getColumn() == move.destination.getColumn()) {
            return true;
        }
    }
    
    return false;
}

