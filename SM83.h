//
// Created by Jas Sobolewski on 2025-06-16.
//

#ifndef GB_EMULATOR_SM83_H
#define GB_EMULATOR_SM83_H


#include <cstdint>
#include <stack>
#include "MMU.h"

class AbstractInstruction; //forward declaration

class SM83 {

    int debugCounter = 0;
    std::stack<uint8_t> debugStack;//Records instructions in the order they happen *for rewinding and debugging later*
    std::vector<std::unique_ptr<AbstractInstruction>> instructionSet;

public: //This is temporary
    MMU memoryBus;
    SM83();
    ~SM83(); // To handle the forward declaration of AbstractInstruction


    //Accumulators
    uint8_t A{},B{},D{},H{};
    //Flags
    uint8_t F{}, C{}, E{}, L{};

    uint16_t SP{}; //Stack Pointer
    uint16_t PC{}; //Program Counter

    uint8_t low_byte = this->memoryBus.returnAddress((this->PC + 1));  // Gets 0x00
    uint8_t high_byte =  this->memoryBus.returnAddress((this->PC + 1)); // Gets 0xC0
    uint16_t immediate_value = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
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

    static void setFlag(uint16_t value, uint8_t& flags);

    static void setAccumulator(uint16_t value, uint8_t& accumulator);

    static uint16_t combinedValue(uint8_t upper, uint8_t lower);

    void set_AF(uint16_t value);

    void set_BC(uint16_t value);

    void set_DE(uint16_t value);

    void set_HL(uint16_t value);

    int instructionExecution();//returns cycle count


    SM83(const SM83&) = delete;
    SM83& operator=(const SM83&) = delete;
    SM83(SM83&&) = delete;
    SM83& operator=(SM83&&) = delete;


    uint16_t immediate16BitValueSP();

    uint16_t immediate16BitValue(uint8_t &registerLSB, uint8_t &registerMSB);
};


#endif //GB_EMULATOR_SM83_H
