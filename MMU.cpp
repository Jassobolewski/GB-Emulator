//
// Created by Jas Sobolewski on 2025-06-21.
//

#include "MMU.h"

void MMU::loadRom(const std::vector<uint8_t>& romData) {
    size_t i = 0;
    for(auto &it : romData)
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

uint8_t MMU::returnAddress(const uint16_t address) const {
    return memoryMap[address];
}

void MMU::writeToAddress(const uint16_t address, const uint8_t value) {
    if (address == 0xFF01) {//Serial port
        std::cout << (value) << std::endl;
        serialTransferData = value;
        return;
    }

    if(address > 0x7FFF)//write to address outside of rom area
    {
        memoryMap[address] = value;
    }
    else
    {
        std::println("Denied Access MMU");
    }
}

void MMU::writeWord(uint16_t address, uint16_t value) {
    if (address == 0xFF01) {//Serial port
        std::cout << (value) << std::endl;
        serialTransferData = value;
        return;
    }

    if(address == 0xFF02)
    {
        if (value == 0x81) {
            // Append the buffered character to our stringstream.
            serialOutput << static_cast<char>(serialTransferData);
        }
        return; // Return early
    }

    if(address > 0x7FFF)//write to address outside of rom area
    {
        uint8_t low_byte = value & 0xFF;
        uint8_t high_byte = (value >> 8) & 0xFF;
        writeToAddress(address,low_byte);
        writeToAddress(address + 1, high_byte);
    }
    else
    {
        std::println("Denied Access");
    }
}

uint16_t MMU::returnWord(uint16_t address) {
    auto low_byte = returnAddress(address);
    auto high_byte = returnAddress(address + 1);

    return (high_byte << 8 | low_byte);

}

std::string MMU::getSerialOutput() const {
        return serialOutput.str();
}

