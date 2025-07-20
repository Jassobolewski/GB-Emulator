//
// Created by Jas Sobolewski on 2025-06-23.
//

#ifndef GB_EMULATOR_ABSTRACTINSTRUCTION_H
#define GB_EMULATOR_ABSTRACTINSTRUCTION_H

#include "../MMU.h"
#include "../SM83.h"


class AbstractInstruction {
public:
    virtual ~AbstractInstruction() = default;
    virtual void execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) = 0;
};


#endif //GB_EMULATOR_ABSTRACTINSTRUCTION_H
