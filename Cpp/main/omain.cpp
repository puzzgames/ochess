#include <iostream>
#include <chrono>
#include "Searcher.h"
#include "Dict.h"

using namespace ochess::main;

extern FILE *myfile;
int main() {
    BoardGen *board = new BoardGen();
    Searcher *searcher = new Searcher(board);
    Dict *dict = new Dict(board, searcher);
    //board->parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board->parseFen("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    using ChronoType = std::chrono::time_point<std::chrono::high_resolution_clock>;
    ChronoType startTimer = std::chrono::high_resolution_clock::now();
    searcher->count = 0;
    char namebuf[64];
    sprintf(namebuf, "%d-%d_test.cbc", partDepth, fullDepth);
    myfile = fopen(namebuf, "w");
    fprintf(myfile, "%d/%d\n", partDepth, fullDepth);
    fprintf(myfile, "%s\n", board->getFen().c_str());
    searcher->MiniMax(dict, fullDepth);
    fclose(myfile);
    ChronoType endTimer = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimer - startTimer).count();
    printf("duration=%ld count=%ld",duration,searcher->count);
    delete dict;
    delete searcher;
    delete board;
    return 0;
}
