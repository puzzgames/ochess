//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDQUEEN_H
#define BITSZACHY_KINDQUEEN_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class Queen : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        Queen(Board *board, MoveList *moveList, bool color);

        ~Queen() override = default;
    };
}

#endif //BITSZACHY_KINDQUEEN_H
