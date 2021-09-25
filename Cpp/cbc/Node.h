//
// Created by andrzej on 9/23/21.
//
#pragma once
#include <vector>
#include "../common/Move.h"
#include "Context.h"

namespace ochess::cbc {
    struct Node {
        ~Node();

        Node(Node *parent, Context *context) : parent(parent), context(context) {}

        Node *parent = nullptr;
        Context *context = nullptr;
        int64_t summary = -1;

        Node *lastChild();
        void addChild(Move move, int64_t summary);
        void sortChildren();
        static bool node_sorter(Node const *lhs, Node const *rhs) {
            return Move::move_sorter(lhs->move, rhs->move);
        }
        void compareTo(Node *testNode);

    private:
        Move move;
        std::vector<Node *> children;
    };
}