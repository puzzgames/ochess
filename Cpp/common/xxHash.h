//
// Created by andrzej on 9/24/21.
//

#ifndef BITSZACHY_XXHASH_H
#define BITSZACHY_XXHASH_H

#include <cstdint>
#include <cstddef>

uint32_t XXH32(void const *const input, size_t const length, uint32_t const seed);

#endif //BITSZACHY_XXHASH_H
