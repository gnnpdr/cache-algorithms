cmake_minimum_required(VERSION 3.11)
project("Cache")

SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(MAIN_DIR "main")
SET(INCLUDE_DIR "include")

add_library(cache_lib INTERFACE)
target_include_directories(cache_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR})

target_compile_options(cache_lib INTERFACE $<$<CONFIG:Release>:-O3 -march=native -DNDEBUG> $<$<CONFIG:Debug>:-g -O0>)

add_executable(Belady ${MAIN_DIR}/Belady_main.cpp)
target_link_libraries(Belady cache_lib)

add_executable(LFU ${MAIN_DIR}/LFU_main.cpp)
target_link_libraries(LFU cache_lib)