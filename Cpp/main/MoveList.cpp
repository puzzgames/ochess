//
// Created by andrzej on 9/18/21.
//

#include <cassert>
#include "MoveList.h"
#include "../common/PieceKind.h"

using namespace ochess::main;

MoveList::MoveList() {
    using PMove = Move*;
    levels = new PMove[MaxLevels];
    for (int i=0; i<MaxLevels; i++) {
        levels[i] = new Move[MaxMoves];
        levsize[i] = 0;
    }
    //levels[0] = new Move[MaxMoves];
    level = levels[0];
}

MoveList::~MoveList() {
    for (int i=0; i<MaxLevels; i++)
        delete[] levels[i];
    delete[] levels;
}

