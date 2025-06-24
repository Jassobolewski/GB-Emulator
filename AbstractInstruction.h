//
// Created by Jas Sobolewski on 2025-06-23.
//

#ifndef GB_EMULATOR_ABSTRACTINSTRUCTION_H
#define GB_EMULATOR_ABSTRACTINSTRUCTION_H


#include "SM83.h"
#include "MMU.h"

class AbstractInstruction {
public:
    virtual ~AbstractInstruction() = default;
    virtual void execute(SM83& cpu, MMU& mmu) = 0;
};


#endif //GB_EMULATOR_ABSTRACTINSTRUCTION_H
