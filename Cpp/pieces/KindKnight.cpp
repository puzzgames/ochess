//
// Created by andrzej on 9/18/21.
//

#include "KindKnight.h"

using namespace ochess::main;
using namespace ochess::pieces;

void KindKnight::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, deltaKnight, 8, false);
}

KindKnight::KindKnight(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_KNIGHT;
    pieceType = KNIGHT;
    pieceSym = "Nn";
}
