#include <iostream>
#include <memory>
#include <string>
#include "GameState.h"
#include "Helpers/Move.h"
#include "Helpers/Position.h"
#include "Helpers/MoveValidator.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide a FEN string as argument.\n";
        std::cerr << "Example: ./chess_engine \"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\"\n";
        return 1;
    }

    std::string fenString = argv[1];
    
    try {
        GameState gameState(fenString);
        std::cout << "Game state created successfully!\n";
        std::cout << "FEN: " << fenString << "\n\n";
        
        // Print the board
        gameState.getBoard().printBoard();
        Position src("e7");
        Position dest("e4");
        
        Move move(src, dest);
        
        MoveValidator v(gameState, move);
        // v.validateMove();
        
    } catch (const std::exception& e) {
        std::cerr << "Error creating game state: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
} 