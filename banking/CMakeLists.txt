cmake_minimum_required(VERSION 3.14)
project(banking LANGUAGES CXX)

add_library(banking STATIC
    src/Account.cpp
    src/Transaction.cpp
)

target_include_directories(banking PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
