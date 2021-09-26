//
// Created by andrzej on 9/19/21.
//

#include "PieceGen.h"

using namespace ochess::main;

PieceGen::PieceGen(Board *board, bool color): board(board) {
    this->color = color;
    pieceMask = color;
}

void PieceGen::genMoves(PosType pos, MoveList *moveList, const int deltas[], int deltaCount,bool canFar) {
    if (canFar)
    for (int i=0; i<deltaCount; i++) {
        int delta = deltas[i];
        PosType newPos = pos + delta;

        while (board->onBoard(newPos) && board->emptyOrOpposite(color, newPos)) {
            bool nonempty = board->nonempty(newPos);
            FlagsType flags;
            moveList->addSimpleMove(pos, newPos,  nonempty?board->get(newPos).piece:EMPTY, castlingTouch);
            if (nonempty) break;
            newPos += delta;
        }
    }
     else for (int i=0; i<deltaCount; i++) {
            int delta = deltas[i];
            PosType newPos = pos + delta;
        if (board->onBoard(newPos) && board->emptyOrOpposite(color, newPos)) {
            bool nonempty = board->nonempty(newPos);
            moveList->addSimpleMove(pos, newPos,  nonempty?board->get(newPos).piece:EMPTY, castlingTouch);
        }
    }
}
