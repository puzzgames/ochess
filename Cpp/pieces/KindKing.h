//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDKING_H
#define BITSZACHY_KINDKING_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class KindKing : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

        void genCastlinLong(PosType pos, MoveList *moveList);

        void genCastlinShort(PosType pos, MoveList *moveList);

    public:
        KindKing(Board *board, MoveList *moveList, bool color);

        ~KindKing() override = default;
    };
}

#endif //BITSZACHY_KINDKING_H
