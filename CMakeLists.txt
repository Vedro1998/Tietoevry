cmake_minimum_required(VERSION 3.22)
project(TietoevryRecruitmentTask)

include_directories(./lib/)
add_executable(grepr 
               main.cpp
               ArgParser.cpp
               OutPrinter.cpp
               lib/utils.cpp
               search.cpp)