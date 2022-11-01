cmake_minimum_required(VERSION 3.16.3)
project(CppQueryable VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_PARALLEL_LEVEL 6)

add_subdirectory(DataStructures)
add_subdirectory(CppQueryableTest/Queryable/Functional)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/DataStructures
    ${PROJECT_SOURCE_DIR}/CppQueryableTest/Queryable/Functional)
    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin )
add_executable(
    CppQueryable
    
    main.cpp)

# important for this to go after add_executable and find_package
target_link_libraries(CppQueryable PRIVATE
    DataStructures)