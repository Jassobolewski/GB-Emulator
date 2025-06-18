//
// Created by Jas Sobolewski on 2025-06-16.
//

#ifndef GB_EMULATOR_SM83_H
#define GB_EMULATOR_SM83_H


#include <cstdint>

class SM83 {

public: //This is temporary
    //Accumulators
    uint8_t A,B,D,H;
    //Flags
    uint8_t F, C, E, L;

    uint16_t SP; //Stack Pointer
    uint16_t PC; //Program Counter

    //Combined 16 bit registers
    uint16_t AF, BC, DE,HL;

    enum class Flag : uint8_t {
        Z = 1 << 7,
        N = 1 << 6,
        H = 1 << 5,
        C = 1 << 4
    };

    void setRegisterFlag(Flag flag, bool toggleBit);

    bool getRegisterFlag(Flag flag) const;

    void setFlag(uint16_t value, uint8_t& flags);

    void setAccumulator(uint16_t value, uint8_t& accumulator);

    uint16_t combinedValue(uint8_t upper, uint8_t lower);

    void set_AF(uint16_t value);

    void set_BC(uint16_t value);

    void set_DE(uint16_t value);

    void set_HL(uint16_t value);

};


#endif //GB_EMULATOR_SM83_H
