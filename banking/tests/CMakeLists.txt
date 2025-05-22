cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(banking_tests
    AccountTest.cpp
    TransactionTest.cpp
)

target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
)

# Исправленные цели линковки
target_link_libraries(banking_tests PRIVATE
    banking
    gtest
    gmock
    gtest_main
)

enable_testing()

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(banking_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()
