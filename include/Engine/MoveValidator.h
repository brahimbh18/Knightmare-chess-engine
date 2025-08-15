#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "../Helpers/Position.h"
#include "../Helpers/Move.h"
#include "GameState.h"
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