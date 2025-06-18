//
// Created by Jas Sobolewski on 2025-06-16.
//

#include "SM83.h"
//TODO lamdas later in the morning
void SM83::SetFlag(uint16_t value, uint8_t& flags) {
    flags = value & 0xFF;
}

void SM83::SetAccumulator(uint16_t value, uint8_t& accumulator) {
    accumulator = (value >> 8) & 0xFF;
}

void SM83::set_AF(uint16_t value) {
    this->SetAccumulator(value, A);
    this->SetFlag(value, F);
    AF = ((A << 8)|F); // you put A and F into 16 bits you shift A to high postion
}

void SM83::set_BC(uint16_t value) {
    this->SetAccumulator(value, B);
    this->SetFlag(value, C);
    BC = ((B << 8)|C); // you put A and F into 16 bits you shift A to high postion

}

void SM83::set_DE(uint16_t value) {

}


void SM83::set_HL(uint16_t value) {

}
