//
// Created by andrzej on 9/18/21.
//

#include "Pawn.h"

using namespace ochess::main;
using namespace ochess::pieces;

void Pawn::genKindMoves(PosType pos, MoveList *moveList) {
    if (color) {
        if (Board::onInitPawnLine(pos, color)) {
            if (board->empty(pos-16)) {
                moveList->addSimpleMove(pos, pos-16, EMPTY, false);
                if (board->empty(pos-32))
                    moveList->addDoublePawnMove(pos, pos-32, pos-16);
            }
            if (board->oppositeOnBoard(pos-15,color))
                moveList->addSimpleMove(pos, pos-15, board->get(pos-15).piece, false);
            if (board->oppositeOnBoard(pos-17,color))
                moveList->addSimpleMove(pos, pos-17, board->get(pos-17).piece, false);
        }
        else if (Board::onPromotionLine(pos, color)) {
            if (board->empty(pos-16))
                moveList->addPromotionsMultiMove(pos, pos-16, EMPTY);
            if (board->oppositeOnBoard(pos-15,color))
                moveList->addPromotionsMultiMove(pos, pos-15, board->get(pos-15).piece);
            if (board->oppositeOnBoard(pos-17,color))
                moveList->addPromotionsMultiMove(pos, pos-17, board->get(pos-17).piece);
        } else {
            if (board->emptyOnBoard(pos-16))
                moveList->addSimpleMove(pos, pos-16, EMPTY, false);
            if (board->oppositeOnBoard(pos-15,color))
                moveList->addSimpleMove(pos, pos-15, board->get(pos-15).piece, false);
            if (board->oppositeOnBoard(pos-17,color))
                moveList->addSimpleMove(pos, pos-17, board->get(pos-17).piece, false);
            if (pos-15==board->enPassantPos || pos-17==board->enPassantPos)
                moveList->addEnPassantMove(pos,board->enPassantPos, board->enPassantPos+16);
        }
    }
    else {
        if (Board::onInitPawnLine(pos, color)) {
            if (board->empty(pos+16)) {
                moveList->addSimpleMove(pos, pos+16, EMPTY, false);
                if (board->empty(pos+32))
                    moveList->addDoublePawnMove(pos, pos+32, pos+16);
            }
            if (board->oppositeOnBoard(pos+15,color))
                moveList->addSimpleMove(pos, pos+15, board->get(pos+15).piece, false);
            if (board->oppositeOnBoard(pos+17,color))
                moveList->addSimpleMove(pos, pos+17, board->get(pos+17).piece, false);
        }
        else if (Board::onPromotionLine(pos, color)) {
            if (board->empty(pos+16))
                moveList->addPromotionsMultiMove(pos, pos+16, EMPTY);
            if (board->oppositeOnBoard(pos+15,color))
                moveList->addPromotionsMultiMove(pos, pos+15, board->get(pos+15).piece);
            if (board->oppositeOnBoard(pos+17,color))
                moveList->addPromotionsMultiMove(pos, pos+17, board->get(pos+17).piece);
        } else {
            if (board->emptyOnBoard(pos+16))
                moveList->addSimpleMove(pos, pos+16, EMPTY, false);
            if (board->oppositeOnBoard(pos+15,color))
                moveList->addSimpleMove(pos, pos+15, board->get(pos+15).piece, false);
            if (board->oppositeOnBoard(pos+17,color))
                moveList->addSimpleMove(pos, pos+17, board->get(pos+17).piece, false);
            if (pos+15==board->enPassantPos || pos+17==board->enPassantPos)
                moveList->addEnPassantMove(pos,board->enPassantPos,board->enPassantPos-16);
        }
    }
}

Pawn::Pawn(Board *board, MoveList *moveList, bool color): PieceGen(board, color) {
    pieceMask |= BITMASK_PAWN;
    pieceType = PAWN;
    pieceSym = "Pp";
}
