cmake_minimum_required(VERSION 3.20)
project(SVector LANGUAGES CXX)

# --- Compiler setup ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Source & header setup ---
add_executable(implementation implementation/implementation.cpp)
target_include_directories(implementation PRIVATE header)

# --- GoogleTest setup via FetchContent ---
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Untuk menghindari warning saat install system-wide
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Testing setup ---
include(CTest)
enable_testing()

add_executable(vector_test testing/testing.cpp)
target_include_directories(vector_test PRIVATE header)
target_link_libraries(vector_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(vector_test)
