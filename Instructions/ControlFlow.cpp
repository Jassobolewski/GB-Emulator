//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "ControlFlow.h"

void JR_NZ_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    if(cpu.getRegisterFlag(SM83::Flag::Z) == 0) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }

}

void JP_NN::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    // The 16-bit address operand is at PC + 1
    const uint16_t new_address = cpu.memoryBus.returnWord(cpu.PC + 1);
    cpu.PC = new_address;
    cyclesDuringInstruction = 4;
}

void JP_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {

    uint8_t operand = mmu.returnAddress(cpu.PC++);

    auto signed_offset = static_cast<int8_t>(operand);

    cpu.PC =  cpu.PC + signed_offset;

    cyclesDuringInstruction = 12;
}

void JR_NC_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::C) == 0) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }
}

void JR_Z_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::Z)) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }
}

void JR_C_e8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::C)) {//jump to flag
        const auto e = mmu.returnWord(cpu.PC);
        cpu.PC = (static_cast<int8_t>(e) + cpu.PC + 1);
    }
    else {
        cpu.PC++;
    }
}

void RET_NC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(!cpu.getRegisterFlag(SM83::Flag::C))
    {
        cpu.PC = cpu.immediate16BitValueSP();
        cyclesDuringInstruction = 2;
    }
    else
        cyclesDuringInstruction = 5;
}



void RET_NZ::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(!cpu.getRegisterFlag(SM83::Flag::Z))
    {
        cpu.PC = cpu.immediate16BitValueSP();
        cyclesDuringInstruction = 2;
    }
    else
        cyclesDuringInstruction = 5;
}

void RET_Z::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::Z))
    {
        cpu.PC = cpu.immediate16BitValueSP();
        cyclesDuringInstruction = 20;
    }
    else
        cyclesDuringInstruction = 8;
}

void RET_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    if(cpu.getRegisterFlag(SM83::Flag::C))
    {
        cpu.PC = cpu.immediate16BitValueSP();
        cyclesDuringInstruction = 20;
    }
    else
        cyclesDuringInstruction = 8;
}


void RET::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.PC = cpu.immediate16BitValueSP();
    cyclesDuringInstruction = 2;
}

void RETInterrupt::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.PC = cpu.immediate16BitValueSP();
    cpu.interruptEnabled = true;
}

void JP_NZ_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    auto value = cpu.immediate16BitValue(lsb,msb);
    if(!cpu.getRegisterFlag(SM83::Flag::Z))
        cpu.PC = value;
}


void JP_NC_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    auto value = cpu.immediate16BitValue(lsb,msb);
    if(!cpu.getRegisterFlag(SM83::Flag::C))
        cpu.PC = value;
}

void JP_C_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    auto value = cpu.immediate16BitValue(lsb,msb);
    if(cpu.getRegisterFlag(SM83::Flag::C))
        cpu.PC = value;
}


void JP_Z_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    auto value = cpu.immediate16BitValue(lsb,msb);
    if(cpu.getRegisterFlag(SM83::Flag::Z))
        cpu.PC = value;
}


void JP_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    cpu.PC  = cpu.immediate16BitValue(lsb,msb);
}

void CALL_NC_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb1 = 0;
    uint8_t msb1 = 0;
    auto value = cpu.immediate16BitValue(lsb1,msb1);
    if(!cpu.getRegisterFlag(SM83::Flag::C))
    {
        uint8_t lsb = cpu.PC & 0xFF;
        uint8_t msb = (cpu.PC >> 8) & 0xFF;
        cpu.immediate16BitValuePushSP(msb, lsb);
        cpu.PC = value;
    }
}

void CALL_C_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb1 = 0;
    uint8_t msb1 = 0;
    auto value = cpu.immediate16BitValue(lsb1,msb1);
    if(cpu.getRegisterFlag(SM83::Flag::C))
    {
        uint8_t lsb = cpu.PC & 0xFF;
        uint8_t msb = (cpu.PC >> 8) & 0xFF;
        cpu.immediate16BitValuePushSP(msb, lsb);
        cpu.PC = value;
    }
}


void CALL_NZ_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb1 = 0;
    uint8_t msb1 = 0;
    auto value = cpu.immediate16BitValue(lsb1,msb1);
    if(!cpu.getRegisterFlag(SM83::Flag::Z))
    {
        uint8_t lsb = cpu.PC & 0xFF;
        uint8_t msb = (cpu.PC >> 8) & 0xFF;
        cpu.immediate16BitValuePushSP(msb, lsb);
        cpu.PC = value;
    }
}

void CALL_Z_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb1 = 0;
    uint8_t msb1 = 0;
    auto value = cpu.immediate16BitValue(lsb1,msb1);
    if(cpu.getRegisterFlag(SM83::Flag::Z))
    {
        uint8_t lsb = cpu.PC & 0xFF;
        uint8_t msb = (cpu.PC >> 8) & 0xFF;
        cpu.immediate16BitValuePushSP(msb, lsb);
        cpu.PC = value;
    }
}

void CALL_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb1 = 0;
    uint8_t msb1 = 0;
    auto value = cpu.immediate16BitValue(lsb1,msb1);
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = value;
}



void RST_00::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x00);
    cyclesDuringInstruction = 16;
}

void RST_08::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x08);
    cyclesDuringInstruction = 16;
}

void RST_10::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x10);
    cyclesDuringInstruction = 16;
}

void RST_18::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x18);
    cyclesDuringInstruction = 16;
}

void RST_20::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x20);
    cyclesDuringInstruction = 16;
}


void RST_28::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x28);
    cyclesDuringInstruction = 16;
}

void RST_30::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x30);
    cyclesDuringInstruction = 16;
}

void RST_38::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = cpu.PC & 0xFF;
    uint8_t msb = (cpu.PC >> 8) & 0xFF;
    cpu.immediate16BitValuePushSP(msb, lsb);
    cpu.PC = SM83::combinedValue(0x00,0x38);
    cyclesDuringInstruction = 16;
}



