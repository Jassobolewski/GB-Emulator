//
// Created by Jas Sobolewski on 2025-06-22.
//
#include <gtest/gtest.h>
#include "../MMU.h" // Include the MMU header
#include <fstream> // For file loading
class MMUTest : public ::testing::Test {
protected:
    MMU mmu;
    // SetUp() might not be needed if the default constructor is enough
};

TEST_F(MMUTest, SimpleReadWrite) {
    // Arrange: Write a value to a specific memory address
    mmu.writeToAddress(0xC000, 0x42);

    // Act & Assert: Read it back and check if it's correct
    EXPECT_EQ(mmu.returnAddress(0xC000), 0x42);
}

TEST_F(MMUTest, ReadWrite16BitWord) {
    // Remember the Game Boy is little-endian!

    // Arrange
    mmu.writeWord(0xC100, 0x1234);

    // Assert individual bytes
    EXPECT_EQ(mmu.returnAddress(0xC100), 0x34); // Low byte first
    EXPECT_EQ(mmu.returnAddress(0xC101), 0x12); // High byte second

    // Assert the full word read
    EXPECT_EQ(mmu.returnWord(0xC100), 0x1234);
}

TEST_F(MMUTest, CannotWriteToROM) {
    // The first 32KB of memory (0x0000 - 0x7FFF) is usually ROM.
    // Your MMU should prevent writes to this area (after the boot ROM is done).
    // This is our simple test ROM.
    const std::vector<uint8_t> simple_rom = {
            // Opcode, Operand(s)  ; Instruction          ; PC After
            //---------------------------------------------------------
            0x3E, 0x42,             // LD A, 0x42           ; PC = 2
            0x06, 0xAA,             // LD B, 0xAA           ; PC = 4
            0x21, 0x00, 0xC0,       // LD HL, 0xC000        ; PC = 7
            0x77,                   // LD (HL), A           ; PC = 8
            0x23,                   // INC HL               ; PC = 9
            0x70,                   // LD (HL), B           ; PC = 10
            0x76                    // HALT                 ; PC = 11
    };


    std::ifstream rom_file("/Users/jas/GB Project/GB-Emulator/roms/cpu_instrs.gb", std::ios::binary);

    // Check if the ROM was found. If not, fail the test immediately.
    if (!rom_file.is_open()) {
        FAIL() << "Could not open Blargg test ROM: ../roms/cpu_instrs.gb";
    }

    // Read the ROM into a vector
    std::vector<uint8_t> rom_data((std::istreambuf_iterator<char>(rom_file)),std::istreambuf_iterator<char>());
    rom_file.close();

    // Arrange: Write the initial value
    mmu.loadRom(rom_data);
    // Assert: The original value should still be there
    EXPECT_EQ(mmu.returnAddress(0x0), 0x3C);
    EXPECT_EQ(mmu.returnAddress(0x1), 0xC9);
    EXPECT_EQ(mmu.returnAddress(0xA), '\0');
}