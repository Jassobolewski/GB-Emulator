//
// Created by Jas Sobolewski on 2025-08-28.
//

#ifndef GB_EMULATOR_PPU_H
#define GB_EMULATOR_PPU_H


#include <array>
#include <vector>

class PPU {

public:

    std::array<uint8_t, 64> tileDecoder(const std::vector<uint8_t>& tile_data);

};


#endif //GB_EMULATOR_PPU_H
