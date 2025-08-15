#include <iostream>
#include "../include/api/EngineAPI.h"


#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>


// Pretty print a sorted vector
static void printMoves(const std::vector<std::string>& moves) {
    std::cout << "{ ";
    for (size_t i = 0; i < moves.size(); ++i) {
        std::cout << moves[i];
        if (i + 1 < moves.size()) std::cout << ", ";
    }
    std::cout << " }";
}

// Core test function
static bool testMoveGeneration(const std::string& fen,
                                const std::string& square,
                                const std::vector<std::string>& expectedRaw)
{
    // Copy & sort expected
    std::vector<std::string> expected = expectedRaw;
    std::sort(expected.begin(), expected.end());

    // Get result & sort
    std::vector<std::string> got = getLegalMovesForPosition(fen, square);
    std::sort(got.begin(), got.end());

    // Quick equality check
    bool ok = (expected == got);

    // If mismatch, compute set diffs for helpful output
    if (!ok) {
        std::set<std::string> exp(expected.begin(), expected.end());
        std::set<std::string> res(got.begin(), got.end());

        std::vector<std::string> missing, unexpected;
        std::set_difference(exp.begin(), exp.end(), res.begin(), res.end(),
                            std::back_inserter(missing));
        std::set_difference(res.begin(), res.end(), exp.begin(), exp.end(),
                            std::back_inserter(unexpected));

        std::cout << "❌ Test FAILED for square " << square << "\n";
        std::cout << "   Expected: "; printMoves(expected); std::cout << "\n";
        std::cout << "   Got     : "; printMoves(got);      std::cout << "\n";
        if (!missing.empty())   { std::cout << "   Missing : ";   printMoves(missing);   std::cout << "\n"; }
        if (!unexpected.empty()){ std::cout << "   Unexpected: "; printMoves(unexpected);std::cout << "\n"; }
    } else {
        std::cout << "✅ Test PASSED for square " << square << "  ";
        printMoves(expected);
        std::cout << "\n";
    }
    return ok;
}


int main() {
    std::string startFEN = "r3k2r/8/8/8/8/8/8/4K2R b kqKQ - 0 1";
    std::cout << "=== Move Generation Tests ===\n\n";
    int failed = 0;

    failed += !testMoveGeneration(startFEN, "e8", {"d8", "d7", "c8", "e7", "f7", "f8", "g8"});

    std::cout << "\nSummary: " << (failed == 0 ? "ALL TESTS PASSED" : std::to_string(failed) + " TEST(S) FAILED") << "\n";
    return failed == 0 ? 0 : 1;
}