#include "../../include/Engine/GameState.h"
#include "../../include/Helpers/Position.h"
#include "../../include/Piece.h"
#include <cctype>
#include <vector>

GameState::GameState(std::string fen) {
    std::vector<std::string> parts = splitFEN(fen);
    if (parts.size() != 6) {
        std::cerr << "Invalid FEN string\n";
        return;
    }
    board.setBoardFromFEN(parts[0]);


    currentPlayer = parts[1] == "w" ? "white" : "black";
    
    castlingRights = 0;
    std::string castlingStr = parts[2];
    
    enpassantTarget = parts[3] == "-" ? nullptr : new Position(parts[3]);

    if (castlingStr.find('K') != std::string::npos)
        castlingRights |= WHITE_KINGSIDE;
    if (castlingStr.find('Q') != std::string::npos)
        castlingRights |= WHITE_QUEENSIDE;
    if (castlingStr.find('k') != std::string::npos)
        castlingRights |= BLACK_KINGSIDE;
    if (castlingStr.find('q') != std::string::npos)
        castlingRights |= BLACK_QUEENSIDE;

    halfMoveClock = std::stoi(parts[4]);
    fullMoveNumber = std::stoi(parts[5]);

}

std::vector<std::string> GameState::splitFEN(const std::string &fen) {
    std::vector<std::string> parts;
    std::istringstream ss(fen);
    std::string segment;

    while (ss >> segment) {
        parts.push_back(segment);
    }
    return parts;
}

const Board& GameState::getBoard() const {
    return board;
}

const std::string GameState::getCurrentPlayer() const {
    return currentPlayer;
}

void GameState::applyMove(const Move& move) {
    Piece* piece  = getPieceAtPosition(move.source);
    Piece* target = getPieceAtPosition(move.destination);

    bool pawnMove = false;
    bool capture  = (target != nullptr);
    bool newEp = false;

    if (piece->getType() == "King") {
        if (currentPlayer == "white")
            castlingRights &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);
        else
            castlingRights &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);

        int dc = std::abs(move.source.getColumn() - move.destination.getColumn());
        if (dc == 2) {
            int row = move.source.getRow();
            if (move.destination.getColumn() == 6) {
                board.movePiece(Position(row, 7), Position(row, 5));
            } else if (move.destination.getColumn() == 2) {
                board.movePiece(Position(row, 0), Position(row, 3));
            }
        }
    }

    if (piece->getType() == "Rook") {
        if (currentPlayer == "white") {
            if (move.source.getRow() == 0 && move.source.getColumn() == 0)
                castlingRights &= ~WHITE_QUEENSIDE;
            if (move.source.getRow() == 0 && move.source.getColumn() == 7)
                castlingRights &= ~WHITE_KINGSIDE;
        } else {
            if (move.source.getRow() == 7 && move.source.getColumn() == 0)
                castlingRights &= ~BLACK_QUEENSIDE;
            if (move.source.getRow() == 7 && move.source.getColumn() == 7)
                castlingRights &= ~BLACK_KINGSIDE;
        }
    }

    if (target && target->getType() == "Rook") {
        if (move.destination.getRow() == 0 && move.destination.getColumn() == 0)
            castlingRights &= ~WHITE_QUEENSIDE;
        if (move.destination.getRow() == 0 && move.destination.getColumn() == 7)
            castlingRights &= ~WHITE_KINGSIDE;
        if (move.destination.getRow() == 7 && move.destination.getColumn() == 0)
            castlingRights &= ~BLACK_QUEENSIDE;
        if (move.destination.getRow() == 7 && move.destination.getColumn() == 7)
            castlingRights &= ~BLACK_KINGSIDE;
    }

    if (piece->getType() == "Pawn") {
        pawnMove = true;

        bool diagonal = (move.destination.getColumn() != move.source.getColumn());
        if (diagonal && !target && enpassantTarget && Position::equals(move.destination, *enpassantTarget)) {
            Position captured(move.source.getRow(), move.destination.getColumn());
            removePieceAtPosition(captured);
            capture = true;
        }

        int dr = move.destination.getRow() - move.source.getRow();
        if (std::abs(dr) == 2) {
            int midRow = (move.source.getRow() + move.destination.getRow()) / 2;
            enpassantTarget = new Position(midRow, move.source.getColumn());
            newEp = true;
        }
    }

    board.movePiece(move.source, move.destination);

    enpassantTarget = newEp ? nullptr : enpassantTarget;
    halfMoveClock = (pawnMove || capture) ? 0 : (halfMoveClock + 1);

    if (currentPlayer == "black")
        fullMoveNumber++;

    currentPlayer = (currentPlayer == "white") ? "black" : "white";
}


