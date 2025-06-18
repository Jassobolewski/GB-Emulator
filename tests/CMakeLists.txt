# tests/CMakeLists.txt

# Create the executable for our tests
add_executable(run_tests test_cpu.cpp)

# Link our main CPU code to the tests so we can test it
# Using target_sources() is a modern way to do this.
# This assumes your CPU class is in SM83.h/cpp.
target_sources(run_tests PRIVATE
        ../SM83.cpp
)

# --- THE FIX IS HERE ---
# When you link against GoogleTest, it knows about its own source files,
# but your target `run_tests` also needs to know where to find the headers
# (`gtest/gtest.h`). The variable `${googletest_SOURCE_DIR}/googletest/include`
# points to exactly that directory.
target_include_directories(run_tests PRIVATE
        ${googletest_SOURCE_DIR}/googletest/include
        ${googletest_SOURCE_DIR}/googlemock/include # Also good to include mock headers
)

# Link GoogleTest to our test executable
# GTest::gtest_main includes both gtest and a pre-written main() function.
target_link_libraries(run_tests PRIVATE GTest::gtest_main)

# Tell CTest (CMake's test runner) about our test executable
include(GoogleTest)
gtest_add_tests(TARGET run_tests)