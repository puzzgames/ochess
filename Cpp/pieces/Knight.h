//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_KINDKNIGHT_H
#define BITSZACHY_KINDKNIGHT_H

#include "../common/PieceKind.h"
#include "../main/PieceGen.h"

using namespace ochess::main;

namespace ochess::pieces {
    class Knight : public PieceGen {
        void genKindMoves(PosType pos, MoveList *moveList) override;

    public:
        Knight(Board *board, MoveList *moveList, bool color);

        ~Knight() override = default;
    };
}

#endif //BITSZACHY_KINDKNIGHT_H
