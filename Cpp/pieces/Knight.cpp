//
// Created by andrzej on 9/18/21.
//

#include "Knight.h"

using namespace ochess::main;
using namespace ochess::pieces;

void Knight::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, deltaKnight, 8, false);
}

Knight::Knight(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_KNIGHT;
    pieceType = KNIGHT;
    pieceSym = "Nn";
}
