//
// Created by Jas Sobolewski on 2025-06-24.
//

#ifndef GB_EMULATOR_UNIMPLEMENTED_H
#define GB_EMULATOR_UNIMPLEMENTED_H
#include "AbstractInstruction.h"

class Unimplemented : public AbstractInstruction {
public:
    void execute(SM83& cpu, MMU& mmu, int& cyclesDuringInstruction) override;
};


#endif //GB_EMULATOR_UNIMPLEMENTED_H
