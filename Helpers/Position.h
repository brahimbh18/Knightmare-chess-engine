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

        int getRow();
        int getColumn();
        std::string getAlgebraic();
        
};
#endif