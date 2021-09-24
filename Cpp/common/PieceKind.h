//
// Created by andrzej on 9/18/21.
//

#ifndef BITSZACHY_PIECEKIND_H
#define BITSZACHY_PIECEKIND_H

#include <cstdint>
#include <string>

namespace ochess::common {
    using PieceType = uint8_t;
    using BitType = uint8_t;
    using FlagsType = uint8_t;

//below moveKinds are exclusive, not kind
/*const FlagsType Moveflag_promote = 1;
const FlagsType Moveflag_doublePawnInit = 2;
const FlagsType Moveflag_enPassant = 4;
const FlagsType Moveflag_castling = 8;
 */
    const FlagsType MoveKind_simple = 0;
    const FlagsType MoveKind_promote = 1;
    const FlagsType MoveKind_doublePawnInit = 3;
    const FlagsType MoveKind_enPassant = 4;
    const FlagsType MoveKind_castling = 5;


    struct SquareType {
        PieceType piece;
        bool color;

        SquareType() : piece(0), color(false) {};

        SquareType(PieceType piece, bool color) : piece(piece), color(color) {};
    };

    class PieceKind {
    protected:
        //8x16 boards
        constexpr static int delta90degree[] = {1, -1, 16, -16};
        constexpr static int delta45degree[] = {-17, -15, 15, 17};
        constexpr static int deltaKnight[] = {-33, -31, -18, -14, 14, 18, 31, 33};
        static std::string piecetypeToSymArray[2];
    public:
        static constexpr PieceType EMPTY = 0;
        static constexpr PieceType PAWN = 1;
        static constexpr PieceType KNIGHT = 2;
        static constexpr PieceType BISHOP = 3;
        static constexpr PieceType ROOK = 4;
        static constexpr PieceType QUEEN = 5;
        static constexpr PieceType KING = 6;

        static char getSym(PieceType type, bool color);

        bool color;
        static const BitType BITMASK_COLOR = 1; //don't change , turnColor iniied by bool
        static const BitType BITMASK_90 = 2;
        static const BitType BITMASK_45 = 4;
        static const BitType BITMASK_FAR = 8;
        static const BitType BITMASK_KNIGHT = 16;
        static const BitType BITMASK_PAWN = 32;
        BitType pieceMask;
        PieceType pieceType;
        std::string pieceSym;

        static SquareType symToSquare(char sym);

        static PieceType symToType(char sym);

        virtual ~PieceKind() = default;
    };
}

#endif //BITSZACHY_PIECEKIND_H
