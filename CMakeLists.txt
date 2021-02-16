cmake_minimum_required(VERSION 3.5)

project(Logger LANGUAGES CXX)


find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_options(-Werror=return-type)                   # error on missing return type
add_compile_options(-Werror=format)                        # error on wrong printf formats
add_compile_options(-Werror=parentheses)                   # error when using ambiguous syntax

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Logger main.cpp
               src/Processor.cpp
               src/Loader.cpp
               src/Logger.cpp)

target_link_libraries(Logger Threads::Threads)
