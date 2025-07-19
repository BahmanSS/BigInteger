cmake_minimum_required(VERSION 3.14)
project(BigInteger)
set(CMAKE_CXX_STANDARD 20)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare( googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable( BItests
 test/bi_test.cpp
 src/biginteger.cpp
 )

target_link_libraries(BItests gtest gtest_main)

add_custom_target(test ALL
    COMMENT "Running tests for BigInteger..." # коментарий в начале
    DEPENDS BItests# что должно быть выполнено сначала
    COMMAND BItests# что нужно выполнить
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR} # говорит из какой директории запускать команду
    # ${CMAKE_BINARY_DIR} - корневая директория сборки (./build) - обычно
)
