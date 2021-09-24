//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDKNIGHT_H
#define BITSZACHY_KINDKNIGHT_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class KindKnight : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        KindKnight(Board *board, MoveList *moveList, bool color);

        ~KindKnight() override = default;
    };
}

#endif //BITSZACHY_KINDKNIGHT_H
