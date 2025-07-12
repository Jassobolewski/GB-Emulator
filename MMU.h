//
// Created by Jas Sobolewski on 2025-06-21.
//

#ifndef GB_EMULATOR_MMU_H
#define GB_EMULATOR_MMU_H
#include <cstdint>
#include <vector>
#include <print>
#include <iostream>
#include <sstream>
class MMU {
public:
    // Buffer for serial data transfer
    uint8_t serialTransferData = 0;

    // to capture all serial output
    std::stringstream serialOutput;

    uint8_t memoryMap[0xFFFF] = {0}; // Initialize to all zeros

    void loadRom(const std::vector<uint8_t>& romData);
    uint8_t returnAddress(uint16_t address) const;//returns address from memory
    void writeToAddress(uint16_t address, uint8_t value);//Write to address
    void writeWord(uint16_t address, uint16_t value);//Little endian support
    uint16_t returnWord(uint16_t address) const;//Returns word from memory location
    std::string getSerialOutput() const;


};


#endif //GB_EMULATOR_MMU_H
