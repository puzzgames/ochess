//
// Created by andrzej on 9/21/21.
//

#pragma once
#include <cstdint>
#include <cassert>
#include "strutils.h"
#include "PieceKind.h"
#include "Board.h"

namespace ochess::common {
    using PosType = int8_t;
    using PieceType = uint8_t;

    using BitType = uint8_t;

    struct Move {
        Move();

        bool operator<(const Move &rhs);

        bool operator>(const Move &rhs);

        Move(PosType from, PosType to, PieceType promoteTo = PieceKind::EMPTY);

        Move(std::string humanString, Board *board);

        std::string toHuman(Board *board);

        PosType from;
        PosType to;

        union {
            PieceType captured;
            PosType rookFrom;
        };
        union {
            PieceType promoteTo;
            PosType captureEPPos;
            PosType rookTo;
        };
        PosType initEPPos;
        FlagsType kind: 4;
        FlagsType justCastlingDisabled: 4;//just delete possiblities
        short scores;

        static bool move_sorter(Move const &lhs, Move const &rhs);

        void addOtherFlags(Board *board);

        void addOtherFields(Board *board);

        void makeMove(Board *board);

        void takeBack(Board *board);

        std::string toDebug();
    };
}
