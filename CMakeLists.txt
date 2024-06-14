cmake_minimum_required(VERSION 3.1)
project(ToDo)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/gui.cpp src/table.cpp src/todo.cpp)

# target_compile_options(main PRIVATE -g)
