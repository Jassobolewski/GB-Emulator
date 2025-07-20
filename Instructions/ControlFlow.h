//
// Created by Jas Sobolewski on 2025-07-19.
//

#ifndef GB_EMULATOR_CONTROLFLOW_H
#define GB_EMULATOR_CONTROLFLOW_H
#include "AbstractInstruction.h"

class JR_NZ_e8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {

        if(cpu.getRegisterFlag(SM83::Flag::Z) == 0) {//jump to flag
            const auto e = mmu.returnWord(cpu.PC);
            cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 2);
        }
        else {
            cpu.PC += 2;
        }

    };
};

class JP_NN final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        // The 16-bit address operand is at PC + 1
        const uint16_t new_address = cpu.memoryBus.returnWord(cpu.PC + 1);
        cpu.PC = new_address;
        cyclesDuringInstruction = 4;
    }
};



#endif //GB_EMULATOR_CONTROLFLOW_H
