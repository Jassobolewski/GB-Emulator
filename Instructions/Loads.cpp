//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "Loads.h"

void LD_a16_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    const auto address = mmu.returnWord(cpu.PC + 1);
    const auto write = cpu.A;
    mmu.writeWord(address, write);
    cpu.PC += 3;
    cyclesDuringInstruction = 16;
}

void LD_A_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    const auto address = mmu.returnWord(cpu.PC + 1);
    const auto value = mmu.returnAddress(address);
    cpu.A = value;
    cpu.PC += 3;
    cyclesDuringInstruction = 16;
}

void LD_B_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.A; //load the value of B into A
    cyclesDuringInstruction = 4;
    cpu.PC += 1;
}

void LD_C_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate8BitValue(cpu.C);
    cyclesDuringInstruction = 8;
}

void LD_E_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate8BitValue(cpu.E);
    cyclesDuringInstruction = 8;
}

void LD_HL_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    const auto address = mmu.returnWord(cpu.PC + 1);
    cpu.set_HL(address);
    cpu.PC += 3;
    cyclesDuringInstruction = 12;
}

void LD_DE_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.set_DE(cpu.immediate16BitValue(cpu.D, cpu.E));
    cyclesDuringInstruction = 12;
}

void LD_BC_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.memoryBus.writeToAddress(cpu.getBc(),cpu.A);
    cyclesDuringInstruction = 8;
}
void LD_DE_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.memoryBus.writeToAddress(cpu.getDe(),cpu.A);
    cyclesDuringInstruction = 8;
}

void LD_BC_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    //std::cout << "EXECUTING LD BC, n16 "<< std::endl;
    cpu.BC = cpu.immediate16BitValue(cpu.B, cpu.C);
    cyclesDuringInstruction = 12;
}

void LD_B_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.immediate8BitValue(cpu.B);
    cyclesDuringInstruction = 8;
}

void LD_D_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.immediate8BitValue(cpu.D);
    cyclesDuringInstruction = 8;
}

void LD_A_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.B; //load the value of B into A
    cyclesDuringInstruction = 4;
    cpu.PC += 1;
}

void LD_A_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.HL;
    cyclesDuringInstruction = 8;
    cpu.PC += 1;
}

void LD_HLI_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.memoryBus.writeToAddress(cpu.HL, cpu.A);
    cpu.HL = cpu.HL + 1;
    cyclesDuringInstruction = 4;
}

void LD_D_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_D_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.H;
    cyclesDuringInstruction = 4;
}

void LD_SP_NN::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = [](SM83 &cpu) {
        uint8_t lsb = 0;
        uint8_t msb = 0;
        auto nn = cpu.immediate16BitValue(lsb, msb);
        return nn;
    }(cpu);
    cpu.memoryBus.writeWord(nn,(cpu.SP));
    cyclesDuringInstruction = 20;
}

void LD_A_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.memoryBus.returnAddress(cpu.getBc());
    cyclesDuringInstruction = 8;
}


void LD_A_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.memoryBus.returnAddress(cpu.getDe());
    cyclesDuringInstruction = 8;
}

void POP_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_BC(nn);
}
void POP_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_DE(nn);
}
void POP_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_HL(nn);
}
void POP_AF::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_AF(nn);
    cyclesDuringInstruction = 12;
}

void Push_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate16BitValuePushSP(cpu.B,cpu.C);
    cyclesDuringInstruction = 16;
}

void Push_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate16BitValuePushSP(cpu.D,cpu.E);
    cyclesDuringInstruction = 16;
}

void Push_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate16BitValuePushSP(cpu.H,cpu.L);
    cyclesDuringInstruction = 16;
}

void Push_AF::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate16BitValuePushSP(cpu.A,cpu.F);
    cyclesDuringInstruction = 16;
}
