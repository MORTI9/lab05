cmake_minimum_required(VERSION 3.14)

# Настройка GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Создание тестового исполняемого файла
add_executable(banking_tests
    AccountTest.cpp
    TransactionTest.cpp
)

# Настройка include директорий
target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
)

# Линковка библиотек
target_link_libraries(banking_tests PRIVATE
    banking
    gtest
    gmock
    gtest_main
)

# Явная регистрация тестов
enable_testing()
add_test(NAME RunBankingTests COMMAND banking_tests)

# Альтернативный вариант с явным указанием тестов
function(add_gtest TEST_NAME)
    add_test(NAME ${TEST_NAME} 
        COMMAND banking_tests --gtest_filter=${TEST_NAME}*
    )
endfunction()

add_gtest(AccountTest)
add_gtest(TransactionTest)

# Настройка покрытия кода
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
endif()
