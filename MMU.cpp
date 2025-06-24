//
// Created by Jas Sobolewski on 2025-06-21.
//

#include "MMU.h"

void MMU::loadRom(const std::vector<uint8_t>& romData) {
    size_t i = 0;
    for(auto it : romData)
    {
        if(i > 0x7FFF)//the end of the rom bank https://gbdev.io/pandocs/Memory_Map.html
        {
            std::println("Out of bounds");
            break;
        }
        memoryMap[i] = it;
        i++;
    }

}

uint8_t MMU::returnAddress(uint16_t address) {
    return memoryMap[address];
}

void MMU::writeToAddress(uint16_t address, uint8_t value) {
    if (address == 0xFF01) {//Serial port
       std::cout << (value) << std::endl;
    }

    if(address > 0x7FFF)//write to address outside of rom area
    {
        memoryMap[address] = value;
    }
    else
    {
        std::println("Denied Access");
    }
}

void MMU::writeToAddress(uint16_t address, uint16_t value) {
    if (address == 0xFF01) {//Serial port
        std::cout << (value) << std::endl;
    }

    if(address > 0x7FFF)//write to address outside of rom area
    {
        memoryMap[address] = value;
    }
    else
    {
        std::println("Denied Access");
    }
}
