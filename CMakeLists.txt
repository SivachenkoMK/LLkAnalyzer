cmake_minimum_required(VERSION 3.26)
project(LLkAnalyzer)

set(CMAKE_CXX_STANDARD 17)

add_executable(LLkAnalyzer main.cpp
        grammar.cpp
        grammar.h
        transition.cpp
        transition.h)
