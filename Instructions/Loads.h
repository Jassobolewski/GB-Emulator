//
// Created by Jas Sobolewski on 2025-07-19.
//

#ifndef GB_EMULATOR_LOADS_H
#define GB_EMULATOR_LOADS_H

#include "AbstractInstruction.h"


class LD_a16_A final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        const auto address = mmu.returnWord(cpu.PC + 1);
        const auto write = cpu.A;
        mmu.writeWord(address, write);
        cpu.PC += 3;
        cyclesDuringInstruction = 16;
    };
};

class LD_A_a16 final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        const auto address = mmu.returnWord(cpu.PC + 1);
        const auto value = mmu.returnAddress(address);
        cpu.A = value;
        cpu.PC += 3;
        cyclesDuringInstruction = 16;
    };
};

class LD_B_A final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.B = cpu.A; //load the value of B into A
        cyclesDuringInstruction = 4;
        cpu.PC += 1;
    }
};

class LD_C_n8 final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        const auto address = mmu.returnWord(cpu.PC + 1);
        const auto value = mmu.returnAddress(address);
        cpu.C = value; //load the value of n8 into C
        cyclesDuringInstruction = 8;
        cpu.PC += 2;
    }
};


class LD_HL_n16 final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        const auto address = mmu.returnWord(cpu.PC + 1);
        cpu.set_HL(address);
        cpu.PC += 3;
        cyclesDuringInstruction = 12;
    };
};

class LD_DE_n16 final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.DE = cpu.immediate16BitValue(cpu.D, cpu.E);
        cyclesDuringInstruction = 12;
    };
};

class LD_BC_n16 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        //std::cout << "EXECUTING LD BC, n16 "<< std::endl;
        cpu.BC = cpu.immediate16BitValue(cpu.B, cpu.C);
        cyclesDuringInstruction = 12;
    }
};


class LD_B_n8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.B = cpu.immediate8BitValue(cpu.B);
        cyclesDuringInstruction = 8;
    }
};

//0x2
class LD_BC_A final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.set_BC(cpu.A);
        cpu.PC += 1;
        cyclesDuringInstruction = 8;
    }
};

class LD_A_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.A = cpu.B; //load the value of B into A
        cyclesDuringInstruction = 4;
        cpu.PC += 1;
    }
};

class LD_A_HL final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.A = cpu.HL;
        cyclesDuringInstruction = 8;
        cpu.PC += 1;
    }
};

class LD_HLI_A final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.memoryBus.writeToAddress(cpu.HL, cpu.A);
        cpu.HL = cpu.HL + 1;
        cyclesDuringInstruction = 4;
    }
};


class LD_D_B final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.D = cpu.B;
        cyclesDuringInstruction = 4;
    }
};


class LD_D_H final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.D = cpu.H;
        cyclesDuringInstruction = 4;
    }
};

class LD_SP_NN : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        auto nn = [](SM83 &cpu) {
            uint8_t lsb = 0;
            uint8_t msb = 0;
            auto nn = cpu.immediate16BitValue(lsb, msb);
            return nn;
        }(cpu);
        cpu.memoryBus.writeWord(nn,(cpu.SP));
        cyclesDuringInstruction = 20;
    }
};






#endif //GB_EMULATOR_LOADS_H
