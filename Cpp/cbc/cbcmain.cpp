//chess branch comparer
#include <iostream>
#include "Tree.h"

using namespace ochess::cbc;

int main() {
    Tree trust(false);
    Tree test(true);
    trust.readCBC("trust3-6.cbc");
    test.readCBC("test3-6.cbc");
    if (trust.fullDepth!=test.fullDepth) throw std::exception();
    if (trust.partDepth!=test.partDepth) throw std::exception();
    if (trust.fen!=test.fen) throw std::exception();
    trust.compareTo(&test);
    return 0;
}
