//
// Created by Jas Sobolewski on 2025-06-16.
//

#include "SM83.h"
#include "AbstractInstruction.h"
#include "Unimplemented.h"
#include "Opcode.h"

void SM83::setFlag(uint16_t value, uint8_t& flags) {
    flags = value & 0xFF;
}

void SM83::setAccumulator(uint16_t value, uint8_t& accumulator) {
    accumulator = (value >> 8) & 0xFF;
}

uint16_t SM83::combinedValue(uint8_t upper, uint8_t lower) {
    return ((upper << 8)|lower);
}

//#warning bugs maybe if F lower isn't always 0
void SM83::set_AF(uint16_t value) {
    this->setAccumulator(value, A);
    this->setFlag(value, F);
    //set lower half of F to 0
    F &= 0xF0;
    AF = this->combinedValue(A,F);
}

void SM83::set_BC(uint16_t value) {
    this->setAccumulator(value, B);
    this->setFlag(value, C);
    BC = this->combinedValue(B,C);

}

void SM83::set_DE(uint16_t value) {
    this->setAccumulator(value, D);
    this->setFlag(value, E);
    DE = this->combinedValue(D,E);
}


void SM83::set_HL(uint16_t value) {
    this->setAccumulator(value, H);
    this->setFlag(value, L);
    HL = this->combinedValue(H,L);
}

void SM83::setRegisterFlag(SM83::Flag flag, bool toggleBit) {
    const auto bitmask = static_cast<uint8_t>(flag);

    if (toggleBit) {
        F = F | bitmask;//turns on
    } else {
        F = F & (~bitmask);//turns off
    }
    F &= 0xF0;
}

bool SM83::getRegisterFlag(SM83::Flag flag) const {
    const auto bitmask = static_cast<uint8_t>(flag);
    return (F & bitmask) != 0;//We check if the flag is on or off
}

int SM83::instructionExecution() {
    uint8_t opcode = memoryBus->returnAddress(PC++);
    auto instruction = instructionSet[opcode].get();
    int cycles_this_step = 0;

    if(instruction != nullptr)
        instruction->execute(*this, *memoryBus, cycles_this_step);
    else
        std::cerr << "FATAL ERROR: Unimplemented opcode encountered: 0x" << std::hex << static_cast<int>(opcode) << std::endl;


    return cycles_this_step;
}

void SM83::connectMemory(MMU *memory) {
    this->memoryBus = memory;
}

SM83::SM83() {
    instructionSet.resize(256);

    for (int i = 0; i < 256; ++i) {
        instructionSet[i] = std::make_unique<Unimplemented>();
    }
    instructionSet[0x78] = std::make_unique<LD_A_B>();

}

SM83::~SM83() = default;


