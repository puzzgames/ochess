//
// Created by andrzej on 9/23/21.
//
#include "Move.h"

using namespace ochess::common;

Move::Move() {
    assert(sizeof(*this)==sizeof(uint64_t));
    *((uint64_t*)(this)) = 0;
}

Move::Move(std::string humanString, Board* board):Move()  {
    this->from = board->toPos(humanString[0], humanString[1]);
    this->to = board->toPos(humanString[3], humanString[4]);
    if (humanString.size()>5) {
        char sym = humanString[4];
        promoteTo = PieceKind::symToType(sym);
        kind = MoveKind_promote;
    }
    else kind = MoveKind_simple;
}


Move::Move(PosType from, PosType to, PieceType promoteTo):Move()  {
    this->from = from;
    this->to = to;
    if (promoteTo!=PieceKind::EMPTY) {
        this->promoteTo = promoteTo;
        kind = MoveKind_promote;
    }
    else kind = MoveKind_simple;
}

std::string Move::toHuman(Board* board) {
    std::string ret = board->fromPos(from)+"-"+board->fromPos(to);
    if (kind == MoveKind_promote)
        ret +=  PieceKind::getSym(promoteTo, board->turnColor);
    return ret;
}

bool Move::operator<(const Move &rhs) {
    if (from != rhs.from)
        return from < rhs.from;
    if (to != rhs.to)
        return to < rhs.to;
    return promoteTo < rhs.promoteTo;
};

bool Move::operator>(const Move &rhs) {
    if (from != rhs.from)
        return from > rhs.from;
    if (to != rhs.to)
        return to > rhs.to;
    return promoteTo > rhs.promoteTo;
};

bool Move::move_sorter(Move const& lhs, Move const& rhs) {
    if (lhs.from != rhs.from)
        return lhs.from < rhs.from;
    if (lhs.to != rhs.to)
        return lhs.to < rhs.to;
    return lhs.promoteTo < rhs.promoteTo;
}

void Move::addOtherFlags(Board* board) {
    if (board->get(from).piece==PieceKind::PAWN) {
        int delta = to-from;
        if (delta==32 || delta==-32)
            kind = MoveKind_doublePawnInit;
        else
            if (to == board->enPassantPos)
                kind = MoveKind_enPassant;
    } else {
        int deltaCol = to - from;
        if (board->get(from).piece == PieceKind::KING && (deltaCol == -2 || deltaCol == 2))
            kind = MoveKind_castling;
    }
}

void Move::makeMove(Board* board) {
    addOtherFlags(board);
    captured = board->get(to).piece;
    board->moveSquare(from,to);
    board->castling &= ~justCastlingDisabled;
    boardSavEP = board->enPassantPos;
    if (kind == MoveKind_doublePawnInit) {
        board->enPassantPos = (from+to)/2;
    } else {
        if (kind == MoveKind_enPassant) {
            captured = PieceKind::PAWN;
            bool colorEp = board->enPassantPos>=64;
            int posCapturableEP = colorEp?board->enPassantPos-16:board->enPassantPos+16;
            board->remove(posCapturableEP);
        } else {
            if (kind == MoveKind_castling) {
                if (to=from-2) {
                    rookFrom = from-4;
                    rookTo = from-1;
                }
                else {
                    rookFrom = from+3;
                    rookTo = from+1;
                }
                board->moveSquare(rookFrom, rookTo);
            }
        }
        board->enPassantPos = -1;
    }
    board->turnColor = !board->turnColor;
}

void Move::takeBack(Board* board) {
    board->turnColor = !board->turnColor;
    PieceType cap;
    if (kind==MoveKind_castling) //only if due to union captured with rookFrom
        cap = PieceKind::EMPTY;
    else
        cap = captured;
    bool restoreColor = cap != PieceKind::EMPTY && !board->turnColor;
    if (kind == MoveKind_enPassant) {
        bool colorEp = board->enPassantPos>=64;
        int posCapturableEP = colorEp?board->enPassantPos-16:board->enPassantPos+16;
        board->moveSquareWithRestore(posCapturableEP, from, cap, restoreColor);
    }
    else
        board->moveSquareWithRestore(to,from, cap, restoreColor);
    board->enPassantPos = boardSavEP;
    if (kind == MoveKind_castling)
        board->moveSquare(rookTo,rookFrom);
    board->castling |= justCastlingDisabled;
}

std::string Move::toDebug() {
    return std::to_string(from)+"-"+std::to_string(to);
}

