//
// Created by andrzej on 9/23/21.
//

#pragma once

#include <string>
#include "../common/Move.h"
#include "Node.h"
#include "Context.h"

namespace ochess::cbc {
    class Tree {
        bool test = false;
        Node *root, *currentOwner;
        int currentLevel = 1;
        Context *context = nullptr;
    public:
        explicit Tree(bool test);
        ~Tree();
        void sort();
        void readCBC(std::string filename);
        void add(int level, Move move, int64_t summary);
        void compareTo(Tree *testTree);

        std::string fen;
        int partDepth;
        int fullDepth;
    };
}
