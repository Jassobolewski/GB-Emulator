//
// Created by Jas Sobolewski on 2025-07-19.
//

#include "Loads.h"

void LD_a16_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    auto nn = cpu.immediate16BitValue(lsb, msb);
    cpu.write(nn, cpu.A);
    cyclesDuringInstruction = 16;
}

void LD_A_a16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    auto nn = cpu.immediate16BitValue(lsb, msb);
    cpu.A = cpu.read(nn);
    cyclesDuringInstruction = 16;
}

void LD_B_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.A; //load the value of B into A
    cyclesDuringInstruction = 4;
}

void LD_C_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate8BitValue(cpu.C);
    cyclesDuringInstruction = 8;
}

void LD_E_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate8BitValue(cpu.E);
    cyclesDuringInstruction = 8;
}

void LD_L_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate8BitValue(cpu.L);
    cyclesDuringInstruction = 8;
}

void LD_A_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.immediate8BitValue(cpu.A);
    cyclesDuringInstruction = 8;
}

void LD_HL_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.HL = cpu.immediate16BitValue(cpu.H, cpu.L);
    cyclesDuringInstruction = 12;
}

void LD_DE_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.set_DE(cpu.immediate16BitValue(cpu.D, cpu.E));
    cyclesDuringInstruction = 12;
}

void LD_SP_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = [](SM83 &cpu) {
        uint8_t lsb = 0;
        uint8_t msb = 0;
        auto nn = cpu.immediate16BitValue(lsb, msb);
        return nn;
    }(cpu);
    cpu.SP = nn;
    cyclesDuringInstruction = 12;
}

void LD_BC_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getBc(),cpu.A);
    cyclesDuringInstruction = 8;
}
void LD_DE_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getDe(),cpu.A);
    cyclesDuringInstruction = 8;
}

void LD_BC_n16::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    //std::cout << "EXECUTING LD BC, n16 "<< std::endl;
    cpu.BC = cpu.immediate16BitValue(cpu.B, cpu.C);
    cyclesDuringInstruction = 12;
}

void LD_B_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.immediate8BitValue(cpu.B);
    cyclesDuringInstruction = 8;
}

void LD_D_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.immediate8BitValue(cpu.D);
    cyclesDuringInstruction = 8;
}


void LD_H_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.immediate8BitValue(cpu.H);
    cyclesDuringInstruction = 8;
}


void LD_A_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.A;
    cyclesDuringInstruction = 4;
}

void LD_A_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_A_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.C;
    cyclesDuringInstruction = 4;
}

void LD_A_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.D;
    cyclesDuringInstruction = 4;
}

void LD_A_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.E;
    cyclesDuringInstruction = 4;
}

void LD_A_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.L;
    cyclesDuringInstruction = 4;
}

void LD_A_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.H;
    cyclesDuringInstruction = 4;
}
//end of L loads

void LD_B_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.B; //load the value of B into B
    cyclesDuringInstruction = 4;
}

void LD_B_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.C; //load the value of B into B
    cyclesDuringInstruction = 4;
}

void LD_B_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.D; //load the value of B into B
    cyclesDuringInstruction = 4;
}

void LD_B_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.E; //load the value of B into B
    cyclesDuringInstruction = 4;
}

void LD_B_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.H; //load the value of B into B
    cyclesDuringInstruction = 4;
}

void LD_B_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.L; //load the value of B into B
    cyclesDuringInstruction = 4;
}

void LD_B_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.B = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}

void LD_C_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.A;
    cyclesDuringInstruction = 4;
}

void LD_C_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_C_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.C;
    cyclesDuringInstruction = 4;
}

void LD_C_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.D;
    cyclesDuringInstruction = 4;
}

void LD_C_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.E;
    cyclesDuringInstruction = 4;
}

void LD_C_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.L;
    cyclesDuringInstruction = 4;
}

void LD_C_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.H;
    cyclesDuringInstruction = 4;
}
// D loads
void LD_D_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.A;
    cyclesDuringInstruction = 4;
}

void LD_D_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_D_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.C;
    cyclesDuringInstruction = 4;
}

void LD_D_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.D;
    cyclesDuringInstruction = 4;
}

void LD_D_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.E;
    cyclesDuringInstruction = 4;
}

void LD_D_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.L;
    cyclesDuringInstruction = 4;
}

void LD_D_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.H;
    cyclesDuringInstruction = 4;
}

//end of D loads


//E loads


void LD_E_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.A;
    cyclesDuringInstruction = 4;
}

void LD_E_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_E_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.C;
    cyclesDuringInstruction = 4;
}

void LD_E_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.D;
    cyclesDuringInstruction = 4;
}

void LD_E_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.E;
    cyclesDuringInstruction = 4;
}

void LD_E_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.L;
    cyclesDuringInstruction = 4;
}

void LD_E_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.H;
    cyclesDuringInstruction = 4;
}

//end of E loads

// H loads

void LD_H_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.A;
    cyclesDuringInstruction = 4;
}

void LD_H_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_H_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.C;
    cyclesDuringInstruction = 4;
}

void LD_H_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.D;
    cyclesDuringInstruction = 4;
}

void LD_H_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.E;
    cyclesDuringInstruction = 4;
}

void LD_H_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.L;
    cyclesDuringInstruction = 4;
}

void LD_H_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.H;
    cyclesDuringInstruction = 4;
}


//End of H loads

//L loads
void LD_L_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.A;
    cyclesDuringInstruction = 4;
}

void LD_L_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.B;
    cyclesDuringInstruction = 4;
}

void LD_L_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.C;
    cyclesDuringInstruction = 4;
}

