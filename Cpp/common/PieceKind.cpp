//
// Created by andrzej on 9/18/21.
//

#include <cstring>
#include "PieceKind.h"

using namespace ochess::common;

constexpr int PieceKind::delta90degree[];
constexpr int PieceKind::delta45degree[];
constexpr int PieceKind::deltaKnight[];

constexpr PieceType PieceKind::EMPTY;
constexpr PieceType PieceKind::PAWN;
constexpr PieceType PieceKind::KNIGHT;
constexpr PieceType PieceKind::BISHOP;
constexpr PieceType PieceKind::ROOK;
constexpr PieceType PieceKind::QUEEN;
constexpr PieceType PieceKind::KING;

std::string PieceKind::piecetypeToSymArray[2] = {".PNBRQK", ".pnbrqk"};

char PieceKind::getSym(PieceType type, bool color) {
    return piecetypeToSymArray[color][type];
}

SquareType PieceKind::symToSquare(char sym) {
    bool color;
    size_t pos = piecetypeToSymArray[false].find(sym);
    if (pos==std::string::npos) {
        pos = piecetypeToSymArray[true].find(sym);
        if (pos==std::string::npos)
            throw new std::exception;
        else color = true;
    } else color = false;
    return SquareType(PieceType(pos),color);
}

PieceType PieceKind::symToType(char sym) {
    bool color;
    size_t pos = piecetypeToSymArray[false].find(sym);
    if (pos==std::string::npos) {
        pos = piecetypeToSymArray[true].find(sym);
        if (pos==std::string::npos)
            throw new std::exception;
        else color = true;
    } else color = false;
    return PieceType(pos);
}
