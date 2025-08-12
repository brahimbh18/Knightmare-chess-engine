#include "Board.h"
#include "Helpers/Position.h"
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
    if (row >= 0 && row < 8 &&
        col >= 0 && col < 8)
        return board[row][col].get();
    return nullptr;
}

Piece* Board::getPieceAtPosition(Position position) const {
    int row = position.getRow();
    int col = position.getColumn();
    return getPieceAtIndex(row, col);
}


void Board::removePieceAtPosition(Position position) {
    if (!isInsideBoard(position)) return;
    int row = position.getRow();
    int col = position.getColumn();
    board[row][col].reset();
}

bool Board::isInsideBoard(int row, int col) const {
    return row >= 0 && row < 8 &&
           col >= 0 && col < 8;
}

bool Board::isInsideBoard(Position position) const {
    return isInsideBoard(position.getRow(), position.getColumn());
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

void Board::movePiece(const Position& src, const Position& dest) {
    int sr = src.getRow();
    int sc = src.getColumn();
    int dr = dest.getRow();
    int dc = dest.getColumn();
    if (board[sr][sc] == nullptr) {
        return;
    }
    board[dr][dc] = std::move(board[sr][sc]);
    board[sr][sc].reset();
}

std::string Board::toFENBoard() const {
    std::string result;
    for (int row = 7; row >= 0; --row) {
        int emptyCount = 0;
        for (int col = 0; col < 8; ++col) {
            const Piece* p = board[row][col].get();
            if (p == nullptr) {
                ++emptyCount;
            } else {
                if (emptyCount > 0) {
                    result += char('0' + emptyCount);
                    emptyCount = 0;
                }
                char pieceChar = p->getType()[0];
                if (p->getColor() == "black") pieceChar = std::tolower(pieceChar);
                result += pieceChar;
            }
        }
        if (emptyCount > 0) result += char('0' + emptyCount);
        if (row > 0) result += '/';
    }
    return result;
}