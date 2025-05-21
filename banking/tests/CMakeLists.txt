cmake_minimum_required(VERSION 3.14)

find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

add_executable(banking_tests
    AccountTest.cpp
    TransactionTest.cpp
)

target_include_directories(banking_tests
    PRIVATE /include
    PRIVATE /tests/mocks
)

target_link_libraries(banking_tests
    PRIVATE banking
    PRIVATE GTest::GTest
    PRIVATE GMock::GMock
)

enable_testing()
add_test(NAME banking_tests COMMAND banking_tests)
