cmake_minimum_required(VERSION 3.14)
project(banking LANGUAGES CXX)

add_library(banking
    src/Account.cpp
    src/Transaction.cpp
)

target_include_directories(banking PUBLIC include)

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
