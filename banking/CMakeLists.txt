cmake_minimum_required(VERSION 3.14)
project(banking LANGUAGES CXX)

# Основная библиотека
add_library(banking STATIC
    src/Account.cpp
    src/Transaction.cpp
)

target_include_directories(banking PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Тесты
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
