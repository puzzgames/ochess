//
// Created by andrzej on 9/18/21.
//
#include <cstring>
#include <iostream>
#include <sstream>
#include <cassert>
#include "Board.h"
#include "xxHash.h"

using namespace ochess::common;

Board::Board() {
    clearSquares();
}


Board::~Board() {
}

bool Board::onBoard(PosType pos) {
    return (pos & ~(127-8)) == 0;
}

bool Board::emptyOrOpposite(bool mycolor, PosType pos) {
    SquareType square = squares128[pos];
    return (square.piece==0) || (square.color != mycolor);
}

bool Board::opposite(PosType pos, bool mycolor) {
    SquareType square = squares128[pos];
    return (square.piece!=0) && (square.color != mycolor);
}

bool Board::oppositeOnBoard(PosType pos, bool mycolor) {
    return onBoard(pos) && opposite(pos, mycolor);
}

bool Board::nonempty(PosType pos) {
    return squares128[pos].piece != 0;
}

bool Board::empty(PosType pos) {
    return squares128[pos].piece == 0;
}

bool Board::empty(PosType pos, int num) {
    for (int i=pos; i<pos+num; i++)
        if (squares128[i].piece != 0)
            return false;
    return true;
}

bool Board::emptyOnBoard(PosType pos) {
    return onBoard(pos) && empty(pos);
}

//7 bit is used in 128 squares128 board, 6 in 64 squares128 binary board
/*
bits7to6 changes 0abc0def to 00abcded
first divide to two parts: lower with mask 00000111 upper with maska 00000111
 upper part shift to right and or both parts
 * */
PosType Board::bits7to6(PosType pos) {
    PosType lower = pos & 7;
    PosType upper = pos & (7*16);
    return lower | (upper >> 1);
}

/*
bits6to7 changes  00abcded to 0abc0def
 first divide to two parts: lower with mask 00000111 upper with maska 00000111
 upper part shift to left and or both parts
 * */
PosType Board::bits6to7(PosType pos) {
    PosType lower = pos & 7;
    PosType upper = pos & (7*16);
    return lower | (upper << 1);
}

PosType Board::getLine(PosType pos) {
    return pos/16;
}

PosType Board::startLine(PosType pos) {
    return pos*16;
}

PosType Board::getColumn(PosType pos) {
    return  pos & 7;
}

bool Board::onInitPawnLine(PosType pos, bool color) {
    return getLine(pos) == (color?6:1);
}

bool Board::onPromotionLine(PosType pos, bool color) {
    return getLine(pos) == (color?1:6);
}

void Board::clearSquares() {
    memset(squares128, 0, sizeof(squares128));
}

PosType Board::add(char sym, PosType pos) {
    squares128[pos] = PieceKind::symToSquare(sym);
    pos++;
    return pos;
}

PosType Board::add(char sym, PosType pos, int count) {
    SquareType square = PieceKind::symToSquare(sym);
    for (int i=0; i<count; i++) {
        squares128[pos] = square;
        pos++;
    }
    return pos;
}

PosType Board::newLine(PosType pos) {
    PosType curr = getLine(pos);
    curr--;
    return startLine(curr);
}

char Board::getSymAt(PosType pos) {
    SquareType square = squares128[pos];
    return PieceKind::getSym(square.piece, square.color);
}

void Board::moveSquare(PosType from, PosType to) {
    squares128[to] = squares128[from];
    squares128[from] = {0, 0};
}

//reverse from and to, this is for takeback
void Board::moveSquareWithRestore(PosType to, PosType from, PieceType captured, bool color) {
    squares128[from] = squares128[to];
    squares128[to].piece = captured;
    squares128[to].color = color;
}

void Board::moveSquareWithRestoreEP(PosType to, PosType from, PosType capturedEP, PieceType captured, bool color) {
    squares128[from] = squares128[to];
    squares128[to] = {0, 0};
    squares128[capturedEP] = {captured, color};
}

void Board::remove(PosType pos) {
    squares128[pos] = {0, 0};
}

void Board::promote(PosType pos, PieceType promoteTo) {
    squares128[pos].piece = promoteTo;
}

SquareType Board::get(PosType pos) {
    return squares128[pos];
}

void Board::set(int pos, SquareType square) {
    squares128[pos] = square;
}

