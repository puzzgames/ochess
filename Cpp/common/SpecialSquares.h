//
// Created by andrzej on 9/19/21.
//

#ifndef BITSZACHY_SPECIALSQUARES_H
#define BITSZACHY_SPECIALSQUARES_H

static const uint8_t A1 = 0;//white rook to long castling
static const uint8_t B1 = 1;//must be empty for long castling
static const uint8_t C1 = 2;//destination white king after logn castling
static const uint8_t D1 = 3;//destination white rook after long castling
static const uint8_t E1 = 4;//white king init position
static const uint8_t F1 = 5;//destination white rook after short castling
static const uint8_t G1 = 6;//destination white king after short castling
static const uint8_t H1 = 7;//white rook to short castling

static const uint8_t A8 = 7*16+0;//black rook to long castling
static const uint8_t B8 = 7*16+1;//must be empty for long castling
static const uint8_t C8 = 7*16+2;//destination black king after logn castling
static const uint8_t D8 = 7*16+3;//destination black rook after long castling
static const uint8_t E8 = 7*16+4;//black king init position
static const uint8_t F8 = 7*16+5;//destination black rook after short castling
static const uint8_t G8 = 7*16+6;//destination black king after short castling
static const uint8_t H8 = 7*16+7;//black rook to short castling



#endif //BITSZACHY_SPECIALSQUARES_H
