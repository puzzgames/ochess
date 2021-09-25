//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDPAWN_H
#define BITSZACHY_KINDPAWN_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class Pawn : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        Pawn(Board *board, MoveList *moveList, bool color);

        ~Pawn() override = default;
    };
}

#endif //BITSZACHY_KINDPAWN_H
