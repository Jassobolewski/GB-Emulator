//
// Created by Jas Sobolewski on 2025-06-16.
//

#ifndef GB_EMULATOR_SM83_H
#define GB_EMULATOR_SM83_H


#include <cstdint>

class SM83 {
    //Accumulators
    uint8_t A,B,D,H;
    //Flags
    uint8_t F, C, E, L;

    uint16_t SP; //Stack Pointer
    uint16_t PC; //Program Counter

    //Combined 16 bit registers
    uint16_t AF, BC, DE,HL;

    void SetFlag(uint16_t value, uint8_t& flags);

    void SetAccumulator(uint16_t value, uint8_t& accumulator);

    void set_AF(uint16_t value);

    void set_BC(uint16_t value);

    void set_DE(uint16_t value);

    void set_HL(uint16_t value);





};


#endif //GB_EMULATOR_SM83_H
