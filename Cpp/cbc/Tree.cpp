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
}

void Tree::readCBC(string filename) {
    ifstream infile(filename);
    if (infile.eof()) throw exception();
    int lineCnt = 0;
    string line;
    bool good;
    good = getline(infile, line).good();
    if (!good) throw exception();
    int pos = line.find('/');
    if (pos==string::npos) throw exception();
    partDepth = stoi(line.substr(0,pos));
    fullDepth = stoi(line.substr(pos+1));
    good = getline(infile, fen).good();
    context = new Context(fen);
    if (!good) throw exception();
    root = new Node(nullptr, context);
    currentOwner = root;
    do {
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
        Move move(moveStr, context->board);
        add(level,move,summary);
    } while (good);
    if (lineCnt==0) throw exception();
    sort();
}

Tree::~Tree() {
    delete root;
    delete context;
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
    currentOwner->addChild(move, summary);
}

void Tree::sort() {
    root->sortChildren();
}

void Tree::compareTo(Tree *testTree) {
    root->compareTo(testTree->root);
    if (context==nullptr)
        throw new std::exception();
    if (context->addCnt==0 && context->delCnt==0 && context->mismatchCnt==0)
        printf("Congratulations! Files are identical.");
}
