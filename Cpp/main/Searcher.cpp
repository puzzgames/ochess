//
// Created by andrzej on 9/20/21.
//
#include <cstring>
#include <iostream>
#include "Searcher.h"

using namespace ochess::main;

void Searcher::MiniMax(Dict *dict, int depth) {
    if (depth == 0) {
        count++;
        thrCounter++;
        return;
    }
    levsize[ply] = 0;
    board->gen(dict, this);
    for (int i=0; i < levsize[ply]; i++) {
        MakeMove(i);
        MiniMax(dict, depth - 1);
        takeBack();
    }
}

Searcher::Searcher(BoardGen *board):board(board) {
}

FILE *myfile;
void Searcher::MakeMove(int index) {
    Move move = level[index];
    if (ply==partDepth-1) thrCounter = 0;
    if (ply<partDepth) {
        fprintf(myfile, "%d. %s", ply + 1, move.toHuman(board).c_str()); //fprintf is faster than ofstream for big files
        if (ply<partDepth-1)
            fprintf(myfile, "\n");
    }
    move.makeMove(board);
    hist[ply] = move;
    ply++;
    if (!levels[ply])
        levels[ply] = new Move[MaxMoves];
    level = levels[ply];
    /*board->turnColor = !board->turnColor;*/
}

void Searcher::takeBack() {
    //board->turnColor = !board->turnColor;
    ply--;
    level = levels[ply];
    Move move = hist[ply];
    if (ply==partDepth-1) {
        if (partDepth<fullDepth)
            fprintf(myfile, " =>%ld\n",thrCounter);
        else
            fprintf(myfile, "\n");
    }
    move.takeBack(board);
}

void Searcher::addSimpleMove(PosType from, PosType to, PieceType captured, bool touchCastling) {
    Move move(from, to);
    if (touchCastling) {
        auto castlingFlag = board->castling;
        FlagsType disableCastling;
        if (board->get(from).piece==PieceKind::KING) {
            if (board->turnColor)
                disableCastling = CASTLING_LONG_B | CASTLING_SHORT_B;
            else
                disableCastling = CASTLING_LONG_W | CASTLING_SHORT_W;
        }
        else { //rooks
            int col = from  & 7;
            if (board->turnColor) {
                if (col == 0)
                    disableCastling = CASTLING_LONG_B;
                else if (col == 7)
                    disableCastling = CASTLING_SHORT_B;
                else
                    disableCastling = 0;
            } else {
                if (col == 0)
                    disableCastling = CASTLING_LONG_W;
                else if (col == 7)
                    disableCastling = CASTLING_SHORT_W;
                else
                    disableCastling = 0;
            }
        }
        //very subltle condition
        move.justCastlingDisabled = castlingFlag & disableCastling;
    }
    level[levsize[ply]] = move;
    levsize[ply]++;
}

void Searcher::addDoublePawnMove(PosType from, PosType to, PosType oneStepPos) {
    Move move(from, to);
    level[levsize[ply]] = move;
    levsize[ply]++;
}

void Searcher::addEnPassantMove(PosType from, PosType to, PosType capturedPos) {
    Move move(from, to);
    level[levsize[ply]] = move;
    levsize[ply]++;
}

void Searcher::addCastling(PosType from, PosType to, PosType rookFrom, PosType rookTo) {
    Move move(from, to);
    level[levsize[ply]] = move;
    levsize[ply]++;
}

void Searcher::addPromotionsMultiMove(PosType from, PosType to, PieceType captured) {
    addPromotionMove(from, to, captured, PieceKind::QUEEN);
    addPromotionMove(from, to, captured, PieceKind::ROOK);
    addPromotionMove(from, to, captured, PieceKind::BISHOP);
    addPromotionMove(from, to, captured, PieceKind::KNIGHT);
}

void Searcher::addPromotionMove(PosType from, PosType to, PieceType captured, PieceType promoteTo) {
    Move move(from, to, promoteTo);
    level[levsize[ply]] = move;
    levsize[ply]++;
}