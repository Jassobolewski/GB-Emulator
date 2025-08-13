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
//        "00.json", // NOP
//        "01.json", //
//        "02.json", //
//        "03.json",
//        "04.json",
//        "05.json",
//        "06.json",
//        "07.json",
//        "08.json",
//        "09.json",
//        "0A.json",
//        "0B.json",
//        "0C.json",
//        "0D.json",
//        "0E.json",
//        "0F.json",
//
//        "11.json",
//        "12.json",
//        "14.json", //
//        "15.json",
//        "16.json",
//        "17.json",
//        "18.json",
//        "19.json",
//        "1A.json",
//        "1B.json",
//        "1C.json",
//        "1D.json",
//        "1E.json",
//        "1F.json",
//
//        "20.json",
//        "21.json",
//        "22.json",
//        "23.json",
//        "24.json", //
//        "25.json",
//        "27.json",
//        "28.json",
//        "29.json",
//        "2A.json",
//        "2B.json",
//        "2C.json",
//        "2D.json",
//        "2E.json",
//        "2F.json",
//
//        "30.json",
//        "31.json",
//        "32.json",
//        "33.json",
//        "34.json",
//        "35.json",
//        "36.json",
//        "37.json",
//        "38.json",
//        "39.json",
//        "3A.json",
//        "3B.json",
//        "3C.json",
//        "3D.json",
//        "3E.json",
//        "3F.json",
//
//        "40.json",
//        "41.json",
//        "42.json",
//        "43.json",
//        "44.json",
//        "45.json",
//        "46.json",
//        "47.json",
//        "48.json",
//        "49.json",
//        "4A.json",
//        "4B.json",
//        "4C.json",
//        "4D.json",
//        "4E.json",
//        "4F.json",
//
//        "50.json",
//        "51.json",
//        "52.json",
//        "53.json",
//        "54.json",
//        "55.json",
//        "56.json",
//        "57.json",
//        "58.json",
//        "59.json",
//        "5A.json",
//        "5B.json",
//        "5C.json",
//        "5D.json",
//        "5E.json",
//        "5F.json",
//
//        "60.json",
//        "61.json",
//        "62.json",
//        "63.json",
//        "64.json",
//        "65.json",
//        "66.json",
//        "67.json",
//        "68.json",
//        "69.json",
//        "6A.json",
//        "6B.json",
//        "6C.json",
//        "6D.json",
//        "6E.json",
//        "6F.json",
//
//        "70.json",
//        "71.json",
//        "72.json",
//        "73.json",
//        "74.json",
//        "75.json",//halt doesnt exist 0x76
//        "77.json",
//        "78.json",
//        "79.json",
//        "7A.json",
//        "7B.json",
//        "7C.json",
//        "7D.json",
//        "7E.json",
//        "7F.json",
//
//        "80.json",
//        "81.json",
//        "82.json",
//        "83.json",
//        "84.json",
//        "85.json",
//        "86.json",
//        "87.json",
//        "88.json",
//        "89.json",
//        "8A.json",
//        "8B.json",
//        "8C.json",
//        "8D.json",
//        "8E.json",
//        "8F.json",
//
//        "90.json",
//        "91.json",
//        "92.json",
//        "93.json",
//        "94.json",
//        "95.json",
//        "96.json",
//        "97.json",
//        "98.json",
//        "99.json",
//        "9A.json",
//        "9B.json",
//        "9C.json",
//        "9D.json",
//        "9E.json",
//        "9F.json",
//
//        "A0.json",
//        "A1.json",
//        "A2.json",
//        "A3.json",
//        "A4.json",
//        "A5.json",
//        "A6.json",
//        "A7.json",
//        "A8.json",
//        "A9.json",
//        "AA.json",
//        "AB.json",
//        "AC.json",
//        "AD.json",
//        "AE.json",
//        "AF.json",
//
//        "B0.json",
//        "B1.json",
//        "B2.json",
//        "B3.json",
//        "B4.json",
//        "B5.json",
//        "B6.json",
//        "B7.json",
//        "B8.json",
//        "B9.json",
//        "BA.json",
//        "BB.json",
//        "BC.json",
//        "BD.json",
//        "BE.json",
//        "BF.json",
//
//        "c0.json",
//        "C1.json",//
//        "C2.json",//
//        "C3.json",//
//        "C4.json",//
//        "C5.json",
//        "C6.json",
//        "C7.json",
//        "C8.json",
//        "C9.json",//
//        "CA.json",//skip CB for now
//        "CC.json",
//        "CD.json",
//        "CE.json",
//        "CF.json",
//
//
//        "D1.json",
//        "D2.json",
//        "D4.json",
//        "D5.json",
//        "D6.json",
//        "D7.json",
//        "D8.json",
//        "D9.json",
//        "DA.json",
//        "DC.json",
//        "DE.json",
//        "DF.json",
//
//        "E0.json",
//        "E1.json",
//        "E2.json",
//        "E5.json",
//        "E6.json",
//        "E7.json",
//        "E8.json",
//        "E9.json",
//        "EA.json",
//        "EE.json",
//        "EF.json",
//
//        "F0.json",
//        "F1.json",
//        "F5.json",
//        "F6.json",
//        "F7.json",
//        "F8.json",
//        "F9.json",
//        "FA.json",
//        "FE.json",
//        "FF.json"
            "part_0.json",
            "part_1.json",
            "part_2.json",
            "part_3.json"
    )
);
