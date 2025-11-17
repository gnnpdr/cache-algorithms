cmake_minimum_required(VERSION 3.11)
project("CacheTests")

SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(MAIN_DIR "main")
SET(INCLUDE_DIR "include")
SET(TESTS_DIR "tests")

add_library(tests_lib INTERFACE)
target_include_directories(tests_lib INTERFACE ${CMAKE_SOURCE_DIR}/../${INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR})

target_compile_options(tests_lib INTERFACE $<$<CONFIG:Release>:-O3 -march=native -DNDEBUG> $<$<CONFIG:Debug>:-g -O0>)

add_executable(Belady_tests ${MAIN_DIR}/Belady_tests_main.cpp)
target_link_libraries(Belady_tests tests_lib)

add_executable(LFU_tests ${MAIN_DIR}/LFU_tests_main.cpp)
target_link_libraries(LFU_tests tests_lib)

add_executable(efficiency_test ${MAIN_DIR}/efficiency_test_main.cpp)
target_link_libraries(efficiency_test tests_lib)