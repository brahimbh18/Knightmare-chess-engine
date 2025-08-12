#ifndef ENGINE_API_H
#define ENGINE_API_H

#include <string>
#include <vector>

// Validates and applies a move. Returns pair<ok, newFEN>. If ok == false, newFEN is empty.
std::pair<bool, std::string> applyMoveIfLegal(const std::string& fen,
                                              const std::string& srcAlgebraic,
                                              const std::string& dstAlgebraic);

// Returns legal moves (as algebraic squares) for a piece at position; empty if none or invalid input
std::vector<std::string> getLegalMovesForPosition(const std::string& fen,
                                                  const std::string& positionAlgebraic);

#endif
