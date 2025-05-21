cmake_minimum_required(VERSION 3.14)
project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main library
add_library(banking
    src/Account.cpp
    src/Transaction.cpp
)

target_include_directories(banking PUBLIC include)

# Enable testing
option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
