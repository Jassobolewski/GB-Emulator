//
// Created by Jas Sobolewski on 2025-08-11.
//

#include "CBBitwiseOperations.h"


void RLC_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B << 1);
    toggleBit ? cpu.B |= (1 << 0) : cpu.B &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void RLC_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C << 1);
    toggleBit ? cpu.C |= (1 << 0) : cpu.C &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void RLC_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D << 1);
    toggleBit ? cpu.D |= (1 << 0) : cpu.D &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void RLC_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E << 1);
    toggleBit ? cpu.E |= (1 << 0) : cpu.E &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void RLC_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H << 1);
    toggleBit ? cpu.H |= (1 << 0) : cpu.H &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void RLC_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L << 1);
    toggleBit ? cpu.L |= (1 << 0) : cpu.L &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void RLC_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data << 1);
    toggleBit ? data |= (1 << 0) : data &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void RLC_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A << 1);
    toggleBit ? cpu.A |= (1 << 0) : cpu.A &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


//Rotate RIGHT


void RRC_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B >> 1);
    toggleBit ? cpu.B |= (1 << 7) : cpu.B &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void RRC_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C >> 1);
    toggleBit ? cpu.C |= (1 << 7) : cpu.C &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void RRC_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D >> 1);
    toggleBit ? cpu.D |= (1 << 7) : cpu.D &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void RRC_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E >> 1);
    toggleBit ? cpu.E |= (1 << 7) : cpu.E &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void RRC_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H >> 1);
    toggleBit ? cpu.H |= (1 << 7) : cpu.H &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void RRC_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L >> 1);
    toggleBit ? cpu.L |= (1 << 7) : cpu.L &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void RRC_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data >> 1);
    toggleBit ? data |= (1 << 7) : data &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void RRC_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A >> 1);
    toggleBit ? cpu.A |= (1 << 7) : cpu.A &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


//Rotate Left through carry flag

void RL_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B << 1);
    lastFlagVal ? cpu.B |= (1 << 0) : cpu.B &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void RL_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C << 1);
    lastFlagVal ? cpu.C |= (1 << 0) : cpu.C &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void RL_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D << 1);
    lastFlagVal ? cpu.D |= (1 << 0) : cpu.D &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void RL_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E << 1);
    lastFlagVal ? cpu.E |= (1 << 0) : cpu.E &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void RL_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H << 1);
    lastFlagVal ? cpu.H |= (1 << 0) : cpu.H &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void RL_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L << 1);
    lastFlagVal ? cpu.L |= (1 << 0) : cpu.L &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void RL_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data << 1);
    lastFlagVal ? data |= (1 << 0) : data &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void RL_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 7);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A << 1);
    lastFlagVal ? cpu.A |= (1 << 0) : cpu.A &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


//Rotate RIGHT


void RR_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B >> 1);
    lastFlagVal ? cpu.B |= (1 << 7) : cpu.B &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void RR_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C >> 1);
    lastFlagVal ? cpu.C |= (1 << 7) : cpu.C &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void RR_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D >> 1);
    lastFlagVal ? cpu.D |= (1 << 7) : cpu.D &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void RR_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E >> 1);
    lastFlagVal ? cpu.E |= (1 << 7) : cpu.E &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void RR_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H >> 1);
    lastFlagVal ? cpu.H |= (1 << 7) : cpu.H &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void RR_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L >> 1);
    lastFlagVal ? cpu.L |= (1 << 7) : cpu.L &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void RR_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data >> 1);
    lastFlagVal ? data |= (1 << 7) : data &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void RR_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 0);
    auto lastFlagVal = cpu.getRegisterFlag(SM83::Flag::C);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A >> 1);
    lastFlagVal ? cpu.A |= (1 << 7) : cpu.A &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


//Rotate Left through carry flag default 0

