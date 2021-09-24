//
// Created by andrzej on 9/23/21.
//

#ifndef BITSZACHY_BOARDGEN_H
#define BITSZACHY_BOARDGEN_H

#include "../common/Board.h"
#include "Dict.h"
#include "MoveList.h"

namespace ochess::main {
    class BoardGen : public Board {
    public:
        void gen(Dict *dict, MoveList *moveList);
    };
}

#endif //BITSZACHY_BOARDGEN_H
