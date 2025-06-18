//
// Created by Jas Sobolewski on 2025-06-16.
//

#include "SM83.h"

void SM83::setFlag(uint16_t value, uint8_t& flags) {
    flags = value & 0xFF;
}

void SM83::setAccumulator(uint16_t value, uint8_t& accumulator) {
    accumulator = (value >> 8) & 0xFF;
}

uint16_t SM83::combinedValue(uint8_t upper, uint8_t lower) {
    return ((upper << 8)|lower);
}

void SM83::set_AF(uint16_t value) {
    this->setAccumulator(value, A);
    this->setFlag(value, F);
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


