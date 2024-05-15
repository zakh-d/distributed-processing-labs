cmake_minimum_required(VERSION 3.10)

project(lab1 VERSION 1.0)

add_executable(lab1 main.c double_linked_list.c)
target_include_directories(lab1 PUBLIC
                           "${PROJECT_BINARY_DIR}")