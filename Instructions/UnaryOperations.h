//
// Created by Jas Sobolewski on 2025-07-19.
//

#ifndef GB_EMULATOR_UNARYOPERATIONS_H
#define GB_EMULATOR_UNARYOPERATIONS_H

#include "AbstractInstruction.h"

class INC_A final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.A = cpu.A + 1;

        cpu.setRegisterFlag(SM83::Flag::H,cpu.A & 0x0F );
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.A == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
        cpu.PC += 1;
    };
};

class INC_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.setRegisterFlag(SM83::Flag::H,(((cpu.B++ & 0xF) + (1 & 0xf)) & 0x10));
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
    };
};

class DEC_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.setRegisterFlag(SM83::Flag::H,(((cpu.B-- & 0xF) - (1 & 0xf)) & 0x10));
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.B == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, true );
    };
};

class DEC_D final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.setRegisterFlag(SM83::Flag::H,(((cpu.D-- & 0xF) - (1 & 0xf)) & 0x10));
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, true );
    };
};


class INC_BC final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 8;
        cpu.C += 1;
    };
};


class INC_C final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.C = cpu.C + 1;

        cpu.setRegisterFlag(SM83::Flag::H,cpu.C & 0x0F );
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.C == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
        cpu.PC += 1;
    };
};

class INC_D final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.setRegisterFlag(SM83::Flag::H,(((cpu.D++ & 0xF) + (1 & 0xf)) & 0x10));
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.D == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
    };
};

class INC_H final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.setRegisterFlag(SM83::Flag::H,(((cpu.H++ & 0xF) + (1 & 0xf)) & 0x10));
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.H == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
    };
};

class INC_E final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.E = cpu.E + 1;

        cpu.setRegisterFlag(SM83::Flag::H,cpu.E & 0x0F );
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.E == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
        cpu.PC += 1;
    };
};

class INC_L final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cyclesDuringInstruction = 4;
        cpu.L = cpu.L + 1;

        cpu.setRegisterFlag(SM83::Flag::H, cpu.L & 0x0F);
        cpu.setRegisterFlag(SM83::Flag::Z, cpu.L == 0);
        cpu.setRegisterFlag(SM83::Flag::N, false);
        cpu.PC += 1;
    };
};


#endif //GB_EMULATOR_UNARYOPERATIONS_H