void SLA_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B << 1);
    cpu.B &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void SLA_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C << 1);
    cpu.C &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void SLA_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D << 1);
    cpu.D &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void SLA_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E << 1);
    cpu.E &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void SLA_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H << 1);
    cpu.H &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void SLA_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L << 1);
    cpu.L &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void SLA_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data << 1);
    data &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void SLA_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A << 1);
    cpu.A &= ~(1 << 0);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


//Rotate RIGHT


void SRA_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 0);
    auto toggleBit7 = cpu.B & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B >> 1);
    toggleBit7 ? cpu.B |= (1 << 7) : cpu.B &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void SRA_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 0);
    auto toggleBit7 = cpu.C & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C >> 1);
    toggleBit7 ? cpu.C |= (1 << 7) : cpu.C &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void SRA_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 0);
    auto toggleBit7 = cpu.D & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D >> 1);
    toggleBit7 ? cpu.D |= (1 << 7) : cpu.D &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void SRA_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 0);
    auto toggleBit7 = cpu.E & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E >> 1);
    toggleBit7 ? cpu.E |= (1 << 7) : cpu.E &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void SRA_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 0);
    auto toggleBit7 = cpu.H & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H >> 1);
    toggleBit7 ? cpu.H |= (1 << 7) : cpu.H &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void SRA_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 0);
    auto toggleBit7 = cpu.L & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L >> 1);
    toggleBit7 ? cpu.L |= (1 << 7) : cpu.L &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void SRA_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 0);
    auto toggleBit7 = data & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data >> 1);
    toggleBit7 ? data |= (1 << 7) : data &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void SRA_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 0);
    auto toggleBit7 = cpu.A & (1 << 7);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A >> 1);
    toggleBit7 ? cpu.A |= (1 << 7) : cpu.A &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


// SWAP


void SWAP_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.B >> 4) & 0x0F;
    uint8_t lowerBits = cpu.B & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.B = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void SWAP_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.C >> 4) & 0x0F;
    uint8_t lowerBits = cpu.C & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.C  = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void SWAP_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.D >> 4) & 0x0F;
    uint8_t lowerBits = cpu.D & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.D  = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void SWAP_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.E >> 4) & 0x0F;
    uint8_t lowerBits = cpu.E & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.E  = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void SWAP_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.H >> 4) & 0x0F;
    uint8_t lowerBits = cpu.H & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.H  = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void SWAP_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.L >> 4) & 0x0F;
    uint8_t lowerBits = cpu.L & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.L  = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void SWAP_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    uint8_t upperBits = (data >> 4) & 0x0F;
    uint8_t lowerBits = data & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    data = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void SWAP_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t upperBits = (cpu.A >> 4) & 0x0F;
    uint8_t lowerBits = cpu.A & 0x0F;
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, false);
    cpu.A  = (lowerBits << 4 | upperBits);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}


//SRL

void SRL_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.B & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.B = (cpu.B >> 1);
    cpu.B &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0);
}

void SRL_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.C & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.C = (cpu.C >> 1);
    cpu.C &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0);
}


void SRL_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.D & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.D = (cpu.D >> 1);
    cpu.D &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0);
}

void SRL_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.E & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.E = (cpu.E >> 1);
    cpu.E &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0);
}

void SRL_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.H & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.H = (cpu.H >> 1);
    cpu.H &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0);
}

void SRL_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.L & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.L = (cpu.L >> 1);
    cpu.L &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0);
}


void SRL_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.memoryBus.returnAddress(cpu.getHl());
    auto toggleBit = data & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    data = (data >> 1);
    data &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0);
    cpu.memoryBus.writeToAddress(cpu.getHl(),data);
}

void SRL_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto toggleBit = cpu.A & (1 << 0);
    cpu.setRegisterFlag(SM83::Flag::H,false);
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cpu.setRegisterFlag(SM83::Flag::C, toggleBit);
    cpu.A = (cpu.A >> 1);
    cpu.A &= ~(1 << 7);
    cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0);
}
