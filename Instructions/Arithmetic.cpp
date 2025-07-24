//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "Arithmetic.h"

void Add_HL_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 8;
    const auto registerValueHL = cpu.getHl();
    const auto registerValueBC = cpu.getBc();
    const auto fullValue = cpu.getHl() + cpu.getBc();
    cpu.setRegisterFlag(SM83::Flag::H,   ((registerValueHL & 0x0FFF) + (registerValueBC & 0x0FFF)) > 0x0FFF);
    cpu.setRegisterFlag(SM83::Flag::C, ((fullValue) > 0xFFFF));
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.set_HL(fullValue);
}

void Add_HL_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 8;
    const auto registerValueHL = cpu.getHl();
    const auto registerValueDE = cpu.getDe();
    const auto fullValue = cpu.getHl() + cpu.getDe();
    cpu.setRegisterFlag(SM83::Flag::H,   ((registerValueHL & 0x0FFF) + (registerValueDE & 0x0FFF)) > 0x0FFF);
    cpu.setRegisterFlag(SM83::Flag::C, ((fullValue) > 0xFFFF));
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.set_HL(fullValue);
}


void AddA_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueB = cpu.B;
    cpu.A = cpu.A + cpu.B;
    cpu.setRegisterFlag(SM83::Flag::H, (((registerValueA & 0x0F) + (registerValueB & 0x0F)) > 0x0F));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::C,(0xFF < static_cast<uint16_t>(registerValueA) + static_cast<uint16_t>(registerValueB)) );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void AddA_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueC = cpu.C;
    cpu.A = cpu.A + cpu.C;
    cpu.setRegisterFlag(SM83::Flag::H, (((registerValueA & 0x0F) + (registerValueC & 0x0F)) > 0x0F));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::C,(0xFF < static_cast<uint16_t>(registerValueA) + static_cast<uint16_t>(registerValueC)) );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void AddA_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueD = cpu.D;
    cpu.A = cpu.A + cpu.D;
    cpu.setRegisterFlag(SM83::Flag::H, (((registerValueA & 0x0F) + (registerValueD & 0x0F)) > 0x0F));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::C,(0xFF < static_cast<uint16_t>(registerValueA) + static_cast<uint16_t>(registerValueD)) );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}

void AddA_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueE = cpu.E;
    cpu.A = cpu.A + cpu.E;
    cpu.setRegisterFlag(SM83::Flag::H, (((registerValueA & 0x0F) + (registerValueE & 0x0F)) > 0x0F));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::C,(0xFF < static_cast<uint16_t>(registerValueA) + static_cast<uint16_t>(registerValueE)) );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}


void SubA_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueB = cpu.B;
    cpu.A = cpu.A - cpu.B;
    cpu.setRegisterFlag(SM83::Flag::H, (registerValueB & 0x0F) > (registerValueA & 0x0F));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::C, registerValueB > registerValueA);
    cpu.setRegisterFlag(SM83::Flag::N, true );
}

void AdcA_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueB = cpu.B;
    cpu.A = cpu.A + cpu.B + cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H, (((registerValueA & 0x0F) + (registerValueB & 0x0F)  + (cpu.getRegisterFlag(SM83::Flag::C) & 0x0F)) > 0x0F));
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
    cpu.setRegisterFlag(SM83::Flag::C,(0xFF < static_cast<uint16_t>(registerValueA) + static_cast<uint16_t>(registerValueB) + static_cast<uint16_t> (cpu.getRegisterFlag(SM83::Flag::C))));
    cpu.setRegisterFlag(SM83::Flag::N, false );
}
