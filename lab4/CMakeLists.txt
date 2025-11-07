cmake_minimum_required(VERSION 3.20)

project(lab4
  LANGUAGES C CXX
)

# Стандарты
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(lab4_lib STATIC
  figures.cpp
)
target_include_directories(lab4_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(lab4_exe
  main.cpp
)
target_link_libraries(lab4_exe PRIVATE
  lab4_lib
)

# # ===== Тесты =====
enable_testing()

add_executable(lab4_tests
  tests/test_lab4.cpp
)
target_link_libraries(lab4_tests PRIVATE
  lab4_lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab4_tests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DISCOVERY_TIMEOUT 60
)

# (не обязательно)
# add_test(NAME MyProjectTests COMMAND lab2_tests)
