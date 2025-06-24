//
// Created by Jas Sobolewski on 2025-06-18.
//
#include <gtest/gtest.h>
#include "../SM83.h" // Including the Cpu class for testing

// Test Class
// environment for each test.
class CPUTest : public ::testing::Test {
protected:
    // This function runs before each test
    void SetUp() override {
        // You can initialize a fresh CPU object here for each test
        cpu = std::make_unique<SM83>();
    }

    // Member variables for the tests to use
    std::unique_ptr<SM83> cpu;
};


// TEST_F is used for tests that use the fixture (CPUTest)
// The first argument is the test suite name, the second is the test name.
TEST_F(CPUTest, RegisterPairing_SetAndGetAF) {
// 1. Arrange - Set up the state
cpu->set_AF(0x1234);//BIG issue is that lower half F is 0

// 2. Act - Perform the action (implicitly done by the getter)

// 3. Assert - Check if the result is what you expect
EXPECT_EQ(cpu->A, 0x12);
EXPECT_EQ(cpu->F, 0x30);
EXPECT_EQ(cpu->AF, 0x1230);//this should be the number if lower half of F is zeroed out
}

TEST_F(CPUTest, FlagManipulation_SetAndGetIndividualFlags) {
// Start with a clean state
cpu->F = 0x00;

// Test setting the Z flag
cpu->setRegisterFlag(SM83::Flag::Z, true);
EXPECT_EQ(cpu->F, 0b10000000); // Check the raw F register value
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::Z)); // Check using the getter
EXPECT_FALSE(cpu->getRegisterFlag(SM83::Flag::N)); // Make sure other flags are untouched

// Test setting the C flag
cpu->setRegisterFlag(SM83::Flag::C, true);
EXPECT_EQ(cpu->F, 0b10010000); // Both Z and C should be set
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::Z));
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::C));

// Test clearing the Z flag
cpu->setRegisterFlag(SM83::Flag::Z, false);
EXPECT_EQ(cpu->F, 0b00010000); // Only C should be left
EXPECT_FALSE(cpu->getRegisterFlag(SM83::Flag::Z));
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::C));
}

TEST_F(CPUTest, FlagManipulation_FlagsAreSetCorrectlyBySetAF) {
// Test a value where Z and C flags should be set
cpu->set_AF(0xFF90); // F = 0x90 = 0b10010000 -> Z is true, N is false, H is false, C is true

EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::Z));
EXPECT_FALSE(cpu->getRegisterFlag(SM83::Flag::N));
EXPECT_FALSE(cpu->getRegisterFlag(SM83::Flag::H));
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::C));
}

TEST_F(CPUTest, FlagManipulation_LowerBitsOfFShouldBeZero) {
// The lower 4 bits of the F register are always 0.
// Your set_af and set_flag methods should enforce this.
    cpu->set_AF(0x12FF); // Try to set F to 0xFF


EXPECT_EQ(cpu->F, 0XF0); //lower half should be zeroed out
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::Z));
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::N));
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::H));
EXPECT_TRUE(cpu->getRegisterFlag(SM83::Flag::C));
}