//
// Created by andrzej on 9/19/21.
//

#include "Dict.h"
#include "../pieces/Pawn.h"
#include "../pieces/Knight.h"
#include "../pieces/Bishop.h"
#include "../pieces/Rook.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"

using namespace ochess::main;
using namespace ochess::pieces;

Dict::Dict(Board *board, MoveList *movelist) {
    for (int i=0; i<2; i++) {
        bool color = (bool)i;
        dict[i][0] = nullptr;
        dict[i][1] = new Pawn(board, movelist, color);
        dict[i][2] = new Knight(board, movelist, color);
        dict[i][3] = new Bishop(board, movelist, color);
        dict[i][4] = new Rook(board, movelist, color);
        dict[i][5] = new Queen(board, movelist, color);
        dict[i][6] = new King(board, movelist, color);}
}

Dict::~Dict() {
    for (int i=0; i<2; i++)
        for (int j=0; j<7; j++)
            delete dict[i][j];
}

PieceKind* Dict::get(bool color, unsigned char pieceType) {
        return dict[color][pieceType];
}
