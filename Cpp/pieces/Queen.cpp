//
// Created by andrzej on 9/18/21.
//

#include "Queen.h"

using namespace ochess::pieces;

void Queen::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, delta90degree, 4, true);
    genMoves(pos, moveList, delta45degree, 4, true);
}

Queen::Queen(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_45 | BITMASK_90 | BITMASK_FAR;
    pieceType = QUEEN;
    pieceSym = "Qq";
}
