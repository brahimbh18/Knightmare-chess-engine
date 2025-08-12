#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <stdexcept>


class Position {
    private:
        int row, col;
        std::string algebraic;

        void setCoordsFromAlgebraic();
        void setAlgebraicFromCoords();
    public:
        Position(int, int);
        Position(std::string);

        int getRow() const;
        int getColumn() const;
        std::string getAlgebraic() const;
        static bool equals(Position p1, Position p2);
};
#endif