std::string GameState::castlingToFEN() const {
    std::string s;
    if (castlingRights & WHITE_KINGSIDE)  s += 'K';
    if (castlingRights & WHITE_QUEENSIDE) s += 'Q';
    if (castlingRights & BLACK_KINGSIDE)  s += 'k';
    if (castlingRights & BLACK_QUEENSIDE) s += 'q';
    if (s.empty()) s = "-";
    return s;
}


std::string GameState::toFEN() const {
    std::string boardFEN = board.toFENBoard();
    std::string side = (currentPlayer == "white") ? "w" : "b";
    std::string castling = castlingToFEN();
    std::string ep = enpassantTarget ? enpassantTarget->getAlgebraic() : "-";
    return boardFEN + " " + side + " " + castling + " " + ep + " " + std::to_string(halfMoveClock) + " " + std::to_string(fullMoveNumber);
}

Position* GameState::getEnPassant() const {
    return enpassantTarget;
}

Piece* GameState::getPieceAtPosition(Position position) const {
    return board.getPieceAtPosition(position);
}

void GameState::removePieceAtPosition(Position position) {
    board.removePieceAtPosition(position);
}

bool GameState::isSquareAttacked(const Position sq, const std::string attacker) const {
    bool pawnAttack = isSquareAttackedByPawn(sq, attacker);
    bool knightAttack = isSquareAttackedByKnight(sq, attacker);
    bool linearAttack = isSquareAttackedByRay(sq, attacker);
    bool kingAttack = isSquareAttackedByKing(sq, attacker);

    return pawnAttack || knightAttack || linearAttack || kingAttack;
}

bool GameState::isSquareAttackedByPawn(const Position sq, const std::string attacker) const {
    int dir = attacker == "white" ? -1 : 1;
    int row = sq.getRow(), col = sq.getColumn();
    std::vector<Position> attacks = {Position(row + dir, col + 1), Position(row + dir, col - 1)};
    for (const Position &position : attacks) {
        Piece *piece = getPieceAtPosition(position);
        if (piece && piece->getType() == "Pawn" &&  piece->getColor() == attacker) return true;
    }
    
    return false;
}

bool GameState::isSquareAttackedByKnight(const Position sq, const std::string attacker) const {
    static const int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    int row = sq.getRow(), col = sq.getColumn();
    for (int i = 0; i < 8; i++) {
        int r = knightMoves[i][0], c = knightMoves[i][1];
        Piece *piece = getPieceAtPosition(Position(row + r, col + c));

        if (piece && piece->getColor() == attacker && piece->getType() == "Knight") return true;
    }
    return false;
}

bool GameState::isSquareAttackedByRay(const Position sq, const std::string attacker) const {
    static const int oblique[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
    static const int staight[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    int row = sq.getRow(), col = sq.getColumn();

    for (int i = 0; i < 4; i++) {
        int r = oblique[i][0], c = oblique[i][1];

        Position position(row + r, col + c);
        while (true) {
            if (!board.isInsideBoard(position)) break;
            
            Piece *piece = getPieceAtPosition(position);
            if (piece) {
                if ((piece->getType() == "Queen" || piece->getType() == "Bishop") && piece->getColor() == attacker) return true;
                break;
            }
            
            position = Position(position.getRow() + r, position.getColumn() + c);
        }
    }

    for (int i = 0; i < 4; i++) {
        int r = staight[i][0], c = staight[i][1];
   
        Position position(row + r, col + c);
        while (true) {
            if (!board.isInsideBoard(position)) break;
            
            Piece *piece = getPieceAtPosition(position);
            if (piece) {
                if ((piece->getType() == "Queen" || piece->getType() == "Rook") && piece->getColor() == attacker) return true;
                break;
            }
            
            position = Position(position.getRow() + r, position.getColumn() + c);
        }
    }
    return false;
}
bool GameState::isSquareAttackedByKing(const Position sq, const std::string attacker) const {
    static const int dirs[8][2] = {{1,1},{1,-1},{-1,1},{-1,-1}, {1,0},{-1,0},{0,1},{0,-1}};
    
    int row = sq.getRow(), col = sq.getColumn();
    std::vector<Position> attacks;

    for (int i = 0; i < 8; i++) {
        int r = dirs[i][0], c = dirs[i][1];
        
        Piece *piece = getPieceAtPosition(Position(row + r, col + c));
        if (piece && piece->getType() == "King" &&  piece->getColor() == attacker) return true;
    }
    return false;
}

int GameState::getCastlingRights() const {
    return castlingRights;
}

bool GameState::emptySquare(Position position) const {
    return board.emptySquare(position);
}
