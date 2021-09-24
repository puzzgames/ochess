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

/*
    for (int i=0; i<deltaCount; i++) {
        int delta = deltas[i];
        PosType newPos = pos+delta;
        if (canFar)
            while (board.onBoard(newPos) && board.emptyOrOpposite(color, newPos)) {
                bool nonempty = board.nonempty(newPos);
                FlagsType kind;
                kind = nonempty?Moveflag_capture:0;
                moveList.addMove(pos,newPos,kind);
                if (nonempty) break;
                newPos+=delta;
            }
        else if (board.onBoard(newPos) && board.emptyOrOpposite(color, newPos)) {
            moveList.addMove(pos,newPos,{0});
        }
    }
}
*/
void PieceGen::genAttacks(PosType pos, int deltas[], int deltaCount, bool canFar) {
    for (int i=0; i<deltaCount; i++) {
        int delta = deltas[i];
        PosType newPos = pos+delta;
        if (canFar)
            while (board->onBoard(newPos)) {
                //map.addSqaure(newPos);
                newPos+=delta;
            }
        else if (board->onBoard(newPos)) {
            //map.addSqaure(newPos);
        }
    }
}
