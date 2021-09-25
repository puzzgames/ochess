//
// Created by andrzej on 9/18/21.
//

#include "Rook.h"

using namespace ochess::main;
using namespace ochess::pieces;

void Rook::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, delta90degree, 4, true);
}

Rook::Rook(Board *board, MoveList *moveList, bool color): PieceGen(board, color) {
    pieceMask |= BITMASK_90 | BITMASK_FAR;
    pieceType = ROOK;
    pieceSym = "Rr";
    castlingTouch = true;
}
