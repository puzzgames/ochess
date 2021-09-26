//
// Created by andrzej on 9/19/21.
//
// Intermediate class to avoid mutual dependency betwen pieces a movelists

#ifndef BITSZACHY_PIECEGEN_H
#define BITSZACHY_PIECEGEN_H

#include "../common/PieceKind.h"
#include "../common/Board.h"
#include "MoveList.h"

namespace ochess::main {
    class PieceGen : public PieceKind {
    protected:
        void genMoves(PosType pos, MoveList *moveList, const int deltas[], int deltaCount, bool canFar);

        Board *board;
        bool castlingTouch = false;
    public:
        PieceGen(Board *board, bool color);
        ~PieceGen() override = default;
        virtual void genKindMoves(PosType pos, MoveList *moveList) = 0;
    };
}

#endif //BITSZACHY_PIECEGEN_H
