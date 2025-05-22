cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Создаем тестовый исполняемый файл
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

# Включаем систему тестирования
enable_testing()

# Регистрируем тестовые случаи
add_test(
    NAME AccountTests
    COMMAND banking_tests --gtest_filter=AccountTest*
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(
    NAME TransactionTests
    COMMAND banking_tests --gtest_filter=TransactionTest*
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Альтернативный вариант - регистрация всех тестов
add_test(
    NAME AllTests
    COMMAND banking_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()
