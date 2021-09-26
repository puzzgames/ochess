//
// Created by andrzej on 9/26/21.
//

#ifndef OCHESS_RADIUS_H
#define OCHESS_RADIUS_H

#include "../common/PieceKind.h"

using namespace ochess::common;

namespace ochess::bit {
    class Radius {
        SquareType squares64[64];
        uint8_t radiusMaps[2][64];
    };
}

#endif //OCHESS_RADIUS_H
