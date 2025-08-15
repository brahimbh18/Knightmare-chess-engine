#include "../include/Piece.h"

Piece::Piece(const std::string& type, const std::string& color): type(type), color(color) {}

std::unique_ptr<Piece> Piece::generatePieceByFENCHAR(const char c) {
    std::string color = std::isupper(c) ? "white" : "black";
    
    switch (std::tolower(c)) {
        case 'p': return std::make_unique<Piece>("Pawn", color);
        case 'k': return std::make_unique<Piece>("King", color);
        case 'q': return std::make_unique<Piece>("Queen", color);
        case 'r': return std::make_unique<Piece>("Rook", color);
        case 'b': return std::make_unique<Piece>("Bishop", color);
        case 'n': return std::make_unique<Piece>("Knight", color);
        default: return nullptr;
    }
}

std::string Piece::getType() const {
    return type;
}

std::string Piece::getColor() const {
    return color;
}

