#include "GameState.h"
#include "Helpers/Move.h"
#include "Helpers/Position.h"

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
    
    enpassantTarget = parts[3] == "-" ? nullptr : std::make_unique<Position>(parts[3]);

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

