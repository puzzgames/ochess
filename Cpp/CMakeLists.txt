cmake_minimum_required(VERSION 3.20)
project(ochess)

set(CMAKE_CXX_STANDARD 17)

add_definitions("-Werror=return-type")

add_executable(ochess main/omain.cpp common/PieceKind.cpp common/PieceKind.h
        pieces/KindQueen.cpp pieces/KindQueen.h pieces/KindKing.cpp pieces/KindKing.h pieces/KindRook.cpp
        pieces/KindRook.h pieces/KindBishop.cpp pieces/KindBishop.h pieces/KindKnight.cpp pieces/KindKnight.h
        pieces/KindPawn.cpp pieces/KindPawn.h main/MoveList.cpp main/MoveList.h common/Board.cpp common/Board.h
        common/SpecialSquares.h main/Dict.cpp main/Dict.h main/PieceGen.cpp
        main/PieceGen.h main/Searcher.cpp main/Searcher.h common/Move.h main/BoardGen.cpp main/BoardGen.h
        common/Move.cpp common/xxHash.cpp common/xxHash.h)

add_executable(cbc cbc/cbcmain.cpp cbc/Node.cpp cbc/Node.h cbc/Tree.cpp cbc/Tree.h common/PieceKind.cpp
        common/Move.cpp common/Board.cpp cbc/Context.cpp cbc/Context.h common/xxHash.cpp)

