//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDQUEEN_H
#define BITSZACHY_KINDQUEEN_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class KindQueen : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        KindQueen(Board *board, MoveList *moveList, bool color);

        ~KindQueen() override = default;
    };
}

#endif //BITSZACHY_KINDQUEEN_H
