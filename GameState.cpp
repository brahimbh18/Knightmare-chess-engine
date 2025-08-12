#include "GameState.h"
#include "Helpers/Position.h"
#include "Piece.h"
#include <cctype>

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