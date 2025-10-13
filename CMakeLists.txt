cmake_minimum_required(VERSION 3.11)
project("Cache")

SET(SRC_DIR "src")
SET(SRCS 
    ${SRC_DIR}/Belady.cpp
    ${SRC_DIR}/LFU.cpp
    ${SRC_DIR}/tests.cpp
)
add_library(lib STATIC ${SRCS})
target_include_directories(lib PUBLIC "include")

add_executable(prog main.cpp)
target_link_libraries(prog PRIVATE lib)     #делаем ссылку на библиотеку, чтобы можно было скомпилировать cpp файлы из нее