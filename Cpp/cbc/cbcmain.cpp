//chess branch comparer
#include <iostream>
#include "Tree.h"

using namespace ochess::cbc;

int main() {
    Tree trust(false);
    Tree test(true);
    trust.readCBC("3-6_trust.cbc");
    test.readCBC("3-6_test.cbc");
    if (trust.fullDepth!=test.fullDepth) throw std::exception();
    if (trust.partDepth!=test.partDepth) throw std::exception();
    if (trust.fen!=test.fen) {
        int len1 = trust.fen.size();
        int len2 = test.fen.size();
        if (len1!=len2)
            printf("fens len diff %d - %d\n",len1,len2);
        else
            printf("fens diffs\n");
            for (int i=0; i<len1; i++)
                if (trust.fen[i]!=test.fen[i]) {
                    std::cout << trust.fen << std::endl;
                    std::cout << test.fen << std::endl;
                    for (int j=0; j<i; j++)
                        std::cout << " ";
                    std::cout << "^" << std::endl;;
                }
        exit(1);
    }
    trust.compareTo(&test);
    return 0;
}
