//
// Created by andrzej on 9/24/21.
//

#include <iostream>
#include "Context.h"

using namespace ochess::cbc;

void Context::print() {
    board->print();
    for (int i=0; i<ply; i++) {
        if (i>0) std::cout << ",";
        std::cout << hist[i].toHuman(board);
    }
    std::cout << std::endl;
}
