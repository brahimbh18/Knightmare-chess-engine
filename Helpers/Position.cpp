#include "Position.h"
#include <cctype>

Position::Position(int row, int col): row(row), col(col) {
    setAlgebraicFromCoords();
}

Position::Position(std::string algebraic): algebraic(algebraic) {
    setCoordsFromAlgebraic();
}

void Position::setCoordsFromAlgebraic() {
    if (algebraic.size() == 2 && std::isalpha(static_cast<unsigned char>(algebraic[0])) && std::isdigit(static_cast<unsigned char>(algebraic[1]))) {
        col = std::tolower(static_cast<unsigned char>(algebraic[0])) - 'a';
        row = algebraic[1] - '1';
    } else {
        throw std::invalid_argument("Invalid algebraic notation: " + algebraic);
    }
}

void Position::setAlgebraicFromCoords() {
    algebraic.clear();
    algebraic.push_back(static_cast<char>('a' + col));
    algebraic.push_back(static_cast<char>('1' + row));
}

int Position::getRow() const {
    return row;
}

int Position::getColumn() const {
    return col;
}

std::string Position::getAlgebraic() const {
    return algebraic;
}

bool Position::equals(Position p1, Position p2) {
    return p1.getRow() == p2.getRow() && 
           p1.getColumn() == p2.getColumn();
}