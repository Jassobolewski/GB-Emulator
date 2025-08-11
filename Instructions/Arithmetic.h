//
// Created by Jas Sobolewski on 2025-07-19.
//

#ifndef GB_EMULATOR_ARITHMETIC_H
#define GB_EMULATOR_ARITHMETIC_H

#include "AbstractInstruction.h"

class Add_HL_BC final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class Add_HL_DE final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class Add_HL_HL final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class Add_HL_SP final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_n8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AddSP_n8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};


class AddA_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AddA_C final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_D final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_E final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_H final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_L final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_HL final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AddA_A final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class AdcA_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_C final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_D final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_E final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_H final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_L final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_HL final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_A final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AdcA_n8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_n8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_A final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_C final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_D final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};


class SubA_E final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_H final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_L final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SubA_HL final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};



class SbcA_B final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_n8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_A final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_C final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_D final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_E final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_H final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_L final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class SbcA_HL final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_n8 final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_A final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_B final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_C final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_D final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_E final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_H final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_L final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class AND_A_HL final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_n8 final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_A final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_B final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_C final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_D final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_E final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_H final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_L final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class OR_A_HL final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_n8 final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_A final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_B final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_C final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_D final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_E final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_H final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_L final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class XOR_A_HL final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};


class CP_A_n8 final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_A final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_B final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_C final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_D final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_E final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_H final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_L final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CP_A_HL final :public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};









#endif //GB_EMULATOR_ARITHMETIC_H
