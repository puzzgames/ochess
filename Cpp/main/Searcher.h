//
// Created by andrzej on 9/20/21.
//

#ifndef BITSZACHY_SEARCHER_H
#define BITSZACHY_SEARCHER_H

#include "MoveList.h"
#include "BoardGen.h"
#include "Dict.h"

namespace ochess::main {
    static int fullDepth = 3;
    static int partDepth = 3;

    class Searcher : public MoveList {
        BoardGen *board;
    public:
        Searcher(BoardGen *board);

        void MiniMax(Dict *dict, int depth);

        long count = 0;
        long thrCounter = 0;

        void addSimpleMove(PosType from, PosType to, PieceType captured, bool touchCastling) override;

        void addPromotionsMultiMove(PosType from, PosType to, PieceType captured) override;

        void addPromotionMove(PosType from, PosType to, PieceType captured, PieceType promoteTo);

        void addDoublePawnMove(PosType from, PosType to, PosType oneStepPos) override;

        void addEnPassantMove(PosType from, PosType to, PosType capturedPos) override;

        void addCastling(PosType from, PosType to, PosType rookFrom, PosType rookTo) override;

        void MakeMove(int index);

        void takeBack();
    };
}

#endif //BITSZACHY_SEARCHER_H
