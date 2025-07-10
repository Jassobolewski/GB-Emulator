#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <vector>
#include <string>

// Include your emulator's components
#include "../SM83.h"
#include "../MMU.h"

// =====================================================================================
// 1. CONFIGURATION
// =====================================================================================

// Define the path to your ROMs directory.
// Using a relative path from the build directory is more portable than an absolute path.
// Adjust this if your build directory is not at the root of your project.
const std::string ROM_PATH_PREFIX = "../../roms/";


// =====================================================================================
// 2. CORE TEST HELPER FUNCTION
// This function contains the logic to run any given Blargg test ROM.
// =====================================================================================

std::string runBlarggRom(const std::string& rom_filename, const int timeout_cycles) {
    // ARRANGE: Create components and load the specified ROM
    auto cpu = std::make_unique<SM83>(); // Assumes SM83 creates its own MMU

    std::ifstream rom_file(rom_filename, std::ios::binary);
    if (!rom_file.is_open()) {
        ADD_FAILURE() << "Could not open Blargg test ROM: " << rom_filename;
        return "ROM_FILE_NOT_FOUND";
    }

    std::vector<uint8_t> rom_data(
        (std::istreambuf_iterator<char>(rom_file)),
        std::istreambuf_iterator<char>()
    );
    rom_file.close();

    cpu->memoryBus.loadRom(rom_data);
    cpu->PC = 0x100;

    // ACT: Run the emulator until the test completes or times out
    std::string final_output = "TIMEOUT";
    for (int cycles_ran = 0; cycles_ran < timeout_cycles; ) {
        cycles_ran += cpu->instructionExecution();

        std::string current_output = cpu->memoryBus.getSerialOutput();
        if (current_output.find("Passed") != std::string::npos ||
            current_output.find("Failed") != std::string::npos) {
            final_output = current_output;
            break;
        }
    }

    // RETURN: The final captured output
    return final_output;
}


// =====================================================================================
// 3. INDIVIDUAL ROM TESTS (Parameterized Test Suite)
// This suite tests each of the smaller `cpu_instrs` ROMs one by one.
// =====================================================================================

class BlarggIndividualTest : public ::testing::Test {};
const int timeout = 40'000'000; // The full test needs a longer timeout
TEST_F(BlarggIndividualTest, Passes_01_special) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "01-special.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_03_op_sp_hl) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "03-op sp,hl.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_04_op_r_imm) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "04-op r,imm.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_05_op_rp) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "05-op rp.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_06_ld_r_r) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "06-ld r,r.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_07_jr_jp_call_ret_rst) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "07-jr,jp,call,ret,rst.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_08_misc_instrs) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "08-misc instrs.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_09_op_r_r) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "09-op r,r.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_10_bit_ops) {
    std::string result = runBlarggRom(ROM_PATH_PREFIX + "10-bit ops.gb",timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}

TEST_F(BlarggIndividualTest, Passes_11_op_a_hl) {
    std::string result = runBlarggRom((ROM_PATH_PREFIX + "11-op a,(hl).gb"),timeout);
    EXPECT_NE(result.find("Passed"), std::string::npos) << "Full output:\n" << result;
}



// =====================================================================================
// 4. COMBINED ROM TEST (Simple Test Suite)
// This suite tests the full, combined `cpu_instrs.gb` ROM.
// =====================================================================================

class BlarggCombinedTest : public ::testing::Test {};

TEST_F(BlarggCombinedTest, FullCpuInstrsRom) {
    const std::string full_rom_path = ROM_PATH_PREFIX + "cpu_instrs.gb";
    const int timeout = 40'000'000; // The full test needs a longer timeout

    // Run the ROM using our helper function
    std::string result = runBlarggRom(full_rom_path, timeout);

    // Print the result for immediate feedback
    std::cout << "\n--- Full cpu_instrs.gb Output ---\n"
              << result
              << "\n---------------------------------\n";

    // Record the full output for test reports
    RecordProperty("SerialOutput", result);

    // ASSERT: Check that the result contains "Passed"
    EXPECT_NE(result.find("Passed"), std::string::npos)
        << "The full cpu_instrs test did not pass.";
}