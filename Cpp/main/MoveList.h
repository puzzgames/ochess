//
// Created by andrzej on 9/18/21.
//
#ifndef BITSZACHY_MOVELIST_H
#define BITSZACHY_MOVELIST_H

#include <vector>
#include "../common/Move.h"

using namespace ochess::common;

namespace ochess::main {
    class MoveList {
    protected:
        static const int MaxLevels = 40;
        static const int MaxMoves = 300;
        Move **levels;
        Move *level;
        int levsize[MaxLevels];
        Move hist[MaxLevels];
        int ply = 0;
    public:
        MoveList();

        ~MoveList();

        virtual void addSimpleMove(PosType from, PosType to, PieceType captured, bool touchCastling) = 0;

        virtual void addPromotionsMultiMove(PosType from, PosType to, PieceType captured) = 0;

        virtual void addDoublePawnMove(PosType from, PosType to, PosType oneStepPos) = 0;

        virtual void addEnPassantMove(PosType from, PosType to, PosType capturedPos) = 0;

        virtual void addCastling(PosType from, PosType to, PosType rookFrom, PosType rookTo) = 0;
    };
}

#endif //BITSZACHY_MOVELIST_H
