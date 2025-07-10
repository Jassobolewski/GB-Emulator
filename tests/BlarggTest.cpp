//
// Created by Jas Sobolewski on 2025-06-24.
//
#include <gtest/gtest.h>
#include <memory>
#include <fstream> // For file loading
#include <vector>
#include <string>

// Include your main components
#include "../SM83.h"
#include "../MMU.h"

// This is an integration test, so our fixture needs both CPU and MMU
class BlarggTest : public ::testing::Test {
protected:

    SM83 cpu;
};

// The main test case for the cpu_instrs ROM
TEST_F(BlarggTest, CpuInstrsRom) {
    // 1. ARRANGE: Load the ROM file
    // NOTE: You must place the "cpu_instrs.gb" file in a known location.
    // A good spot is a "roms/" directory in your project root.
    std::ifstream rom_file("/Users/jas/GB Project/GB-Emulator/roms/cpu_instrs.gb", std::ios::binary);

    // Check if the ROM was found. If not, fail the test immediately.
    if (!rom_file.is_open()) {
        FAIL() << "Could not open Blargg test ROM: ../roms/cpu_instrs.gb";
    }

    // Read the ROM into a vector
    const std::vector<uint8_t> rom_data((std::istreambuf_iterator<char>(rom_file)),std::istreambuf_iterator<char>());
    rom_file.close();

    cpu.memoryBus.loadRom(rom_data);
    cpu.PC = 0x100; // Set Program Counter to the ROM's entry point

    // 2. ACT: Run the emulator until the test completes or times out

    // We need a timeout to prevent the test runner from freezing if the
    // CPU gets stuck in an infinite loop (which is a common failure mode).
    // 30 million cycles should be more than enough for this test.
    const int TIMEOUT_CYCLES = 30'000'000;
    std::string serial_output;

    for (int cycles_ran = 0; cycles_ran < TIMEOUT_CYCLES; ) {
        cycles_ran += cpu.instructionExecution();

        // Check the serial output after each instruction
        serial_output =  cpu.memoryBus.getSerialOutput();

        // The test is successful if the word "Passed" appears
        if (serial_output.find("Passed") != std::string::npos) {
            break; // Exit the loop, the test has passed
        }

        // The test fails if the word "Failed" appears
        if (serial_output.find("Failed") != std::string::npos) {
            break; // Exit the loop, the test has failed
        }
    }

    // 3. ASSERT: Check the final output

    // For debugging, print the complete serial output.
    // This will only show up if the test fails or if you run with --gtest_print_time
   // RecordProperty("SerialOutput", serial_output);
    std::cout << "TEST STRING "<< (serial_output) << std::endl;
    // The assertion that matters: Did we find "Passed"?
    ASSERT_NE(serial_output.find("Passed"), std::string::npos)
                                << "The test timed out or failed without printing 'Passed'.";
}