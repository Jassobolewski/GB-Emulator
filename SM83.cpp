//
// Created by Jas Sobolewski on 2025-06-16.
//

#include "SM83.h"
#include "AbstractInstruction.h"
#include "Opcode.h"

void SM83::setFlag(const uint16_t value, uint8_t& flags) {
    flags = value & 0xFF;
}

void SM83::setAccumulator(const uint16_t value, uint8_t& accumulator) {
    accumulator = (value >> 8) & 0xFF;
}

uint16_t SM83::combinedValue(const uint8_t upper, const uint8_t lower) {
    return ((upper << 8)|lower);
}

//#warning bugs maybe if F lower isn't always 0
void SM83::set_AF(const uint16_t value) {
    SM83::setAccumulator(value, A);
    SM83::setFlag(value, F);
    //set lower half of F to 0
    F &= 0xF0;
    AF = SM83::combinedValue(A,F);
}

void SM83::set_BC(const uint16_t value) {
    SM83::setAccumulator(value, B);
    SM83::setFlag(value, C);
    BC = SM83::combinedValue(B,C);

}

void SM83::set_DE(const uint16_t value) {
    SM83::setAccumulator(value, D);
    SM83::setFlag(value, E);
    DE = SM83::combinedValue(D,E);
}


void SM83::set_HL(const uint16_t value) {
    SM83::setAccumulator(value, H);
    SM83::setFlag(value, L);
    HL = SM83::combinedValue(H,L);
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
    const uint8_t opcode = memoryBus.returnAddress(PC);
    const auto instruction = instructionSet[opcode].get();
    int cycles_this_step = 0;
   if(instruction != nullptr) {
       instruction->execute(*this, memoryBus, cycles_this_step, opcode);
   }
   else
        std::cerr << "FATAL ERROR: Unimplemented opcode encountered: 0x" << std::hex << static_cast<int>(opcode) <<
                std::endl;


    return cycles_this_step;
}

SM83::SM83() {

    for (int i = 0; i < 256; ++i) {
        instructionSet.push_back(std::make_unique<Unimplemented>());
    }
    instructionSet[0x00] = std::make_unique<NOP>();
    instructionSet[0x01] = std::make_unique<LD_BC_n16>();

    instructionSet[0x3c] = std::make_unique<INC_A>();

    instructionSet[0xc3] = std::make_unique<JP_NN>();
    instructionSet[0x78] = std::make_unique<LD_A_B>();
    instructionSet[0x80] = std::make_unique<AddA_B>();
    instructionSet[0x81] = std::make_unique<AddA_C>();
    instructionSet[0x82] = std::make_unique<AddA_D>();
    instructionSet[0x83] = std::make_unique<AddA_E>();

    instructionSet[0xea] = std::make_unique<LD_A_a16>();

}

SM83::~SM83() = default;



