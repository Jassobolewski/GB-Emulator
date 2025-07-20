//
// Created by Jas Sobolewski on 2025-07-20.
//
#include "Opcode.h"

void STOP_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.PC = cpu.PC + 2;
}

void NOP::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    //cpu.PC += 1;
    cyclesDuringInstruction = 4;
}

void HALT::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cyclesDuringInstruction = 4;
}

void RLCA::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    auto toggleBit = cpu.A & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::Z,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A << 1) ^ (toggleBit ? 1 : 0);

}

void RRCA::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1);
    cpu.A = cpu.A >> 1;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::Z,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    toggleBit ? cpu.A |= (1 << 7) : cpu.A &= ~(1 << 7);

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

void Unimplemented::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint16_t address = cpu.PC - 1;
    std::cerr << "FATAL ERROR: Unimplemented opcode encountered: 0x"
              << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(opcode)
              << " at address 0x"
              << std::hex << std::setw(4) << std::setfill('0') << address
              << std::endl;
    cpu.PC += 1;
    cyclesDuringInstruction = 4;
}


