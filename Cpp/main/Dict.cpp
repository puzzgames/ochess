//
// Created by andrzej on 9/19/21.
//

#include "Dict.h"
#include "../pieces/KindPawn.h"
#include "../pieces/KindKnight.h"
#include "../pieces/KindBishop.h"
#include "../pieces/KindRook.h"
#include "../pieces/KindQueen.h"
#include "../pieces/KindKing.h"

using namespace ochess::main;
using namespace ochess::pieces;

Dict::Dict(Board *board, MoveList *movelist) {
    for (int i=0; i<2; i++) {
        bool color = (bool)i;
        dict[i][0] = nullptr;
        dict[i][1] = new KindPawn(board, movelist, color);
        dict[i][2] = new KindKnight(board, movelist, color);
        dict[i][3] = new KindBishop(board, movelist, color);
        dict[i][4] = new KindRook(board, movelist, color);
        dict[i][5] = new KindQueen(board, movelist, color);
        dict[i][6] = new KindKing(board, movelist, color);}
}

Dict::~Dict() {
    for (int i=0; i<2; i++)
        for (int j=0; j<7; j++)
            delete dict[i][j];
}

PieceKind* Dict::get(bool color, unsigned char pieceType) {
        return dict[color][pieceType];
}
