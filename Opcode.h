//
// Created by Jas Sobolewski on 2025-06-23.
//

#ifndef GB_EMULATOR_OPCODE_H
#define GB_EMULATOR_OPCODE_H

#include "AbstractInstruction.h"
#include <iomanip>
class AddA_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
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
};

class AddA_C final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
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
    };
};

class AddA_D final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
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
    };
};

class AddA_E final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
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
    };
};

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

        cpu.setRegisterFlag(SM83::Flag::H,cpu.L & 0x0F );
        cpu.setRegisterFlag(SM83::Flag::Z,cpu.L == 0 );
        cpu.setRegisterFlag(SM83::Flag::N, false );
        cpu.PC += 1;
    };
};

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

class JR_NZ_e8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {

        if(cpu.getRegisterFlag(SM83::Flag::Z) == 0) {//jump to flag
            const auto e = mmu.returnWord(cpu.PC);
            cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 2);
        }
        else {
            cpu.PC += 2;
        }

    };
};

class STOP_n8 final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
       cpu.PC = cpu.PC + 2;
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



class SubA_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {

    };
};

class NOP final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        //cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};

class LD_BC_n16 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        //std::cout << "EXECUTING LD BC, n16 "<< std::endl;
        cpu.BC = cpu.immediate16BitValue(cpu.B, cpu.C);
        cyclesDuringInstruction = 12;
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

class JP_NN final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        // The 16-bit address operand is at PC + 1
        const uint16_t new_address = cpu.memoryBus.returnWord(cpu.PC + 1);
        cpu.PC = new_address;
        cyclesDuringInstruction = 4;
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

class HALT final : public AbstractInstruction {
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};

class LD_HLI_A final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.memoryBus.writeToAddress(cpu.HL, cpu.A);
        cpu.HL = cpu.HL + 1;
        cyclesDuringInstruction = 4;
    }
};

class DEC_SP final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        cpu.SP -= 1;
        cyclesDuringInstruction = 8;
    }
};

class DEC_H final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        auto result = cpu.H - 1;
        cpu.H = result;
        cpu.setRegisterFlag(SM83::Flag::Z, result == 0);
        cpu.setRegisterFlag(SM83::Flag::H, result & 0x0F);
        cpu.setRegisterFlag(SM83::Flag::N, true);
        cyclesDuringInstruction = 8;
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

class RET_NZ final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        if(!cpu.getRegisterFlag(SM83::Flag::Z))
        {
            cpu.PC = cpu.immediate16BitValueSP();
            cyclesDuringInstruction = 2;
        }
        else
            cyclesDuringInstruction = 5;
    }
};
class Unimplemented final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override {
        uint16_t address = cpu.PC - 1;
        std::cerr << "FATAL ERROR: Unimplemented opcode encountered: 0x"
                  << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(opcode)
                  << " at address 0x"
                  << std::hex << std::setw(4) << std::setfill('0') << address
                  << std::endl;
        cpu.PC += 1;
        cyclesDuringInstruction = 4;
    }
};







#endif //GB_EMULATOR_OPCODE_H
