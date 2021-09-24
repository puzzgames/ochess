//
// Created by andrzej on 9/18/21.
//

#include "KindBishop.h"

using namespace ochess::main;
using namespace ochess::pieces;

void KindBishop::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, delta45degree, 4, true);
}

KindBishop::KindBishop(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_45 | BITMASK_FAR;
    pieceType = BISHOP;
    pieceSym = "Bb";
}
