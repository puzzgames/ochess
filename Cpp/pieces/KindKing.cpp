//
// Created by andrzej on 9/18/21.
//

#include "KindKing.h"
#include "../common/SpecialSquares.h"

using namespace ochess::main;
using namespace ochess::pieces;

void KindKing::genKindMoves(PosType pos, MoveList *moveList) {
    genMoves(pos, moveList, delta90degree, 4, false);
    genMoves(pos, moveList, delta45degree, 4, false);
    short castling = board->castling;
    if (castling & (CASTLING_LONG_W|CASTLING_LONG_B))
        genCastlinLong(pos, moveList);
    if (castling & (CASTLING_SHORT_W|CASTLING_SHORT_B))
        genCastlinShort(pos, moveList);
}

KindKing::KindKing(Board *board, MoveList *moveList, bool color) : PieceGen(board, color) {
    pieceMask |= BITMASK_45 | BITMASK_90;
    pieceType = KING;
    pieceSym = "Kk";
    castlingTouch = true;
}

void KindKing::genCastlinLong(PosType pos, MoveList *moveList) {
    if(color) {
        SquareType sqA8 = board->get(A8);
        if (sqA8.color && sqA8.piece == ROOK && board->empty(PosType(B8), 3))
            moveList->addCastling(pos,PosType(C8),PosType(A8),PosType(D8));
    }
    else {
        SquareType sqA1 = board->get(A1);
        if (!sqA1.color && sqA1.piece == ROOK && board->empty(PosType(B1),3))
            moveList->addCastling(pos,PosType(C1),PosType(A1),PosType(D1));
    }
}

void KindKing::genCastlinShort(PosType pos, MoveList *moveList) {
    if(color) {
        SquareType sqH8 = board->get(H8);
        if (sqH8.color && sqH8.piece == ROOK && board->empty(PosType(F8),2))
            moveList->addCastling(pos,PosType(G8),PosType(H8),PosType(F8));
    }
    else {
        SquareType sqH1 = board->get(H1);
        if (!sqH1.color && sqH1.piece == ROOK && board->empty(PosType(F1),2))
            moveList->addCastling(pos,PosType(G1),PosType(H1),PosType(F1));
    }
}
