//
// Created by andrzej on 9/18/21.
//

#include "KindQueen.h"

using namespace ochess::pieces;

void KindQueen::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, delta90degree, 4, true);
    genMoves(pos, moveList, delta45degree, 4, true);
}

KindQueen::KindQueen(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_45 | BITMASK_90 | BITMASK_FAR;
    pieceType = QUEEN;
    pieceSym = "Qq";
}
