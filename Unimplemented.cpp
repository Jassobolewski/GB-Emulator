//
// Created by Jas Sobolewski on 2025-06-24.
//

#include "Unimplemented.h"
#include <iomanip>
void Unimplemented::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction) {
    uint16_t opcode_address = cpu.PC - 1;
    uint8_t opcode_value = mmu.returnAddress(opcode_address); // Careful with MMU access here

    std::cerr << "FATAL ERROR: Unimplemented opcode encountered: 0x"
              << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(opcode_value)
              << " at address 0x" << std::setw(4) << opcode_address << std::endl;
}
