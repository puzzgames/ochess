//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDBISHOP_H
#define BITSZACHY_KINDBISHOP_H


#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class KindBishop : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        KindBishop(Board *board, MoveList *moveList, bool color);

        ~KindBishop() override = default;
    };
}

#endif //BITSZACHY_KINDBISHOP_H
