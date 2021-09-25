//
// Created by andrzej on 9/23/21.
//

#include <fstream>
#include <iostream>
#include "Tree.h"
#include "../common/Move.h"

using namespace std;
using namespace ochess::common;
using namespace ochess::cbc;

Tree::Tree(bool test):test(test) {
    board.parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //board.parseFen("rnbqkbnr/p1pppppp/8/1p6/P7/8/1PPPPPPP/RNBQKBNR w KQkq -");
    context.board = &board;
    root = new Node(nullptr, &context);
    currentOwner = root;
}

void Tree::readCBC(string filename) {
    ifstream infile(filename);
    if (infile.eof()) throw exception();
    int lineCnt = 0;
    bool good;
    do {
        string line;
        good = getline(infile, line).good();
        if (!good && line == "") break;
        lineCnt++;
        int pos = line.find('.');
        string numStr = line.substr(0,pos);
        int level = stoi(numStr);
        pos++;
        while (line[pos]==' ') pos++;
        int pos2 = line.find("=>");
        std::string moveStr;
        int64_t summary = -1;
        if (pos2!=string::npos) {
            int pos3 = pos2+2;
            numStr = line.substr(pos3);
            summary = stoi(numStr);
            while (line[pos2 - 1] == ' ') pos2--;
            moveStr = line.substr(pos,pos2-pos);
        } else {
            moveStr = line.substr(pos);
        }
        Move move(moveStr, &board);
        add(level,move, summary);
    } while (good);
    if (lineCnt==0) throw exception();
    sort();
}

Tree::~Tree() {
    delete root;
}

void Tree::add(int level, Move move, int64_t summary) {
    if (level>currentLevel) {
        if (level==(currentLevel+1))
            currentOwner = currentOwner->lastChild();
        else throw std::exception();
    } else if (level<currentLevel) {
        for (int i=level; i<currentLevel; i++)
            currentOwner = currentOwner->parent;
    }
    currentLevel = level;
    currentOwner->addChildren(move, summary);
}

void Tree::sort() {
    root->sortChildren();
}

void Tree::compareTo(Tree *testTree) {
    root->compareTo(testTree->root);
}
