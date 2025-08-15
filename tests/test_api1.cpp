#include <iostream>
#include <string>
#include <utility>
#include "../include/api/EngineAPI.h"  // for applyMoveIfLegal

static bool expectMove(const std::string& fen,
                       const std::string& from,
                       const std::string& to,
                       bool expectedLegal,
                       const std::string& expectedFenIfLegal = "")
{
    auto result = applyMoveIfLegal(fen, from, to);

    bool legal = result.first;
    bool ok = (legal == expectedLegal);

    if (!ok) {
        std::cout << "❌ " << from << " -> " << to
                  << " expected " << (expectedLegal ? "LEGAL" : "ILLEGAL")
                  << " but got " << (legal ? "LEGAL" : "ILLEGAL") << "\n";
    } else {
        std::cout << "✅ " << from << " -> " << to
                  << " (" << (legal ? "LEGAL" : "ILLEGAL") << ")\n";
    }

    // If legal, optionally check returned FEN
    if (legal && !expectedFenIfLegal.empty()) {
        if (result.second != expectedFenIfLegal) {
            std::cout << "   ❌ FEN mismatch!\n"
                      << "      Expected: " << expectedFenIfLegal << "\n"
                      << "      Got     : " << result.second << "\n";
            ok = false;
        }
    }

    return ok;
}

int main() {
    int failed = 0;

    const std::string START =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::cout << "=== applyMoveIfLegal() Tests ===\n\n";

    // Knights
    failed += !expectMove(START, "b1", "a3", true);
    failed += !expectMove(START, "b1", "c3", true);
    failed += !expectMove(START, "g1", "f3", true);
    failed += !expectMove(START, "g1", "h3", true);
    failed += !expectMove(START, "g1", "e2", false); // own pawn on e2

    // Pawns
    failed += !expectMove(START, "e2", "e3", true);
    failed += !expectMove(START, "e2", "e4", true);
    failed += !expectMove(START, "e2", "e5", false);

    // Blocked rook
    failed += !expectMove(START, "a1", "a3", false);

    // Pawn capture scenario
    const std::string PAWN_CAP =
        "rnbqkbnr/pppppppp/8/8/pP/8/PPPPPPPP/RNBQKBNR w KQkq b4 0 1";
    failed += !expectMove(PAWN_CAP, "a4", "b4", true);   // capture
                                                           
    std::cout << "\nSummary: " << (failed == 0 ? "ALL TESTS PASSED"
                                              : std::to_string(failed) + " TEST(S) FAILED")
              << "\n";
    return failed == 0 ? 0 : 1;
}
