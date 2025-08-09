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
//https://blog.ollien.com/posts/gb-daa/ thanks source for logic
    uint8_t a = cpu.A;
    uint8_t offset = 0;
    auto carry = cpu.getRegisterFlag(SM83::Flag::C);
    auto subtract = cpu.getRegisterFlag(SM83::Flag::N);
    auto halfCarry = cpu.getRegisterFlag(SM83::Flag::H);

    if (subtract) {
        if (halfCarry)
            offset |= 0x06;
        if (carry)
            offset |= 0x60;
    } else {
        if ((a & 0x0F) > 0x09 || halfCarry)
            offset |= 0x06;

        if (carry || a > 0x99) {
            offset |= 0x60;
            carry = true;
        }
    }

    subtract ? cpu.A -= offset : cpu.A += offset;
    // Set the flags based on the result
    cpu.setRegisterFlag(SM83::Flag::Z, cpu.A == 0);
    cpu.setRegisterFlag(SM83::Flag::H, false);
    cpu.setRegisterFlag(SM83::Flag::C, carry);
    cyclesDuringInstruction = 4;

}

void SCF::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.setRegisterFlag(SM83::Flag::N, false);
    cpu.setRegisterFlag(SM83::Flag::H, false);
    cpu.setRegisterFlag(SM83::Flag::C, true);
    cyclesDuringInstruction = 4;
}

void CCF::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.setRegisterFlag(SM83::Flag::N, false);
    cpu.setRegisterFlag(SM83::Flag::H, false);
    cpu.setRegisterFlag(SM83::Flag::C, !cpu.getRegisterFlag(SM83::Flag::C));
    cyclesDuringInstruction = 4;
}

void CPL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = ~cpu.A;
    cpu.setRegisterFlag(SM83::Flag::N, true);
    cpu.setRegisterFlag(SM83::Flag::H, true);
    cyclesDuringInstruction = 4;
}
