//
// Created by Jas Sobolewski on 2025-07-19.
//

#ifndef GB_EMULATOR_CONTROLFLOW_H
#define GB_EMULATOR_CONTROLFLOW_H
#include "AbstractInstruction.h"

class JR_NZ_e8 final : public AbstractInstruction {
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;;
};

class JP_NN final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JP_E final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JR_Z_e8 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JR_C_e8 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JR_NC_e8 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JP_NZ_a16 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JP_NC_a16 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JP_C_a16 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JP_Z_a16 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class JP_a16 final : public AbstractInstruction{
public:
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RET_NZ final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RET_NC final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RET final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};
class RET_Z final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RET_C final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};


class CALL_NC_a16 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CALL_C_a16 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CALL_NZ_a16 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};
class CALL_Z_a16 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class CALL_a16 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_00 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_08 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_10 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_18 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_20 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_28 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_30 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};

class RST_38 final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};


class RETInterrupt final : public AbstractInstruction{
    void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) override;
};


#endif //GB_EMULATOR_CONTROLFLOW_H
