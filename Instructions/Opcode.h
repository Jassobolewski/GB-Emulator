//
// Created by Jas Sobolewski on 2025-06-23.
//

#ifndef GB_EMULATOR_OPCODE_H
#define GB_EMULATOR_OPCODE_H

#include "AbstractInstruction.h"
#include "Arithmetic.h"
#include "Loads.h"
#include "UnaryOperations.h"
#include <iomanip>


class STOP_n8 final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
       cpu.PC = cpu.PC + 2;
    };
};

class NOP final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        //cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};

class HALT final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};


class RLCA final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {

        auto toggleBit = cpu.A & (1 << 7);
        cpu.setRegisterFlag(SM83::Flag::H,false);
        cpu.setRegisterFlag(SM83::Flag::Z,false);
        cpu.setRegisterFlag(SM83::Flag::N, false );
        cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
        cpu.A = (cpu.A << 1) ^ (toggleBit ? 1 : 0);

    }
};

class RET_NZ final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        if(!cpu.getRegisterFlag(SM83::Flag::Z))
        {
            cpu.PC = cpu.immediate16BitValueSP();
            cyclesDuringInstruction = 2;
        }
        else
            cyclesDuringInstruction = 5;
    }
};

class Unimplemented final : public AbstractInstruction {
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
