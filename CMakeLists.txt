cmake_minimum_required(VERSION 3.11)
project("Cache")

SET(SRC_DIR "src")
SET(MAIN_DIR "main")
SET(INCLUDE_DIR "include")
SET(TESTS_DIR "tests")

SET(SRCS 
    ${SRC_DIR}/Belady.cpp
    ${SRC_DIR}/LFU.cpp
)
add_library(cache_lib STATIC ${SRCS})
target_include_directories(cache_lib PUBLIC ${INCLUDE_DIR})

add_library(common_lib INTERFACE)
target_include_directories(common_lib INTERFACE ${INCLUDE_DIR})

add_library(tests_lib INTERFACE)
target_include_directories(tests_lib INTERFACE ${TESTS_DIR}/${INCLUDE_DIR})

add_executable(Belady ${SRC_DIR}/${MAIN_DIR}/Belady_main.cpp)
target_link_libraries(Belady PRIVATE cache_lib common_lib)

add_executable(LFU ${SRC_DIR}/${MAIN_DIR}/LFU_main.cpp)
target_link_libraries(LFU PRIVATE cache_lib common_lib)

add_executable(Belady_tests ${TESTS_DIR}/${MAIN_DIR}/Belady_tests_main.cpp)
target_link_libraries(Belady_tests PRIVATE cache_lib common_lib tests_lib)

add_executable(LFU_tests ${TESTS_DIR}/${MAIN_DIR}/LFU_tests_main.cpp)
target_link_libraries(LFU_tests PRIVATE cache_lib common_lib tests_lib)

add_executable(efficiency_test ${TESTS_DIR}/${MAIN_DIR}/efficiency_test_main.cpp)
target_link_libraries(efficiency_test PRIVATE cache_lib common_lib tests_lib)