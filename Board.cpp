#include "Board.h"
#include <iostream>

void Board::printBoard() const {
    std::cout << "  a b c d e f g h\n";
    std::cout << "  ---------------\n";
    
    for (int row = 7; row >= 0; row--) {
        std::cout << row + 1 << " ";
        for (int col = 0; col < 8; col++) {
            if (board[row][col] == nullptr) {
                std::cout << ". ";
            } else {
                char pieceChar = board[row][col]->getType()[0];
                std::string color = board[row][col]->getColor();
                
                if (color == "black") {
                    pieceChar = std::tolower(pieceChar);
                }
                
                std::cout << pieceChar << " ";
            }
        }
        std::cout << row + 1 << "\n";
    }
    std::cout << "  ---------------\n";
    std::cout << "  a b c d e f g h\n";
}

Piece* Board::getPieceAtIndex(int row, int col) const {
    return board[row][col].get();
}

void Board::setBoardFromFEN(const std::string& fenBoard) {
   int row = 7, col = 0;

    for (char c : fenBoard) {
        if (c == '/') {
            row--;
            col = 0;
        } else if (std::isdigit(c)) {
            col += c - '0';
        } else {
            board[row][col++] = Piece::generatePieceByFENCHAR(c);
        }
    }
}