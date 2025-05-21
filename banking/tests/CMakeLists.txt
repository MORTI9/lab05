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

target_include_directories(banking_tests
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/mocks
)

target_link_libraries(banking_tests
    PRIVATE banking
    PRIVATE gtest_main
    PRIVATE gmock_main
)

enable_testing()
add_test(NAME banking_tests COMMAND banking_tests)

# Enable coverage
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()
