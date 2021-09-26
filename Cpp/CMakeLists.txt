cmake_minimum_required(VERSION 3.20)
project(ochess)

set(CMAKE_CXX_STANDARD 17)

add_definitions("-Werror=return-type")

add_executable(ochess main/omain.cpp common/PieceKind.cpp common/PieceKind.h
        pieces/Queen.cpp pieces/Queen.h pieces/King.cpp pieces/King.h pieces/Rook.cpp
        pieces/Rook.h pieces/Bishop.cpp pieces/Bishop.h pieces/Knight.cpp pieces/Knight.h
        pieces/Pawn.cpp pieces/Pawn.h main/MoveList.cpp main/MoveList.h common/Board.cpp common/Board.h
        common/SpecialSquares.h main/Dict.cpp main/Dict.h main/PieceGen.cpp
        main/PieceGen.h main/Searcher.cpp main/Searcher.h common/Move.h main/BoardGen.cpp main/BoardGen.h
        common/Move.cpp common/xxHash.cpp common/xxHash.h)

add_executable(cbc cbc/cbcmain.cpp cbc/Node.cpp cbc/Node.h cbc/Tree.cpp cbc/Tree.h common/PieceKind.cpp
        common/Move.cpp common/Board.cpp cbc/Context.cpp cbc/Context.h common/xxHash.cpp bit/Radius.cpp bit/Radius.h)

