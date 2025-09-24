cmake_minimum_required(VERSION 3.10)
project(gtest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(lab1_lib src/lab1.cpp)
add_executable(lab1_exe main.cpp)

target_link_libraries(lab1_exe PRIVATE lab1_lib)

# Добавление тестов
enable_testing()
add_executable(lab1_tests tests/test_lab1.cpp)
target_link_libraries(lab1_tests PRIVATE lab1_lib gtest_main)



include(GoogleTest)
gtest_discover_tests(lab1_tests
  # опционально:
  DISCOVERY_TIMEOUT 60         # если сбока долгая
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# add_test(NAME MyProjectTests COMMAND lab1_tests)