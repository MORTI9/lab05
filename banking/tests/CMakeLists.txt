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

target_link_libraries(banking_tests PRIVATE
    banking
    gtest_main
    gmock_main
)

enable_testing()

# Явно регистрируем тестовый исполняемый файл
add_test(NAME banking_tests 
    COMMAND banking_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Альтернативно можно регистрировать отдельные тестовые случаи
function(add_gtest TEST_NAME)
    add_test(NAME ${TEST_NAME}
        COMMAND banking_tests --gtest_filter=${TEST_NAME}*
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endfunction()

add_gtest(AccountTest)
add_gtest(TransactionTest)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()
