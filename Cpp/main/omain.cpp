#include <iostream>
#include <chrono>
#include "Searcher.h"
#include "Dict.h"

using namespace ochess::main;

extern FILE *myfile;
int main() {
    BoardGen board;
    Searcher searcher(&board);
    Dict dict(&board, &searcher);
    //board.parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board.parseFen("rnbqkbnr/1ppppppp/p7/P7/8/8/1PPPPPPP/RNBQKBNR b KQkq -");
    using ChronoType = std::chrono::time_point<std::chrono::high_resolution_clock>;
    ChronoType startTimer = std::chrono::high_resolution_clock::now();
    searcher.count = 0;
    char namebuf[64];
    sprintf(namebuf, "test%d-%d.cbc", partDepth, fullDepth);
    myfile = fopen(namebuf, "w");
    fprintf(myfile, "%d/%d\n", partDepth, fullDepth);
    fprintf(myfile, "%s\n", board.getFen().c_str());
    searcher.MiniMax(&dict, fullDepth);
    fclose(myfile);
    ChronoType endTimer = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimer - startTimer).count();
    printf("duration=%ld count=%ld",duration,searcher.count);
    return 0;
}
