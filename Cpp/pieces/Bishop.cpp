//
// Created by andrzej on 9/18/21.
//

#include "Bishop.h"

using namespace ochess::main;
using namespace ochess::pieces;

void Bishop::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, delta45degree, 4, true);
}

Bishop::Bishop(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_45 | BITMASK_FAR;
    pieceType = BISHOP;
    pieceSym = "Bb";
}
