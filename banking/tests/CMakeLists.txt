cmake_minimum_required(VERSION 3.14)

# Загрузка GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Создаем исполняемый файл тестов
add_executable(banking_tests
  AccountTest.cpp
  TransactionTest.cpp
)

# Настройка include директорий
target_include_directories(banking_tests
  PRIVATE ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CMAKE_SOURCE_DIR}/tests/mocks
  PRIVATE ${gtest_SOURCE_DIR}/include
)

# Линковка библиотек
target_link_libraries(banking_tests
  PRIVATE banking
  PRIVATE gtest
  PRIVATE gmock
  PRIVATE gtest_main
)

# Регистрация тестов
enable_testing()
add_test(NAME banking_tests COMMAND banking_tests)

# Покрытие кода
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(banking_tests PRIVATE --coverage)
  target_link_options(banking_tests PRIVATE --coverage)
endif()
