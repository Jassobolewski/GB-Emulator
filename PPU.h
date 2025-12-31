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

    uint16_t writeVram(uint16_t address, uint8_t value);

    uint16_t writeOAM(uint16_t address, uint8_t value);

    uint16_t writeRegister(uint16_t address, uint8_t value);

    uint16_t readVram(uint16_t address);

    uint16_t readOAM(uint16_t address);

    uint16_t readRegister(uint16_t address);

};


#endif //GB_EMULATOR_PPU_H
