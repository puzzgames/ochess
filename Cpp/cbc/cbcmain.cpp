//chess branch comparer
#include <iostream>
#include "Tree.h"

using namespace ochess::cbc;

int main() {
    Tree trust(false);
    Tree test(true);
    trust.readCBC("trust3-6.cbc");
    test.readCBC("test3-6.cbc");
    trust.compareTo(&test);
    return 0;
}
