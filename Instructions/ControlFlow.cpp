//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "ControlFlow.h"

void JR_NZ_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    if(cpu.getRegisterFlag(SM83::Flag::Z) == 0) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 2);
    }
    else {
        cpu.PC += 2;
    }

}

void JP_NN::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    // The 16-bit address operand is at PC + 1
    const uint16_t new_address = cpu.memoryBus.returnWord(cpu.PC + 1);
    cpu.PC = new_address;
    cyclesDuringInstruction = 4;
}
