cmake_minimum_required(VERSION 3.11)
project("Cache")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -DNDEBUG")

SET(MAIN_DIR "main")
SET(INCLUDE_DIR "include")
SET(TESTS_DIR "tests")

add_library(cache_lib INTERFACE)
target_include_directories(cache_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})

add_library(tests_lib INTERFACE)
target_include_directories(tests_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${TESTS_DIR}/${INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})

add_executable(Belady ${MAIN_DIR}/Belady_main.cpp)
target_link_libraries(Belady cache_lib)

add_executable(LFU ${MAIN_DIR}/LFU_main.cpp)
target_link_libraries(LFU cache_lib)

add_executable(Belady_tests ${TESTS_DIR}/${MAIN_DIR}/Belady_tests_main.cpp)
target_link_libraries(Belady_tests tests_lib)

add_executable(LFU_tests ${TESTS_DIR}/${MAIN_DIR}/LFU_tests_main.cpp)
target_link_libraries(LFU_tests tests_lib)

add_executable(efficiency_test ${TESTS_DIR}/${MAIN_DIR}/efficiency_test_main.cpp)
target_link_libraries(efficiency_test tests_lib)