//
// Created by Jas Sobolewski on 2025-08-28.
//

#include "PPU.h"

std::array<uint8_t, 64> PPU::tileDecoder(const std::vector<uint8_t> &tile_data) {

    std::array<uint8_t, 64> pixels{};
    // A tile is 8 rows of pixels. Each row takes 2 bytes.
    for (int y = 0; y < 8; ++y) {
        // Get the two bytes for the current row.
        uint8_t byte1 = tile_data[y * 2];
        uint8_t byte2 = tile_data[y * 2 + 1];

        // Each bit in the two bytes corresponds to one pixel in the row.
        for (int x = 0; x < 8; ++x) {
            // The color of a pixel is determined by two bits: one from each byte.
            // We look at the bits from left to right (7 down to 0).
            int bit_pos = 7 - x;

            // Get bit from the first byte (this is the low bit of the color ID)
            uint8_t color_bit0 = (byte1 >> bit_pos) & 1;
            // Get bit from the second byte (this is the high bit of the color ID)
            uint8_t color_bit1 = (byte2 >> bit_pos) & 1;

            // Combine the two bits to get the final color ID (0, 1, 2, or 3).
            uint8_t color_id = (color_bit1 << 1) | color_bit0;

            // Store it in our 8x8 pixel grid.
            pixels[y * 8 + x] = color_id;
        }
    }
    return pixels;
}

uint8_t PPU::writeVram(uint16_t address, uint8_t value) {
    return 0;
}

uint8_t PPU::writeOAM(uint16_t address, uint8_t value) {
    return 0;
}

uint8_t PPU::writeRegister(uint16_t address, uint8_t value) {
    return 0;
}

uint8_t PPU::readVram(uint16_t address) {
    return 0;
}

uint8_t PPU::readOAM(uint16_t address) {
    return 0;
}

uint8_t PPU::readRegister(uint16_t address) {
    return 0;
}
