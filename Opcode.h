//
// Created by Jas Sobolewski on 2025-06-23.
//

#ifndef GB_EMULATOR_OPCODE_H
#define GB_EMULATOR_OPCODE_H

#include "AbstractInstruction.h"

class AddA_B : public AbstractInstruction {
public:
    void execute(SM83& cpu, MMU& mmu, int& cyclesDuringInstruction) override {
    }
};

class NOP : public AbstractInstruction {
public:
    void execute(SM83& cpu, MMU& mmu, int& cyclesDuringInstruction) override {
    }
};

class LD_A_B : public AbstractInstruction {
public:
    void execute(SM83& cpu, MMU& mmu, int& cyclesDuringInstruction) override {
        cpu.A = cpu.B; //load the value of B into A
    }
};






#endif //GB_EMULATOR_OPCODE_H
