cmake_minimum_required(VERSION 3.12)
project(app VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
find_package(Boost 1.75 REQUIRED COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
else(Boost_FOUND)
    message(FATAL_ERROR "Cannot build Program_options without Boost. Please set Boost_DIR.")
endif(Boost_FOUND)

set(SOURCE_FILES main.cpp)

add_library(
    analyzer
    analyzer.h
    analyzer.cpp 
)
 
add_library(
    dependencyTree
    dependencyTree.h
    dependencyTree.cpp
)


add_library(
    dependencyParser
    dependencyParser.h
    dependencyParser.cpp
)

add_library(
    document
    document.h
    document.cpp
)


add_executable(app ${SOURCE_FILES})

target_link_libraries(app PRIVATE analyzer document dependencyTree dependencyParser)