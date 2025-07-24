//
// Created by Jas Sobolewski on 2025-07-10.
//
// In your new test file, e.g., tests/test_cpu_json.cpp

#include <gtest/gtest.h>
#include "json.hpp" // nlohmann/json library
// ... other includes ...
#include "../SM83.h"
#include <fstream>
using json = nlohmann::json;

// Function to run a single JSON test case
void run_json_test_case(const json& test_case) {
    // 1. ARRANGE: Set up the initial state
   SM83 cpu;

    const auto& initial_state = test_case["initial"];

    // Set all registers
    cpu.A = initial_state["a"];
    cpu.F = initial_state["f"];
    cpu.B = initial_state["b"];
    cpu.C = initial_state["c"];
    cpu.D = initial_state["d"];
    cpu.E = initial_state["e"];
    cpu.H = initial_state["h"];
    cpu.L = initial_state["l"];
    cpu.PC = initial_state["pc"];
    cpu.PC = cpu.PC - 1;
    cpu.SP = initial_state["sp"];

    // Set initial RAM state
    for (const auto& ram_entry : initial_state["ram"]) {
        const uint16_t address = ram_entry[0];
        const uint8_t value = ram_entry[1];
        cpu.memoryBus.writeToAddress(address,value);
    }

    // 2. ACT: Execute one single instruction
    cpu.instructionExecution(); // Assuming step() executes one instruction
    cpu.PC++;
    // 3. ASSERT: Compare the result to the final state
    const auto& final_state = test_case["final"];

    EXPECT_EQ(cpu.A, final_state["a"]) << "Register A mismatch";
    EXPECT_EQ(cpu.F, final_state["f"]) << "Register F mismatch";
    EXPECT_EQ(cpu.B, final_state["b"]) << "Register B mismatch";
    EXPECT_EQ(cpu.C, final_state["c"]) << "Register C mismatch";
    EXPECT_EQ(cpu.D, final_state["d"]) << "Register D mismatch";
    EXPECT_EQ(cpu.E, final_state["e"]) << "Register E mismatch";
    EXPECT_EQ(cpu.H, final_state["h"]) << "Register H mismatch";
    EXPECT_EQ(cpu.L, final_state["l"]) << "Register L mismatch";
    EXPECT_EQ(cpu.PC, final_state["pc"]) << "Program Counter PC mismatch";
    EXPECT_EQ(cpu.SP, final_state["sp"]) << "Stack Pointer SP mismatch";

    // Assert final RAM state
    for (const auto& ram_entry : final_state["ram"]) {
        uint16_t address = ram_entry[0];
        uint8_t expected_value = ram_entry[1];
        EXPECT_EQ(cpu.memoryBus.returnAddress(address), expected_value)
            << "RAM mismatch at address 0x" << std::hex << address;
    }
}


// In the same test file...

// This fixture will run tests for a given JSON opcode file
class JsonOpcodeTest : public ::testing::Test,
                       public ::testing::WithParamInterface<const char*> {};

TEST_P(JsonOpcodeTest, PassesAllScenarios) {
    // Get the JSON filename for this test run
    const char* filename = GetParam();
    const std::string full_path = "../cpu_tests/json_tests/" + std::string(filename);

    std::ifstream f(full_path);
    if (!f.is_open()) {
        FAIL() << "Could not open JSON test file: " << full_path;
    }

    json test_data = json::parse(f);

    // Iterate through every test case in the JSON file
    for (const auto& test_case : test_data) {
        // Use a GTest "sub-test" to get detailed failure info
        // This tells you the *name* of the specific scenario that failed.
        SCOPED_TRACE("Test Case: " + test_case["name"].get<std::string>());
        run_json_test_case(test_case);
    }
}

INSTANTIATE_TEST_SUITE_P(
    CPU_JSON_Tests,
    JsonOpcodeTest,
    ::testing::Values(
        "00.json", // NOP
        "01.json", //
        "02.json", //
        "03.json",
        "04.json",
        "05.json",
        "06.json",
        "07.json",
        "08.json",
        "09.json",
        "0A.json",
        "0B.json",
        "0C.json",
        "0D.json",
        "0E.json",
        "0F.json",
        "11.json",
        "12.json",
        "14.json", //
        "15.json",
        "16.json",
        "17.json",
        "18.json",
        "19.json",
        "1A.json",
        "1B.json",
        "1C.json",
        "1D.json",
        "1E.json",
        "1F.json",
        "20.json",
        "24.json", //
        "25.json",
        "30.json",
        "80.json",
        "90.json",
        "c0.json",
        "C1.json",//
        "C5.json",
        "D1.json",
        "D5.json",
        "E1.json",
        "E5.json",
        "F1.json",
        "F5.json"

    )
);
