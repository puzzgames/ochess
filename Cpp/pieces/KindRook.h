//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDROOK_H
#define BITSZACHY_KINDROOK_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class KindRook : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        KindRook(Board *board, MoveList *moveList, bool color);

        ~KindRook() override = default;
    };
}

#endif //BITSZACHY_KINDROOK_H