void Board::print() {
    for (int row=7; row>=0; row--) {
        int start=row*16;
        char c = row+'1';
        std::cout <<  c << " |";
        for (int j=0; j<8; j++)
            std::cout << getSymAt(PosType(start+j)) << " ";
        std::cout << std::endl;
    }
    std::cout << "  ----------------"<< std::endl;
    std::cout << "   A B C D E F G H"<< std::endl;
    std::cout << std::endl;
}

std::string Board::getFen() {
    std::stringstream ss;
    for (int row=7; row>=0; row--) {
        int start = row * 16;
        if (row!=7)
            ss << "/";
        int emptyLen = 0;
        for (int j=0; j<8; j++) {
            char sym  = getSymAt(PosType(start+j));
            if (sym=='.')
                emptyLen++;
            else {
                if (emptyLen>0) {
                    ss << emptyLen;
                    emptyLen = 0;
                }
                ss << sym;
            }
        }
        if (emptyLen>0) {
            ss << emptyLen;
        }
    }
    ss << ' ';
    if (turnColor)
        ss << 'b';
    else
        ss << 'w';
    ss << ' ';
    if (castling & CASTLING_SHORT_W)
        ss << 'K';
    else
        ss << '-';
    if (castling & CASTLING_LONG_W)
        ss << 'Q';
    else
        ss << '-';
    if (castling & CASTLING_SHORT_B)
        ss << 'k';
    else
        ss << '-';
    if (castling & CASTLING_LONG_B)
        ss << 'q';
    else
        ss << '-';

    ss << ' ';
    if (enPassantPos<0)
        ss << '-';
    else
        ss << fromPos(enPassantPos);
    return ss.str();
}

void Board::printFen() {
    std::cout << getFen() << std::endl;
}

void Board::parseFen(std::string fen) {
    PosType writePos;
    writePos = 7 * 16;
    int pos;
    for (pos = 0; pos < fen.length();) {
        char c = fen[pos];
        int number = 0;
        if (isdigit(c)) {
            while (isdigit(c)) {
                number = 10 * number + (c - '0');
                pos++;
                c = fen[pos];
            }
            if (number < 1) throw std::exception();
            writePos = add('.', writePos, number);
        } else {
            if (isalpha(c)) writePos = add(c, writePos);
            else if (c == '/') writePos = newLine(writePos);
            else if (c == ' ') {
                pos++;
                break;
            } else throw std::exception();
            pos++;
        }
    }
    if (fen[pos] == 'b')
        turnColor = true;
    else if (fen[pos] == 'w')
        turnColor = false;
    else
        throw std::exception();
    pos+=2;
    castling = 0;
    enPassantPos = -1;
    while (pos<fen.size() && fen[pos]!=' ') {
        switch (fen[pos]) {
            case 'K':
                castling |= CASTLING_SHORT_W;
                break;
            case 'Q':
                castling |= CASTLING_LONG_W;
                break;
            case 'k':
                castling |= CASTLING_SHORT_B;
                break;
            case 'q':
                castling |= CASTLING_LONG_B;
                break;
        }
        pos++;
    }
    if (pos>=fen.size()) return;
    assert(fen[pos]==' ');
    pos++;
    if (fen[pos]=='-')
        enPassantPos = -1;
    else {
        enPassantPos = toPos(fen[pos], fen[pos+1]);
    }
}


PosType Board::toPos(char col, char row) {
    return (tolower(col)-'a')+16*(row-'1');
}

std::string Board::fromPos(PosType pos) {
    std::string ret;
    ret.resize(2);
    ret[0] = 'a'+(pos % 16);
    ret[1] = '1'+(pos / 16);
    return ret;
}

uint32_t Board::hash(bool alsoFlags) {
    uint32_t hash = XXH32(squares128, sizeof(squares128), 0);
    if (alsoFlags) {
        hash = XXH32(&castling, sizeof(castling), hash);
        hash = XXH32(&enPassantPos, sizeof(enPassantPos), hash);
        hash = XXH32(&turnColor, sizeof(turnColor), hash);
    }
    return hash;
}

void Board::fromBoard64(const SquareType *squares64) {
    for (int row=0; row<8; row++) {
        int start64 = 8*row;
        int start128 = 16*row;
        for (int j=0; j<8; j++)
            squares128[start128 + j] = squares64[start64 + j];
    }
}

void Board::toBoard64(SquareType *squares64) {
    for (int row=0; row<8; row++) {
        int start64 = 8*row;
        int start128 = 16*row;
        for (int j=0; j<8; j++)
            squares64[start64+j] = squares128[start128 + j];
    }
}

