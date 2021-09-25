//
// Created by andrzej on 9/23/21.
//

#include "Node.h"
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;
using namespace ochess::common;
using namespace ochess::cbc;

Node::~Node() {
    for (auto child: children)
        delete child;
}

Node *Node::lastChild() {
    return children[children.size() - 1];
}

void Node::addChild(Move move, int64_t summary) {
    Node *child = new Node(this, context);
    child->move = move;
    child->summary = summary;
    children.push_back(child);
}

void Node::sortChildren() {
    std::sort(children.begin(), children.end(), &node_sorter);
    for (auto child: children)
        child->sortChildren();
}

void Node::compareTo(Node *testNode) {
    int i0 = 0, i1 = 0;
    while (i0 < children.size() && i1 < testNode->children.size()) {
        if (children[i0]->move < testNode->children[i1]->move) {
            context->print();
            cout << "deleted " << children[i0]->move.toHuman(context->board) << endl;;
            cout << "jest  " << testNode->children[i1]->move.toHuman(context->board)
                 << " = " << testNode->children[i1]->move.toDebug() << endl;;
            i0++;
        } else if (children[i0]->move > testNode->children[i1]->move) {
            context->print();
            cout << "added " << testNode->children[i1]->move.toHuman(context->board) <<
                 " = " << testNode->children[i1]->move.toDebug()
                 << " hash= " << context->board->hash() << endl;;
            i1++;
            exit(0);
        } else {
            context->hist[context->ply] = children[i0]->move;
            Move move = children[i0]->move;
            if (context->ply == 4 && move.from == 16 && move.to == 48) {
                context->cnt++;
                if (context->cnt == 25540) {
                    context->print();
                    cout << "make move" << move.toDebug() << move.toHuman(context->board) << endl;
                }
            }
            children[i0]->move.makeMove(context->board);
            //context->print();
            context->ply++;
            bool savolor = context->board->turnColor;
            children[i0]->compareTo(testNode->children[i1]);
            if (savolor != context->board->turnColor) {
                printf("turn bad\n");
                exit(1);
            }
            uint64_t sum1, sum2;
            sum1 = children[i0]->summary;
            sum2 = testNode->children[i1]->summary;
            if (sum1 != sum2) {
                printf("summary mismatch %ld <-> %ld (%ld)\n", sum1, sum2, sum2 - sum1);
                context->print();
                context->board->printFen();
                cout << endl;
            }
            context->ply--;
            children[i0]->move.takeBack(context->board);
            i0++;
            i1++;
        }
    }
    while (i0 < children.size()) {
        context->print();
        cout << "deleted " << children[i0]->move.toHuman(context->board) << endl;
        i0++;
    }
    while (i1 < testNode->children.size()) {
        context->print();
        cout << "added " << testNode->children[i1]->move.toHuman(context->board) << endl;;
        i1++;
    }
}
