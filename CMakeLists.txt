cmake_minimum_required(VERSION 3.14)
project(BigInteger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-pedantic-errors -gdwarf-4)

include_directories(src)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(biginttest
    src/tests.cc
    src/biginteger.cpp
)
if(UNIX)
  target_link_libraries(biginttest gtest gtest_main pthread)
else()
  target_link_libraries(biginttest gtest gtest_main)
endif()

add_custom_target(test ALL
    COMMENT "Running tests for BigInteger..."
    DEPENDS biginttest
    COMMAND biginttest
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