void LD_L_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.D;
    cyclesDuringInstruction = 4;
}

void LD_L_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.E;
    cyclesDuringInstruction = 4;
}

void LD_L_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.L;
    cyclesDuringInstruction = 4;
}

void LD_L_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.H;
    cyclesDuringInstruction = 4;
}
//end of L loads



void LD_C_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}


void LD_D_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.D = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}

void LD_H_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.H = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}

void LD_E_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.E = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}

void LD_L_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.L = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}

void LD_A_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.read(cpu.getHl());
    cyclesDuringInstruction = 8;
}

void LD_A_HLPlus::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.read(cpu.getHl());
    cpu.set_HL(cpu.getHl() + 1);
    cyclesDuringInstruction = 12;
}

void LD_A_HLMinus::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.read(cpu.getHl());
    cpu.set_HL(cpu.getHl() - 1);
    cyclesDuringInstruction = 12;
}

void LD_HLMinus_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
   cpu.write(cpu.getHl(),cpu.A);
    cpu.set_HL(cpu.getHl() - 1);
    cyclesDuringInstruction = 12;
}

void LD_HLIndirect_n8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
   auto data = cpu.read(cpu.PC++);
   cpu.write(cpu.getHl(), data);
    cyclesDuringInstruction = 12;
}

void LD_SP_NN::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = [](SM83 &cpu) {
        uint8_t lsb = 0;
        uint8_t msb = 0;
        auto nn = cpu.immediate16BitValue(lsb, msb);
        return nn;
    }(cpu);
    cpu.write16Bit(nn,(cpu.SP));
}

void LD_A_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.read(cpu.getBc());
}


void LD_A_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.A = cpu.read(cpu.getDe());
}

void POP_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_BC(nn);
}
void POP_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_DE(nn);
}
void POP_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_HL(nn);
}
void POP_AF::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto nn = cpu.immediate16BitValueSP();
    cpu.set_AF(nn);
    cyclesDuringInstruction = 12;
}

void Push_BC::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.tick();
    cpu.immediate16BitValuePushSP(cpu.B,cpu.C);
}

void Push_DE::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.tick();
    cpu.immediate16BitValuePushSP(cpu.D,cpu.E);
}

void Push_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.tick();
    cpu.immediate16BitValuePushSP(cpu.H,cpu.L);
}

void Push_AF::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.tick();
    cpu.immediate16BitValuePushSP(cpu.A,cpu.F);
}


void LD_HLPlus_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.A);
    cpu.set_HL(cpu.getHl() + 1);
}

void INC_HL_Indirect::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.read(cpu.getHl());
    cpu.setRegisterFlag(SM83::Flag::H, (data & 0x0F) == 0x0F);
    cpu.write(cpu.getHl(), ++data);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, false );
}


void DEC_HL_Indirect::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto data = cpu.read(cpu.getHl());
    cpu.setRegisterFlag(SM83::Flag::H,(((data & 0xF) - (1 & 0xf)) & 0x10));
    cpu.write(cpu.getHl(), --data);
    cpu.setRegisterFlag(SM83::Flag::Z,data == 0 );
    cpu.setRegisterFlag(SM83::Flag::N, true );
}


void LD_HL_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.A);
    cyclesDuringInstruction = 8;
}

void LD_HL_B::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.B);
    cyclesDuringInstruction = 8;
}

void LD_HL_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.C);
    cyclesDuringInstruction = 8;
}

void LD_HL_D::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.D);
    cyclesDuringInstruction = 8;
}
void LD_HL_E::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.E);
    cyclesDuringInstruction = 8;
}

void LD_HL_H::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.H);
    cyclesDuringInstruction = 8;
}

void LD_HL_L::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(cpu.getHl(), cpu.L);
    cyclesDuringInstruction = 8;
}

void LDH_a8_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto value = cpu.read(cpu.PC++);
    uint8_t lsb = value & 0xFF;
    cpu.write(SM83::combinedValue(0xFF,lsb),cpu.A);
    cyclesDuringInstruction = 12;
}

void LDH_C_A::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.write(SM83::combinedValue(0xFF,cpu.C),cpu.A);
    cyclesDuringInstruction = 8;
}

void LDH_A_a8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto value = cpu.read(cpu.PC++);
    uint8_t lsb = value & 0xFF;
    cpu.A = cpu.read(SM83::combinedValue(0xFF,lsb));
    cyclesDuringInstruction = 12;
}

void LDH_A_C::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.C = cpu.read(SM83::combinedValue(0xFF,cpu.C));
    cyclesDuringInstruction = 8;
}

void LD_HL_SPe8::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    auto const nn = static_cast<uint8_t>(cpu.read(cpu.PC++));
    const auto signedAddress = static_cast<int8_t>(nn);
    cpu.set_HL(  (cpu.SP) + signedAddress);
    cpu.setRegisterFlag(SM83::Flag::H, ((nn & 0x0F) + ((cpu.SP & 0xFF) & 0x0F)) > 0x0F);
    cpu.setRegisterFlag(SM83::Flag::Z,false );
    cpu.setRegisterFlag(SM83::Flag::C, ((static_cast<uint16_t>(nn) + static_cast<uint16_t>(cpu.SP & 0xFF)) > 0xFF));
    cpu.setRegisterFlag(SM83::Flag::N, false );
    cyclesDuringInstruction = 12;
}

void LD_SP_HL::execute(SM83 &cpu, MMU &mmu, int &cyclesDuringInstruction, uint8_t opcode) {
    cpu.tick();
   cpu.SP = cpu.getHl();
    cyclesDuringInstruction = 8;
}
