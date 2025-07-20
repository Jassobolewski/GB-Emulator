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

void AddA_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueB = cpu.B;

    const auto half_carry_check = (registerValueA & 0x0F) + (registerValueB & 0x0F);
    cpu.setRegisterFlag(SM83::Flag::H, half_carry_check );

    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );

    const auto fullValue = cpu.A + cpu.B;
    cpu.setRegisterFlag(SM83::Flag::C, fullValue > 0xFF );
    cpu.setRegisterFlag(SM83::Flag::N, false );

    cpu.A = fullValue & 0xFF;
    cpu.PC += 1;
}

void AddA_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueC = cpu.C;

    const auto half_carry_check = (registerValueA & 0x0F) + (registerValueC & 0x0F);
    cpu.setRegisterFlag(SM83::Flag::H, half_carry_check );

    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );

    const auto fullValue = cpu.A + cpu.C;
    cpu.setRegisterFlag(SM83::Flag::C, fullValue > 0xFF );
    cpu.setRegisterFlag(SM83::Flag::N, false );

    cpu.A = fullValue & 0xFF;
    cpu.PC += 1;
}

void AddA_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueC = cpu.D;

    const auto half_carry_check = (registerValueA & 0x0F) + (registerValueC & 0x0F);
    cpu.setRegisterFlag(SM83::Flag::H, half_carry_check );

    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );

    const auto fullValue = cpu.A + cpu.D;
    cpu.setRegisterFlag(SM83::Flag::C, fullValue > 0xFF );
    cpu.setRegisterFlag(SM83::Flag::N, false );

    cpu.A = fullValue & 0xFF;
    cpu.PC += 1;
}

void AddA_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
    const auto registerValueA = cpu.A;
    const auto registerValueC = cpu.E;

    const auto half_carry_check = (registerValueA & 0x0F) + (registerValueC & 0x0F);
    cpu.setRegisterFlag(SM83::Flag::H, half_carry_check );

    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );

    const auto fullValue = cpu.A + cpu.E;
    cpu.setRegisterFlag(SM83::Flag::C, fullValue > 0xFF );
    cpu.setRegisterFlag(SM83::Flag::N, false );

    cpu.A = fullValue & 0xFF;
    cpu.PC += 1;
}
