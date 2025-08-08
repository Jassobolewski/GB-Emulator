//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "ControlFlow.h"

void JR_NZ_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    if(cpu.getRegisterFlag(SM83::Flag::Z) == 0) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }

}

void JP_NN::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    // The 16-bit address operand is at PC + 1
    const uint16_t new_address = cpu.memoryBus.returnWord(cpu.PC + 1);
    cpu.PC = new_address;
    cyclesDuringInstruction = 4;
}

void JP_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    uint8_t operand = mmu.returnAddress(cpu.PC++);

    auto signed_offset = static_cast<int8_t>(operand);

    cpu.PC =  cpu.PC + signed_offset;

    cyclesDuringInstruction = 12;
}

void JR_NC_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::C) == 0) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }
}

void JR_Z_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::Z)) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }
}

void JR_C_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::C)) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }
}




void RET_NZ::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(!cpu.getRegisterFlag(SM83::Flag::Z))
    {
        cpu.PC = cpu.immediate16BitValueSP();
        cyclesDuringInstruction = 2;
    }
    else
        cyclesDuringInstruction = 5;
}

void RET::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.PC = cpu.immediate16BitValueSP();
    cyclesDuringInstruction = 2;
}

void RETInterrupt::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.PC = cpu.immediate16BitValueSP();
    cpu.interruptEnabled = true;
}
