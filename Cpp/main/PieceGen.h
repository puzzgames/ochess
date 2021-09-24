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

        //can be one king, 8 pawns, but for example 10 knigts if all pawns promoted to knight
        //PosType pos[MaxPos]; to do dict
        //PieceKind(Board &board, bool turnColor);
        void genAttacks(PosType pos, int deltas[], int deltaCount, bool canFar);
    };
}

#endif //BITSZACHY_PIECEGEN_H
