//
// Created by andrzej on 9/24/21.
//

#ifndef CNC_CONTEXT_H
#define CNC_CONTEXT_H

#include "../common/Board.h"
#include "../common/Move.h"

using namespace ochess::common;

namespace ochess::cbc {
    const int MaxLevels = 40;
    struct Context {
        Board *board = nullptr;
        Move hist[MaxLevels];
        int ply = 0;
        void print();
        int cnt = 0;
        Context(std::string fen);
        ~Context();
    };
}

#endif //CNC_CONTEXT_H
