cmake_minimum_required(VERSION 3.11)
project("Cache")

SET(SRC_DIR "src")
SET(INCLUDE_DIR "include")
SET(SRCS 
    ${SRC_DIR}/Belady.cpp
    ${SRC_DIR}/LFU.cpp
)
add_library(common_lib STATIC ${SRCS})
target_include_directories(lib PUBLIC INCLUDE_DIR)

SET(TESTS_DIR "tests")
SET(TESTS_SRC
    ${TESTS_DIR}/${SRC_DIR}/tests.cpp
)
add_library(tests_lib STATIC ${TESTS_SRC}/${SRC_DIR})
target_include_directories(tests_lib PUBLIC ${TESTS_DIR}/${INCLUDE_DIR})

add_executable(Belady Belady_main.cpp)
target_link_libraries(Belady PRIVATE common_lib)

add_executable(LFU LFU_main.cpp)
target_link_libraries(LFU PRIVATE common_lib)

add_executable(Belady_tests ${TESTS_DIR}/Belady_tests_main.cpp)
target_link_libraries(Belady_tests PRIVATE common_lib tests_lib)

add_executable(LFU_tests ${TESTS_DIR}/LFU_tests_main.cpp)
target_link_libraries(LFU_tests PRIVATE common_lib tests_lib)