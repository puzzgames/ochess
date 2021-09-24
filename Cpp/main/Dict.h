//
// Created by andrzej on 9/19/21.
//

#ifndef BITSZACHY_DICT_H
#define BITSZACHY_DICT_H

#include "../common/PieceKind.h"
#include "../common/Board.h"
#include "MoveList.h"

namespace ochess::main {
    class Dict {
        PieceKind *dict[2][7];
    public:
        Dict(Board *board, MoveList *movelist);

        ~Dict();

        PieceKind *get(bool color, unsigned char pieceType);
    };
}

#endif //BITSZACHY_DICT_H
