//
// Created by Jas Sobolewski on 2025-06-16.
//

#include "SM83.h"
#include "Instructions/Opcode.h"
#include "Instructions/ControlFlow.h"


uint16_t SM83::immediate16BitValue(uint8_t& registerMSB, uint8_t& registerLSB)
{
    registerLSB = this->memoryBus.returnAddress(PC++);
    registerMSB = this->memoryBus.returnAddress(PC++);
    return combinedValue(registerMSB, registerLSB);
}

uint8_t SM83::immediate8BitValue(uint8_t& currentRegister)
{
    currentRegister = this->memoryBus.returnAddress(PC++);
    return currentRegister;
}


uint16_t SM83::immediate16BitValueSP() {
    auto lsb = this->memoryBus.returnAddress(SP++);
    auto msb = this->memoryBus.returnAddress(SP++);

    return combinedValue(msb,lsb);
}

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
    const uint8_t opcode = memoryBus.returnAddress(this->PC++);
   // this->PC = PC + 1;//increment the PC after instruction is fetched
    /*
     * !important if PC mismatch happens it's because we increment more than necessary
     * */
    const auto instruction = instructionSet[opcode].get();
    int cycles_this_step = 0;
   if(instruction != nullptr) {
       debugStack.push(opcode);

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
    instructionSet[0x00] = std::make_unique<NOP>();//Pass
    instructionSet[0x01] = std::make_unique<LD_BC_n16>();//Pass
    instructionSet[0x03] = std::make_unique<INC_BC>();//Pass
    instructionSet[0x04] = std::make_unique<INC_B>();//Pass
    instructionSet[0x05] = std::make_unique<DEC_B>();//Pass
    instructionSet[0x06] = std::make_unique<LD_B_n8>();//pass
    instructionSet[0x07] = std::make_unique<RLCA>();//
    instructionSet[0x08] = std::make_unique<LD_SP_NN>();//
    instructionSet[0x09] = std::make_unique<Add_HL_BC>();//
    instructionSet[0x14] = std::make_unique<INC_D>();//Pass
    instructionSet[0x15] = std::make_unique<DEC_D>();//pass
    instructionSet[0x24] = std::make_unique<INC_H>();//Pass
    instructionSet[0x25] = std::make_unique<DEC_H>();//pass

    instructionSet[0xC0] =  std::make_unique<RET_NZ>();//Pass

    instructionSet[0x0E] = std::make_unique<LD_C_n8>();
    instructionSet[0x10] =std::make_unique<STOP_n8>();
    instructionSet[0x11] = std::make_unique<LD_DE_n16>();
    instructionSet[0x12] = std::make_unique<INC_C>();
    instructionSet[0x1c] = std::make_unique<INC_E>();

    instructionSet[0x20] = std::make_unique<JR_NZ_e8>();
    instructionSet[0x21] = std::make_unique<LD_HL_n16>();
    instructionSet[0x22] = std::make_unique<LD_HLI_A>();
  //  instructionSet[0x25] = std::make_unique<DEC_H>();
    instructionSet[0x2A] = std::make_unique<LD_A_HL>();
    instructionSet[0x3c] = std::make_unique<INC_A>();
   // instructionSet[0x3b] = std::make_unique<DEC_SP>();
    instructionSet[0x47] = std::make_unique<LD_B_A>();
    instructionSet[0x50]  = std::make_unique<LD_D_B>();

    instructionSet[0x54]  = std::make_unique<LD_D_H>();

    instructionSet[0xc3] = std::make_unique<JP_NN>();
    instructionSet[0x76] = std::make_unique<HALT>();

    instructionSet[0x78] = std::make_unique<LD_A_B>();
    instructionSet[0x80] = std::make_unique<AddA_B>();
    instructionSet[0x81] = std::make_unique<AddA_C>();
    instructionSet[0x82] = std::make_unique<AddA_D>();
    instructionSet[0x83] = std::make_unique<AddA_E>();

    instructionSet[0xea] = std::make_unique<LD_A_a16>();

}

uint16_t SM83::getAf() const {
    return combinedValue(A,F);
}

uint16_t SM83::getBc() const {
    return combinedValue(B,C);
}

uint16_t SM83::getDe() const {
    return combinedValue(D,E);;
}

uint16_t SM83::getHl() const {
    return combinedValue(H,L);
}


SM83::~SM83() = default;



