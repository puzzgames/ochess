//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_BOARD_H
#define BITSZACHY_BOARD_H

#include <cstdint>
#include <string>
#include "PieceKind.h"

namespace ochess::common {
    using PosType = int8_t;

    const static int CASTLING_LONG_W = 1;
    const static int CASTLING_SHORT_W = 2;
    const static int CASTLING_LONG_B = 4;
    const static int CASTLING_SHORT_B = 8;

    class Board {
    protected:
        SquareType squares[128];
    public:
        Board();
        ~Board();
        void toBoard64(SquareType squares64[]);
        void fromBoard64(const SquareType squares64[]);
        bool turnColor = false;
        static PosType bits6to7(PosType pos);
        static PosType bits7to6(PosType pos);
        static PosType getLine(PosType pos);
        static PosType startLine(PosType pos);
        static PosType getColumn(PosType pos);
        static bool onBoard(PosType pos);
        bool emptyOrOpposite(bool mycolor, PosType pos);
        bool opposite(PosType pos, bool mycolor);
        bool oppositeOnBoard(PosType pos, bool mycolor);
        bool nonempty(PosType pos);
        bool empty(PosType pos);
        bool empty(PosType pos, int num);
        bool emptyOnBoard(PosType pos);
        static bool onInitPawnLine(PosType pos, bool color);
        static bool onPromotionLine(PosType pos, bool color);
        PosType enPassantPos = 1;
        uint8_t castling = 15;
        void clearSquares();
        PosType add(char sym, PosType pos);
        PosType add(char sym, PosType pos, int count);
        PosType newLine(PosType pos);
        char getSymAt(PosType pos);
        void moveSquare(PosType from, PosType to);
        void moveSquareWithRestore(PosType to, PosType from, PieceType captured, bool color);
        void moveSquareWithRestoreEP(PosType to, PosType from, PosType capturedEP, PieceType captured, bool color);
        void remove(PosType pos);
        void promote(PosType pos, PieceType promoteTo);
        SquareType get(PosType pos);
        void set(int pos, SquareType square);
        void print();
        std::string getFen();
        void printFen();
        void parseFen(std::string fen);
        static PosType toPos(char col, char row);
        static std::string fromPos(PosType pos);
        uint32_t hash(bool alsoFlags = true);
    };
}

#endif //BITSZACHY_BOARD_H
