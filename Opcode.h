//
// Created by Jas Sobolewski on 2025-06-23.
//

#ifndef GB_EMULATOR_OPCODE_H
#define GB_EMULATOR_OPCODE_H

#include "AbstractInstruction.h"
#include <iomanip>
class AddA_B : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
    }
};

class NOP : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};

class JP_NN : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        // The 16-bit address operand is at PC + 1
        uint16_t new_address = cpu.memoryBus.returnWord(cpu.PC + 1);
        cpu.PC = new_address;
    }
};

class LD_A_B : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.A = cpu.B; //load the value of B into A
        cyclesDuringInstruction = 4;
        cpu.PC += 1;
    }
};

class Unimplemented : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        uint16_t address = cpu.PC - 1;
        std::cerr << "FATAL ERROR: Unimplemented opcode encountered: 0x"
                  << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(opcode)
                  << " at address 0x"
                  << std::hex << std::setw(4) << std::setfill('0') << address
                  << std::endl;
        cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};







#endif //GB_EMULATOR_OPCODE_H
