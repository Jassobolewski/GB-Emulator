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

void SM83::immediate16BitValuePushSP(uint8_t& registerMSB, uint8_t& registerLSB) {
    this->memoryBus.writeToAddress(--SP,registerMSB);
    this->memoryBus.writeToAddress(--SP,registerLSB);
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
        if(opcode != 0xCB)
            instruction->execute(*this, memoryBus, cycles_this_step, opcode);
        else
            instruction->execute(*this, memoryBus, cycles_this_step, this->memoryBus.returnAddress(PC) + 256);
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
    instructionSet[0x02] = std::make_unique<LD_BC_A>();//Pass
    instructionSet[0x03] = std::make_unique<INC_BC>();//Pass
    instructionSet[0x04] = std::make_unique<INC_B>();//Pass
    instructionSet[0x05] = std::make_unique<DEC_B>();//Pass
    instructionSet[0x06] = std::make_unique<LD_B_n8>();//pass
    instructionSet[0x07] = std::make_unique<RLCA>();//pass
    instructionSet[0x08] = std::make_unique<LD_SP_NN>();//pass
    instructionSet[0x09] = std::make_unique<Add_HL_BC>();//pass
    instructionSet[0x0A] = std::make_unique<LD_A_BC>();//pass
    instructionSet[0x0B] = std::make_unique<DEC_BC>();//pass
    instructionSet[0x0C] = std::make_unique<INC_C>();//pass
    instructionSet[0x0D] = std::make_unique<DEC_C>();//pass
    instructionSet[0x0E] = std::make_unique<LD_C_n8>();//pass
    instructionSet[0x0F] = std::make_unique<RRCA>();//pass

    instructionSet[0x11] = std::make_unique<LD_DE_n16>();//pass
    instructionSet[0x12] = std::make_unique<LD_DE_A>();
    instructionSet[0x13] = std::make_unique<INC_DE>();//Pass
    instructionSet[0x14] = std::make_unique<INC_D>();//Pass
    instructionSet[0x15] = std::make_unique<DEC_D>();//pass
    instructionSet[0x16] = std::make_unique<LD_D_n8>();//pass
    instructionSet[0x17] = std::make_unique<RLA>();//pass
    instructionSet[0x18] = std::make_unique<JP_E>();//pass
    instructionSet[0x19] = std::make_unique<Add_HL_DE>();//pass
    instructionSet[0x1A] = std::make_unique<LD_A_DE>();//pass
    instructionSet[0x1B] = std::make_unique<DEC_DE>();//pass
    instructionSet[0x1C] = std::make_unique<INC_E>();//pass
    instructionSet[0x1D] = std::make_unique<DEC_E>();//pass
    instructionSet[0x1E] = std::make_unique<LD_E_n8>();//pass
    instructionSet[0x1F] = std::make_unique<RRA>();//

    instructionSet[0x20] = std::make_unique<JR_NZ_e8>();//
    instructionSet[0x21] = std::make_unique<LD_HL_n16>();//pass
    instructionSet[0x22] = std::make_unique<LD_HLPlus_A>();//pass
    instructionSet[0x23] = std::make_unique<INC_HL>();//Pass
    instructionSet[0x24] = std::make_unique<INC_H>();//Pass
    instructionSet[0x25] = std::make_unique<DEC_H>();//pass
    instructionSet[0x26] = std::make_unique<LD_H_n8>();//pass
    instructionSet[0x27] = std::make_unique<DAA>();//hard
    instructionSet[0x28] = std::make_unique<JR_Z_e8>();//hard
    instructionSet[0x29] = std::make_unique<Add_HL_HL>();//
    instructionSet[0x2A] = std::make_unique<LD_A_HLPlus>();//
    instructionSet[0x2B] = std::make_unique<DEC_HL>();//
    instructionSet[0x2C] = std::make_unique<INC_L>();//
    instructionSet[0x2D] = std::make_unique<DEC_L>();//
    instructionSet[0x2E] = std::make_unique<LD_L_n8>();//
    instructionSet[0x2F] = std::make_unique<CPL>();//

    instructionSet[0x30] = std::make_unique<JR_NC_e8>();//pass
    instructionSet[0x31] = std::make_unique<LD_SP_n16>();//pass
    instructionSet[0x32] = std::make_unique<LD_A_HLMinus>();//pass
    instructionSet[0x33] = std::make_unique<INC_SP>();//pass

    instructionSet[0x34] = std::make_unique<INC_HL_Indirect>();

    instructionSet[0x37] = std::make_unique<SCF>();//pass
    instructionSet[0x38] = std::make_unique<JR_C_e8>();//pass
    instructionSet[0x3C] = std::make_unique<INC_A>();//
    instructionSet[0x3D] = std::make_unique<DEC_A>();//
    instructionSet[0x3F] = std::make_unique<CCF>();//pass

    instructionSet[0x40] = std::make_unique<LD_B_B>();//pass
    instructionSet[0x41] = std::make_unique<LD_B_C>();//pass
    instructionSet[0x42] = std::make_unique<LD_B_D>();//pass
    instructionSet[0x43] = std::make_unique<LD_B_E>();//pass
    instructionSet[0x44] = std::make_unique<LD_B_H>();//pass
    instructionSet[0x45] = std::make_unique<LD_B_L>();//
    instructionSet[0x46] = std::make_unique<LD_B_HL>();//

    instructionSet[0x80] =  std::make_unique<AddA_B>();//
    instructionSet[0x81] =  std::make_unique<AddA_C>();//pass
    instructionSet[0x82] =  std::make_unique<AddA_D>();//pass
    instructionSet[0x83] =  std::make_unique<AddA_E>();////pass
    instructionSet[0x84] =  std::make_unique<AddA_H>();////pass
    instructionSet[0x85] =  std::make_unique<AddA_L>();////pass
    instructionSet[0x86] =  std::make_unique<AddA_HL>();////pass
    instructionSet[0x87] =  std::make_unique<AddA_A>();////pass

    instructionSet[0x88] =  std::make_unique<AdcA_B>();//
    instructionSet[0x89] =  std::make_unique<AdcA_C>();//
    instructionSet[0x8A] =  std::make_unique<AdcA_D>();//
    instructionSet[0x8B] =  std::make_unique<AdcA_E>();//
    instructionSet[0x8C] =  std::make_unique<AdcA_H>();//
    instructionSet[0x8D] =  std::make_unique<AdcA_L>();//
    instructionSet[0x8E] =  std::make_unique<AdcA_HL>();//
    instructionSet[0x8F] =  std::make_unique<AdcA_A>();//

    instructionSet[0x90] =  std::make_unique<SubA_B>();//
    instructionSet[0x98] =  std::make_unique<SbcA_B>();//
    instructionSet[0xA0] =  std::make_unique<AND_A_B>();//
    instructionSet[0xA8] =  std::make_unique<XOR_A_B>();//
    instructionSet[0xB0] =  std::make_unique<OR_A_B>();//
    instructionSet[0xB8] =  std::make_unique<CP_A_B>();//
    instructionSet[0xC0] =  std::make_unique<RET_NZ>();//Pass
    instructionSet[0xC1] =  std::make_unique<POP_BC>();//Pass
    instructionSet[0xC5] =  std::make_unique<Push_BC>();//Pass
    instructionSet[0xC9] =  std::make_unique<RET>();//Pass
    instructionSet[0xD1] =  std::make_unique<POP_DE>();//
    instructionSet[0xD5] =  std::make_unique<Push_DE>();//Pass
    instructionSet[0xE1] =  std::make_unique<POP_HL>();//
    instructionSet[0xE5] =  std::make_unique<Push_HL>();//Pass
    instructionSet[0xF1] =  std::make_unique<POP_AF>();//
    instructionSet[0xF5] =  std::make_unique<Push_AF>();//Pass
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



