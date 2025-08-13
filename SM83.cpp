//
// Created by Jas Sobolewski on 2025-06-16.
//

#include "SM83.h"
#include "Instructions/Opcode.h"
#include "Instructions/ControlFlow.h"
#include "Instructions/CBBitwiseOperations.h"


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
        if(opcode != 0xCB)
            instruction->execute(*this, memoryBus, cycles_this_step, opcode);
        else {

            const uint8_t opcodeCB = memoryBus.returnAddress(this->PC++);
            const auto CBinstruction = instructionSetCB[opcodeCB].get();
            CBinstruction->execute(*this, memoryBus, cycles_this_step, opcode);

        }
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
    instructionSet[0x32] = std::make_unique<LD_HLMinus_A>();//pass
    instructionSet[0x33] = std::make_unique<INC_SP>();//pass
    instructionSet[0x34] = std::make_unique<INC_HL_Indirect>();
    instructionSet[0x35] = std::make_unique<DEC_HL_Indirect>();
    instructionSet[0x36] = std::make_unique<LD_HLIndirect_n8>();
    instructionSet[0x37] = std::make_unique<SCF>();//pass
    instructionSet[0x38] = std::make_unique<JR_C_e8>();//pass
    instructionSet[0x39] = std::make_unique<Add_HL_SP>();//pass
    instructionSet[0x3A] = std::make_unique<LD_A_HLMinus>();//pass
    instructionSet[0x3B] = std::make_unique<DEC_SP>();//pass
    instructionSet[0x3C] = std::make_unique<INC_A>();//
    instructionSet[0x3D] = std::make_unique<DEC_A>();//
    instructionSet[0x3E] = std::make_unique<LD_A_n8>();//
    instructionSet[0x3F] = std::make_unique<CCF>();//pass

    instructionSet[0x40] = std::make_unique<LD_B_B>();//pass
    instructionSet[0x41] = std::make_unique<LD_B_C>();//pass
    instructionSet[0x42] = std::make_unique<LD_B_D>();//pass
    instructionSet[0x43] = std::make_unique<LD_B_E>();//pass
    instructionSet[0x44] = std::make_unique<LD_B_H>();//pass
    instructionSet[0x45] = std::make_unique<LD_B_L>();//
    instructionSet[0x46] = std::make_unique<LD_B_HL>();//
    instructionSet[0x47] = std::make_unique<LD_B_A>();//
    instructionSet[0x48] = std::make_unique<LD_C_B>();//
    instructionSet[0x49] = std::make_unique<LD_C_C>();//
    instructionSet[0x4A] = std::make_unique<LD_C_D>();//
    instructionSet[0x4B] = std::make_unique<LD_C_E>();//
    instructionSet[0x4C] = std::make_unique<LD_C_H>();//
    instructionSet[0x4D] = std::make_unique<LD_C_L>();//
    instructionSet[0x4E] = std::make_unique<LD_C_HL>();//
    instructionSet[0x4F] = std::make_unique<LD_C_A>();//

    instructionSet[0x50] = std::make_unique<LD_D_B>();//pass
    instructionSet[0x51] = std::make_unique<LD_D_C>();//pass
    instructionSet[0x52] = std::make_unique<LD_D_D>();//pass
    instructionSet[0x53] = std::make_unique<LD_D_E>();//pass
    instructionSet[0x54] = std::make_unique<LD_D_H>();//pass
    instructionSet[0x55] = std::make_unique<LD_D_L>();//
    instructionSet[0x56] = std::make_unique<LD_D_HL>();//
    instructionSet[0x57] = std::make_unique<LD_D_A>();//
    instructionSet[0x58] = std::make_unique<LD_E_B>();//
    instructionSet[0x59] = std::make_unique<LD_E_C>();//
    instructionSet[0x5A] = std::make_unique<LD_E_D>();//
    instructionSet[0x5B] = std::make_unique<LD_E_E>();//
    instructionSet[0x5C] = std::make_unique<LD_E_H>();//
    instructionSet[0x5D] = std::make_unique<LD_E_L>();//
    instructionSet[0x5E] = std::make_unique<LD_E_HL>();//
    instructionSet[0x5F] = std::make_unique<LD_E_A>();//


    instructionSet[0x60] = std::make_unique<LD_H_B>();//pass
    instructionSet[0x61] = std::make_unique<LD_H_C>();//pass
    instructionSet[0x62] = std::make_unique<LD_H_D>();//pass
    instructionSet[0x63] = std::make_unique<LD_H_E>();//pass
    instructionSet[0x64] = std::make_unique<LD_H_H>();//pass
    instructionSet[0x65] = std::make_unique<LD_H_L>();//
    instructionSet[0x66] = std::make_unique<LD_H_HL>();//
    instructionSet[0x67] = std::make_unique<LD_H_A>();//
    instructionSet[0x68] = std::make_unique<LD_L_B>();//
    instructionSet[0x69] = std::make_unique<LD_L_C>();//
    instructionSet[0x6A] = std::make_unique<LD_L_D>();//
    instructionSet[0x6B] = std::make_unique<LD_L_E>();//
    instructionSet[0x6C] = std::make_unique<LD_L_H>();//
    instructionSet[0x6D] = std::make_unique<LD_L_L>();//
    instructionSet[0x6E] = std::make_unique<LD_L_HL>();//
    instructionSet[0x6F] = std::make_unique<LD_L_A>();//

    instructionSet[0x70] = std::make_unique<LD_HL_B>();//pass
    instructionSet[0x71] = std::make_unique<LD_HL_C>();//pass
    instructionSet[0x72] = std::make_unique<LD_HL_D>();//pass
    instructionSet[0x73] = std::make_unique<LD_HL_E>();//pass
    instructionSet[0x74] = std::make_unique<LD_HL_H>();//pass
    instructionSet[0x75] = std::make_unique<LD_HL_L>();//
    instructionSet[0x76] = std::make_unique<HALT>();//
    instructionSet[0x77] = std::make_unique<LD_HL_A>();//
    instructionSet[0x78] = std::make_unique<LD_A_B>();//
    instructionSet[0x79] = std::make_unique<LD_A_C>();//
    instructionSet[0x7A] = std::make_unique<LD_A_D>();//
    instructionSet[0x7B] = std::make_unique<LD_A_E>();//
    instructionSet[0x7C] = std::make_unique<LD_A_H>();//
    instructionSet[0x7D] = std::make_unique<LD_A_L>();//
    instructionSet[0x7E] = std::make_unique<LD_A_HL>();//
    instructionSet[0x7F] = std::make_unique<LD_A_A>();//

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
    instructionSet[0x91] =  std::make_unique<SubA_C>();//pass
    instructionSet[0x92] =  std::make_unique<SubA_D>();//pass
    instructionSet[0x93] =  std::make_unique<SubA_E>();////pass
    instructionSet[0x94] =  std::make_unique<SubA_H>();////pass
    instructionSet[0x95] =  std::make_unique<SubA_L>();////pass
    instructionSet[0x96] =  std::make_unique<SubA_HL>();////pass
    instructionSet[0x97] =  std::make_unique<SubA_A>();////pass
    instructionSet[0x98] =  std::make_unique<SbcA_B>();//
    instructionSet[0x99] =  std::make_unique<SbcA_C>();//
    instructionSet[0x9A] =  std::make_unique<SbcA_D>();//
    instructionSet[0x9B] =  std::make_unique<SbcA_E>();//
    instructionSet[0x9C] =  std::make_unique<SbcA_H>();//
    instructionSet[0x9D] =  std::make_unique<SbcA_L>();//
    instructionSet[0x9E] =  std::make_unique<SbcA_HL>();//
    instructionSet[0x9F] =  std::make_unique<SbcA_A>();//


    instructionSet[0xA0] =  std::make_unique<AND_A_B>();//
    instructionSet[0xA1] =  std::make_unique<AND_A_C>();//
    instructionSet[0xA2] =  std::make_unique<AND_A_D>();//pass
    instructionSet[0xA3] =  std::make_unique<AND_A_E>();////pass
    instructionSet[0xA4] =  std::make_unique<AND_A_H>();////pass
    instructionSet[0xA5] =  std::make_unique<AND_A_L>();////pass
    instructionSet[0xA6] =  std::make_unique<AND_A_HL>();////pass
    instructionSet[0xA7] =  std::make_unique<AND_A_A>();////pass
    instructionSet[0xA8] =  std::make_unique<XOR_A_B>();//
    instructionSet[0xA9] =  std::make_unique<XOR_A_C>();//
    instructionSet[0xAA] =  std::make_unique<XOR_A_D>();//
    instructionSet[0xAB] =  std::make_unique<XOR_A_E>();//
    instructionSet[0xAC] =  std::make_unique<XOR_A_H>();//
    instructionSet[0xAD] =  std::make_unique<XOR_A_L>();//
    instructionSet[0xAE] =  std::make_unique<XOR_A_HL>();//
    instructionSet[0xAF] =  std::make_unique<XOR_A_A>();//

    instructionSet[0xB0] =  std::make_unique<OR_A_B>();//
    instructionSet[0xB1] =  std::make_unique<OR_A_C>();//
    instructionSet[0xB2] =  std::make_unique<OR_A_D>();
    instructionSet[0xB3] =  std::make_unique<OR_A_E>();
    instructionSet[0xB4] =  std::make_unique<OR_A_H>();
    instructionSet[0xB5] =  std::make_unique<OR_A_L>();
    instructionSet[0xB6] =  std::make_unique<OR_A_HL>();
    instructionSet[0xB7] =  std::make_unique<OR_A_A>();
    instructionSet[0xB8] =  std::make_unique<CP_A_B>();//
    instructionSet[0xB9] =  std::make_unique<CP_A_C>();//
    instructionSet[0xBA] =  std::make_unique<CP_A_D>();//
    instructionSet[0xBB] =  std::make_unique<CP_A_E>();//
    instructionSet[0xBC] =  std::make_unique<CP_A_H>();//
    instructionSet[0xBD] =  std::make_unique<CP_A_L>();//
    instructionSet[0xBE] =  std::make_unique<CP_A_HL>();//
    instructionSet[0xBF] =  std::make_unique<CP_A_A>();//


    instructionSet[0xC0] =  std::make_unique<RET_NZ>();//Pass
    instructionSet[0xC1] =  std::make_unique<POP_BC>();//Pass
    instructionSet[0xC2] =  std::make_unique<JP_NZ_a16>();
    instructionSet[0xC3] =  std::make_unique<JP_a16>();
    instructionSet[0xC4] =  std::make_unique<CALL_NZ_a16>();
    instructionSet[0xC5] =  std::make_unique<Push_BC>();//Pass
    instructionSet[0xC6] =  std::make_unique<AddA_n8>();//Pass
    instructionSet[0xC7] =  std::make_unique<RST_00>();
    instructionSet[0xC8] =  std::make_unique<RET_Z>();//Pass
    instructionSet[0xC9] =  std::make_unique<RET>();//Pass
    instructionSet[0xCA] =  std::make_unique<JP_Z_a16>();//Pass
    instructionSet[0xCC] =  std::make_unique<CALL_Z_a16>();
    instructionSet[0xCD] =  std::make_unique<CALL_a16>();
    instructionSet[0xCE] =  std::make_unique<AdcA_n8>();
    instructionSet[0xCF] =  std::make_unique<RST_08>();

    instructionSet[0xD0] =  std::make_unique<RET_NC>();//
    instructionSet[0xD1] =  std::make_unique<POP_DE>();//
    instructionSet[0xD2] =  std::make_unique<JP_NC_a16>();//
    instructionSet[0xD4] =  std::make_unique<CALL_NC_a16>();//
    instructionSet[0xD5] =  std::make_unique<Push_DE>();//Pass
    instructionSet[0xD6] =  std::make_unique<SubA_n8>();
    instructionSet[0xD7] =  std::make_unique<RST_10>();
    instructionSet[0xD8] =  std::make_unique<RET_C>();
    instructionSet[0xD9] =  std::make_unique<RETInterrupt>();//Cant be tested currently
    instructionSet[0xDA] =  std::make_unique<JP_C_a16>();
    //empty
    instructionSet[0xDC] =  std::make_unique<CALL_C_a16>();
    //empty
    instructionSet[0xDE] =  std::make_unique<SbcA_n8>();
    instructionSet[0xDF] =  std::make_unique<RST_18>();

    instructionSet[0xE0] =  std::make_unique<LDH_a8_A>();//
    instructionSet[0xE1] =  std::make_unique<POP_HL>();//
    instructionSet[0xE2] =  std::make_unique<LDH_C_A>();//
    instructionSet[0xE5] =  std::make_unique<Push_HL>();//Pass
    instructionSet[0xE6] =  std::make_unique<AND_A_n8>();//Pass
    instructionSet[0xE7] =  std::make_unique<RST_20>();//Pass
    instructionSet[0xE8] =  std::make_unique<AddSP_n8>();
    instructionSet[0xE9] =  std::make_unique<JP_HL>();
    instructionSet[0xEA] =  std::make_unique<LD_a16_A>();
    instructionSet[0xEE] =  std::make_unique<XOR_A_n8>();
    instructionSet[0xEF] =  std::make_unique<RST_28>();

    instructionSet[0xF0] =  std::make_unique<LDH_A_a8>();//
    instructionSet[0xF1] =  std::make_unique<POP_AF>();//
    instructionSet[0xF2] =  std::make_unique<LDH_A_C>();//
    //skip f3
    instructionSet[0xF5] =  std::make_unique<Push_AF>();//Pass
    instructionSet[0xF6] =  std::make_unique<OR_A_n8>();//
    instructionSet[0xF7] =  std::make_unique<RST_30>();//
    instructionSet[0xF8] =  std::make_unique<LD_HL_SPe8>();//
    instructionSet[0xF9] =  std::make_unique<LD_SP_HL>();//
    instructionSet[0xFA] =  std::make_unique<LD_A_a16>();//
    instructionSet[0xFE] =  std::make_unique<CP_A_n8>();//
    instructionSet[0xFF] =  std::make_unique<RST_38>();//


    for (int i = 0; i < 256; ++i) {
        instructionSetCB.push_back(std::make_unique<Unimplemented>());
    }

    instructionSetCB[0x00] = std::make_unique<RLC_B>();//Pass
    instructionSetCB[0x01] = std::make_unique<RLC_C>();//Pass
    instructionSetCB[0x02] = std::make_unique<RLC_D>();//Pass
    instructionSetCB[0x03] = std::make_unique<RLC_E>();//Pass
    instructionSetCB[0x04] = std::make_unique<RLC_H>();//Pass
    instructionSetCB[0x05] = std::make_unique<RLC_L>();//Pass
    instructionSetCB[0x06] = std::make_unique<RLC_HL>();//pass
    instructionSetCB[0x07] = std::make_unique<RLC_A>();//pass
    instructionSetCB[0x08] = std::make_unique<RRC_B>();//pass
    instructionSetCB[0x09] = std::make_unique<RRC_C>();//pass
    instructionSetCB[0x0A] = std::make_unique<RRC_D>();//pass
    instructionSetCB[0x0B] = std::make_unique<RRC_E>();//pass
    instructionSetCB[0x0C] = std::make_unique<RRC_H>();//pass
    instructionSetCB[0x0D] = std::make_unique<RRC_L>();//pass
    instructionSetCB[0x0E] = std::make_unique<RRC_HL>();//pass
    instructionSetCB[0x0F] = std::make_unique<RRC_A>();//pass

    instructionSetCB[0x10] = std::make_unique<RL_B>();//Pass
    instructionSetCB[0x11] = std::make_unique<RL_C>();//Pass
    instructionSetCB[0x12] = std::make_unique<RL_D>();//Pass
    instructionSetCB[0x13] = std::make_unique<RL_E>();//Pass
    instructionSetCB[0x14] = std::make_unique<RL_H>();//Pass
    instructionSetCB[0x15] = std::make_unique<RL_L>();//Pass
    instructionSetCB[0x16] = std::make_unique<RL_HL>();//pass
    instructionSetCB[0x17] = std::make_unique<RL_A>();//pass
    instructionSetCB[0x18] = std::make_unique<RR_B>();//pass
    instructionSetCB[0x19] = std::make_unique<RR_C>();//pass
    instructionSetCB[0x1A] = std::make_unique<RR_D>();//pass
    instructionSetCB[0x1B] = std::make_unique<RR_E>();//pass
    instructionSetCB[0x1C] = std::make_unique<RR_H>();//pass
    instructionSetCB[0x1D] = std::make_unique<RR_L>();//pass
    instructionSetCB[0x1E] = std::make_unique<RR_HL>();//pass
    instructionSetCB[0x1F] = std::make_unique<RR_A>();//pass

    instructionSetCB[0x20] = std::make_unique<SLA_B>();//Pass
    instructionSetCB[0x21] = std::make_unique<SLA_C>();//Pass
    instructionSetCB[0x22] = std::make_unique<SLA_D>();//Pass
    instructionSetCB[0x23] = std::make_unique<SLA_E>();//Pass
    instructionSetCB[0x24] = std::make_unique<SLA_H>();//Pass
    instructionSetCB[0x25] = std::make_unique<SLA_L>();//Pass
    instructionSetCB[0x26] = std::make_unique<SLA_HL>();//pass
    instructionSetCB[0x27] = std::make_unique<SLA_A>();//pass
    instructionSetCB[0x28] = std::make_unique<SRA_B>();//pass
    instructionSetCB[0x29] = std::make_unique<SRA_C>();//pass
    instructionSetCB[0x2A] = std::make_unique<SRA_D>();//pass
    instructionSetCB[0x2B] = std::make_unique<SRA_E>();//pass
    instructionSetCB[0x2C] = std::make_unique<SRA_H>();//pass
    instructionSetCB[0x2D] = std::make_unique<SRA_L>();//pass
    instructionSetCB[0x2E] = std::make_unique<SRA_HL>();//pass
    instructionSetCB[0x2F] = std::make_unique<SRA_A>();//pass





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



