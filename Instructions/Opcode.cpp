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

void RLA::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::Z,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.A = (cpu.A << 1) ^ (cpu.getRegisterFlag(SM83::Flag::C));
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);

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

void RRA::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1);
    cpu.A = cpu.A >> 1;
    cpu.getRegisterFlag(SM83::Flag::C) ? cpu.A |= (1 << 7) : cpu.A &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::Z,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);


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


void DAA::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    int offset = 0;

    if(cpu.getRegisterFlag(SM83::Flag::N) == 0 && (cpu.A & 0xF) > 0x09 || cpu.getRegisterFlag(SM83::Flag::H))
    {
        offset = 0x06;
    }

    if(cpu.getRegisterFlag(SM83::Flag::N) == 0 && (cpu.A) > 0x99 || cpu.getRegisterFlag(SM83::Flag::C))
    {
        offset = 0x60;
    }

    if(!cpu.getRegisterFlag(SM83::Flag::N))
    {
        cpu.A += offset;
    }
    else
    {
        cpu.A -= offset;
    }

    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::C,cpu.A > 0x99);

}
