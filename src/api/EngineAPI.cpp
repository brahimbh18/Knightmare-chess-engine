#include "../../include/api/EngineAPI.h"
#include "../../include/Engine/GameState.h"
#include "../../include/Helpers/Position.h"
#include "../../include/Helpers/Move.h"
#include "../../include/Engine/MoveValidator.h"
#include "../../include/Engine/MoveGenerator.h"

std::pair<bool, std::string> applyMoveIfLegal(const std::string& fen,
                                              const std::string& srcAlgebraic,
                                              const std::string& dstAlgebraic) {
    GameState gameState(fen);
    Position src(srcAlgebraic);
    Position dst(dstAlgebraic);
    Move move(src, dst);

    MoveValidator validator(gameState, move);
    if (!validator.validateMove()) {
        return {false, std::string()};
    }

    // Apply move and return new FEN
    gameState.applyMove(move);
    return {true, gameState.toFEN()};
}

std::vector<std::string> getLegalMovesForPosition(const std::string& fen,
                                                  const std::string& positionAlgebraic) {
    GameState gameState(fen);
    Position src(positionAlgebraic);
    Piece* piece = gameState.getBoard().getPieceAtPosition(src);
    if (piece == nullptr) {
        return {};
    }
    MoveGenerator gen(gameState);
    std::vector<Position> moves = gen.getLegalMoves(piece, src);
    std::vector<std::string> out;
    out.reserve(moves.size());
    for (Position& p : moves) {
        out.push_back(p.getAlgebraic());
    }
    return out;
} 