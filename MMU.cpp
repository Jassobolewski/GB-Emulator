//
// Created by Jas Sobolewski on 2025-06-21.
//

#include "MMU.h"

void MMU::loadRom(const std::vector<uint8_t>& romdata) {
    size_t i = 0;
    for(auto it : romdata)
    {
        if (i > 0XFFFF)
            std::println("Out of bounds");

        memoryMap[i] == it;
        i++;
    }

}

uint8_t MMU::returnAddress(uint16_t address) {
    return memoryMap[address];
}

void MMU::writeToAddress(uint16_t address, uint8_t value) {
    if (address == 0xFF01) {
       std::cout << (value) << std::endl;
    }
}
