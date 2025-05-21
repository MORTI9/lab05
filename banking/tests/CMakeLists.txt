cmake_minimum_required(VERSION 3.14)

# Загрузка GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Исполняемый файл тестов
add_executable(banking_tests
    AccountTest.cpp
    TransactionTest.cpp
)

# Настройка include
target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
)

# Линковка
target_link_libraries(banking_tests PRIVATE
    banking
    GTest::GTest
    GTest::Main
)

# Явная регистрация тестов
enable_testing()
add_test(NAME banking_tests 
    COMMAND $<TARGET_FILE:banking_tests>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Покрытие кода
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()
