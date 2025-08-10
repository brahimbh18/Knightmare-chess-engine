#include "MoveGenerator.h"
#include "MoveValidator.h"
#include "Position.h"
#include <vector>

MoveGenerator::MoveGenerator(const GameState& gameState): gameState(gameState) {}

std::vector<Position> MoveGenerator::getLegalMoves(Piece* piece, Position src) {
    std::string type = piece->getType();
    if (type == "Pawn") {
        return getLegalPawnMoves(piece, src);
    } else if (type == "King") {
        return getLegalKingMoves(piece, src);
    } else if (type == "Queen") {
        return getLegalQueenMoves(piece, src);
    } else if (type == "Rook") {
        return getLegalRookMoves(piece, src);
    } else if (type == "Bishop") {
        return getLegalBishopMoves(piece, src);
    } else if (type == "Knight") {
        return getLegalKnightMoves(piece, src);
    }
    
    // Return empty vector if piece type is not recognized
    return std::vector<Position>();
} 

std::vector<Position> MoveGenerator::getLegalPawnMoves(Piece *piece, Position src) {
    std::vector<Position> legalMoves;
    
    std::string color = piece->getColor();
    int direction = (color == "white") ? 1 : -1;
    int startRow = (color == "white") ? 1 : 6;
    
    Position forward(src.getRow() + direction, src.getColumn());
    if (isInsideBoard(forward) && emptySquare(forward)) {
        legalMoves.push_back(forward);
        
        if (src.getRow() == startRow) {
            Position doubleForward(src.getRow() + 2 * direction, src.getColumn());
            if (isInsideBoard(doubleForward) && emptySquare(doubleForward)) {
                legalMoves.push_back(doubleForward);
            }
        }
    }
    
    // Diagonal captures
    int captureDirs[2] = {-1, 1};
    for (int colDir : captureDirs) {
        Position capture(src.getRow() + direction, src.getColumn() + colDir);
        if (isInsideBoard(capture) && isEnemyPiece(capture)) {
            legalMoves.push_back(capture);
        }
    }
    
    // TODO: Add en passant logic later
    
    return legalMoves;
}
std::vector<Position> MoveGenerator::getLegalKingMoves(Piece *piece, Position src) {
    int directions[8][2] = {{1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}};
    std::vector<Position> moves =  getSingleStepMoves(src, directions);
    std::vector<Position> legalMoves;
    std::string enemyColor = (gameState.getCurrentPlayer() == "white") ? "black" : "white";
    for (Position &position : moves) {
        if (!isSquareAttacked(position, enemyColor)) {
            legalMoves.push_back(position);
        }
    }

    return legalMoves;
}
std::vector<Position> MoveGenerator::getLegalQueenMoves(Piece *piece, Position src) {
    int directions[8][2] = {{1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}};
    return getLinearMoves(src, directions);
}
std::vector<Position> MoveGenerator::getLegalRookMoves(Piece *piece, Position src) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    return getLinearMoves(src, directions);
}
std::vector<Position> MoveGenerator::getLegalBishopMoves(Piece *piece, Position src) {
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    return getLinearMoves(src, directions);
}
std::vector<Position> MoveGenerator::getLegalKnightMoves(Piece *piece, Position src) {
    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    return getSingleStepMoves(src, directions);
}

std::vector<Position> MoveGenerator::getLinearMoves(Position src, int directions[][2]) {
    std::vector<Position> legalMoves;
    
    // For each direction, move as far as possible until blocked
    for (int i = 0; i < sizeof(directions)/sizeof(directions[0]); i++) {
        int row = src.getRow();
        int col = src.getColumn();
        
        // Move in this direction until blocked
        while (true) {
            row += directions[i][0];
            col += directions[i][1];
            
            Position newPos(row, col);
            
            if (!isInsideBoard(newPos)) {
                break; // Out of board
            }
            
            if (emptySquare(newPos)) {
                legalMoves.push_back(newPos);
            } else if (isEnemyPiece(newPos)) {
                legalMoves.push_back(newPos); // Can capture enemy piece
                break; // Can't move further
            } else {
                break; // Blocked by own piece
            }
        }
    }
    
    return legalMoves;
}

std::vector<Position> MoveGenerator::getSingleStepMoves(Position src, int directions[][2]) {
    std::vector<Position> legalMoves;
    
    for (int i = 0; i < sizeof(directions)/sizeof(directions[0]); i++) {
        Position newPosition(src.getRow() + directions[i][0], src.getColumn() + directions[i][1]);
        if (isInsideBoard(newPosition) &&
            (emptySquare(newPosition) ||
            isEnemyPiece(newPosition))
            ) 
        {
            legalMoves.push_back(newPosition);
        }
    }

    return legalMoves;
}


bool MoveGenerator::isSquareAttacked(Position position, std::string enemyColor) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (gameState.getBoard().getPieceAtIndex(i, j)->getColor() == enemyColor) {
                Move move(Position(i, j), position);
                MoveValidator v(gameState, move);
                if (v.validateMove()) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool MoveGenerator::emptySquare(Position position) {
    return gameState.getBoard().getPieceAtIndex(position.getRow(), position.getColumn()) == nullptr;
}

bool MoveGenerator::isEnemyPiece(Position position) {
    Piece* piece = gameState.getBoard().getPieceAtIndex(position.getRow(), position.getColumn());
    return piece != nullptr && piece->getColor() != gameState.getCurrentPlayer();
}

bool MoveGenerator::isInsideBoard(Position position) {
    return position.getRow() < 8 && position.getRow() >= 0 &&
           position.getColumn() < 8 && position.getColumn() >= 0;
}


