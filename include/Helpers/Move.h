#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include <memory>

struct Move {
    Position source;
    Position destination;

    Move(Position src, Position dest)
        : source(src), destination(dest) {}
};
#endif