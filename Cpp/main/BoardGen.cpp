//
// Created by andrzej on 9/23/21.
//
#include "BoardGen.h"
#include "PieceGen.h"

using namespace ochess::main;

void BoardGen::gen(Dict *dict, MoveList* moveList) {;
    for (int row=7; row>=0; row--) {
        int start;
        if (turnColor)
            start=(7-row)*16;
        else
            start=row*16;
        for (int j=0; j<8; j++) {
            SquareType square = squares[start+j];
            PieceGen* pgen = (PieceGen*)(dict->get(square.color,square.piece));
            if (pgen!=nullptr && pgen->color==turnColor)
                pgen->genKindMoves(start+j, moveList);
        }
    }
}
