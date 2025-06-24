//
// Created by Jas Sobolewski on 2025-06-21.
//

#ifndef GB_EMULATOR_MMU_H
#define GB_EMULATOR_MMU_H
#include <cstdint>
#include <vector>
#include <print>
#include <iostream>

class MMU {
public:
    uint8_t memoryMap[0xFFFF] = {0}; // Initialize to all zeros

    void loadRom(const std::vector<uint8_t>& romData);
    uint8_t returnAddress(uint16_t address);//returns address from memory
    void writeToAddress(uint16_t address, uint8_t value);//changes value at address TODO overload to support uint16 and endianness
    void writeToAddress(uint16_t address, uint16_t value);


};


#endif //GB_EMULATOR_MMU_H
