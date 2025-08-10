#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "Position.h"
#include "Move.h"
#include "../GameState.h"
#include <vector>

class MoveValidator {
    private:
        const GameState& gameState;
        Move move;
        
    public:
        MoveValidator(const GameState& gameState, Move move);
        
        bool validateMove();
};

#endif