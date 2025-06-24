//
// Created by Jas Sobolewski on 2025-06-16.
//

#ifndef GB_EMULATOR_SM83_H
#define GB_EMULATOR_SM83_H


#include <cstdint>
#include "MMU.h"

class AbstractInstruction; //forward declaration

class SM83 {

    MMU* memoryBus{};
    std::vector<std::unique_ptr<AbstractInstruction>> instructionSet;

public: //This is temporary

    SM83();
    ~SM83(); // To handle the forward declaration of AbstractInstruction

    //Accumulators
    uint8_t A{},B{},D{},H{};
    //Flags
    uint8_t F{}, C{}, E{}, L{};

    uint16_t SP{}; //Stack Pointer
    uint16_t PC{}; //Program Counter

    //Combined 16 bit registers
    uint16_t AF{}, BC{}, DE{},HL{};

    enum class Flag : uint8_t {
        Z = 1 << 7,
        N = 1 << 6,
        H = 1 << 5,
        C = 1 << 4
    };

    void setRegisterFlag(Flag flag, bool toggleBit);

    [[nodiscard]] bool getRegisterFlag(Flag flag) const;

    void setFlag(uint16_t value, uint8_t& flags);

    void setAccumulator(uint16_t value, uint8_t& accumulator);

    uint16_t combinedValue(uint8_t upper, uint8_t lower);

    void set_AF(uint16_t value);

    void set_BC(uint16_t value);

    void set_DE(uint16_t value);

    void set_HL(uint16_t value);

    int instructionExecution();//returns cycle count

    void connectMemory(MMU* memory);

    SM83(const SM83&) = delete;
    SM83& operator=(const SM83&) = delete;
    SM83(SM83&&) = delete;
    SM83& operator=(SM83&&) = delete;

};


#endif //GB_EMULATOR_SM83_H
