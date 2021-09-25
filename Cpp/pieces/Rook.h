//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDROOK_H
#define BITSZACHY_KINDROOK_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class Rook : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        Rook(Board *board, MoveList *moveList, bool color);

        ~Rook() override = default;
    };
}

#endif //BITSZACHY_KINDROOK_H
