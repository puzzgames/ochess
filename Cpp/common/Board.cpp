//
// Created by andrzej on 9/18/21.
//
#include <cstring>
#include <iostream>
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
    SquareType square = squares[pos];
    return (square.piece==0) || (square.color != mycolor);
}

bool Board::opposite(PosType pos, bool mycolor) {
    SquareType square = squares[pos];
    return (square.piece!=0) && (square.color != mycolor);
}



bool Board::nonempty(PosType pos) {
    return squares[pos].piece!=0;
}

bool Board::empty(PosType pos) {
    return squares[pos].piece==0;
}

bool Board::empty(PosType pos, int num) {
    for (int i=pos; i<pos+num; i++)
        if (squares[i].piece!=0)
            return false;
    return true;
}

//7 bit is used in 128 squares board, 6 in 64 squares binary board
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
    memset(squares,0, sizeof(squares));
}

PosType Board::add(char sym, PosType pos) {
    squares[pos] = PieceKind::symToSquare(sym);
    pos++;
    return pos;
}

PosType Board::add(char sym, PosType pos, int count) {
    SquareType square = PieceKind::symToSquare(sym);
    for (int i=0; i<count; i++) {
        squares[pos] = square;
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
    SquareType square = squares[pos];
    return PieceKind::getSym(square.piece, square.color);
}

void Board::moveSquare(PosType from, PosType to) {
    squares[to] = squares[from];
    squares[from] = {0,0};
}

//reverse from and to, this is for takeback
void Board::moveSquareWithRestore(PosType to, PosType from, PieceType captured, bool color) {
    squares[from] = squares[to];
    squares[to].piece = captured;
    squares[to].color = color;
}

void Board::remove(PosType pos) {
    squares[pos] = {0,0};
}

void Board::promote(PosType pos, PieceType promoteTo) {
    squares[pos].piece = promoteTo;
}

SquareType Board::get(PosType pos) {
    return squares[pos];
}

void Board::set(int pos, SquareType square) {
    squares[pos] = square;
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

void Board::printFen() {
    for (int row=7; row>=0; row--) {
        int start = row * 16;
        if (row!=7)
            std::cout << "/";
        int emptyLen = 0;
        for (int j=0; j<8; j++) {
            char sym  = getSymAt(PosType(start+j));
            if (sym=='.')
                emptyLen++;
            else {
                if (emptyLen>0) {
                    std::cout << emptyLen;
                    emptyLen = 0;
                }
                std::cout << sym;
            }
        }
        if (emptyLen>0) {
            std::cout << emptyLen;
        }
    }
    std::cout << ' ';
    if (turnColor)
        std::cout << 'b';
    else
        std::cout << 'w';
    std::cout << ' ';
    if (castling & CASTLING_SHORT_W)
        std::cout << 'K';
    else
        std::cout << '-';
    if (castling & CASTLING_LONG_W)
        std::cout << 'Q';
    else
        std::cout << '-';
    if (castling & CASTLING_SHORT_B)
        std::cout << 'k';
    else
        std::cout << '-';
    if (castling & CASTLING_LONG_B)
        std::cout << 'q';
    else
        std::cout << '-';

    std::cout << ' ';
    if (enPassantPos<=0)
        std::cout << '-';
    else
        std::cout << fromPos(enPassantPos);
    std::cout << std::endl;
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
    if (fen[pos] == 'K')
        castling |= CASTLING_SHORT_W;
    if (fen[pos+1] == 'Q')
        castling |= CASTLING_LONG_W;
    if (fen[pos+2] == 'k')
        castling |= CASTLING_SHORT_B;
    if (fen[pos+3] == 'q')
        castling |= CASTLING_LONG_B;
    pos += 5;
    if (fen[pos]=='-')
        enPassantPos = 0;
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
    uint32_t hash = XXH32(squares, sizeof(squares), 0);
    if (alsoFlags) {
        hash = XXH32(&castling, sizeof(castling), hash);
        hash = XXH32(&enPassantPos, sizeof(enPassantPos), hash);
        hash = XXH32(&turnColor, sizeof(turnColor), hash);
    }
    return hash;
}
