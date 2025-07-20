//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "UnaryOperations.h"


void INC_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.A = cpu.A + 1;

    cpu.setRegisterFlag(SM83::Flag::H,cpu.A & 0x0F );
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.PC += 1;
}

void INC_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.B++ & 0xF) + (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void DEC_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.B-- & 0xF) - (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, true );
}

void DEC_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.D-- & 0xF) - (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, true );
}

void INC_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 8;
    cpu.set_BC(cpu.getBc() + 1);
}

void INC_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 8;
    cpu.set_DE(cpu.getDe() + 1);
}


void INC_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.C++ & 0xF) + (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void INC_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.D++ & 0xF) + (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void INC_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.H++ & 0xF) + (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void INC_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.E = cpu.E + 1;

    cpu.setRegisterFlag(SM83::Flag::H,cpu.E & 0x0F );
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.PC += 1;
}

void DEC_SP::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.SP -= 1;
    cyclesDuringInstruction = 8;
}

void DEC_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.H-- & 0xF) - (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, true );
}

void INC_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.L = cpu.L + 1;

    cpu.setRegisterFlag(SM83::Flag::H, cpu.L & 0x0F);
    cpu.setRegisterFlag(SM83::Flag::Z, cpu.L == 0);
    cpu.setRegisterFlag(SM83::Flag::N, false);
    cpu.PC += 1;
}

void DEC_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.set_BC(cpu.getBc() - 1);
    cyclesDuringInstruction = 8;
}

void DEC_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    cpu.setRegisterFlag(SM83::Flag::H,(((cpu.C-- & 0xF) - (1 & 0xf)) & 0x10));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, true );
}
