cmake_minimum_required(VERSION 3.16.3)
project(FunctionalTests VERSION 1.0)

include(FetchContent)
include(CTest)
include(GoogleTest)

set(CMAKE_BUILD_TYPE Debug)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/DataStructures
    ${PROJECT_SOURCE_DIR}/CppQueryableTest/Functional/Headers)

enable_testing()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Test )
add_executable(
    FunctionalTests
    
    AggregateFunctionalTest.cpp
    AllFunctionalTest.cpp
    AnyFunctionalTest.cpp
    AtFunctionalTest.cpp
    AverageFunctionalTest.cpp
    ContainsFunctionalTest.cpp
    CountFunctionalTest.cpp
    CountIfFunctionalTest.cpp
    EqualFunctionalTest.cpp
    ExceptFunctionalTest.cpp
    FirstFunctionalTest.cpp
    ForEachFunctionalTest.cpp
    GroupByFunctionalTest.cpp
    JoinFunctionalTest.cpp
    LastFunctionalTest.cpp
    MaxFunctionalTest.cpp
    MinFunctionalTest.cpp
    RangeFunctionalTest.cpp
    SelectFunctionalTest.cpp
    SkipFunctionalTest.cpp
    SkipWhileFunctionalTest.cpp
    SortFunctionalTest.cpp
    SumFunctionalTest.cpp
    TakeFunctionalTest.cpp
    TakeWhileFunctionalTest.cpp
    WhereFunctionalTest.cpp)

    
add_executable(
    DetachedFunctionalTests
    
    DetachedMain.cpp
    AggregateFunctionalTest.cpp
    AllFunctionalTest.cpp
    AnyFunctionalTest.cpp
    AtFunctionalTest.cpp
    AverageFunctionalTest.cpp
    ContainsFunctionalTest.cpp
    CountFunctionalTest.cpp
    CountIfFunctionalTest.cpp
    EqualFunctionalTest.cpp
    ExceptFunctionalTest.cpp
    FirstFunctionalTest.cpp
    ForEachFunctionalTest.cpp
    GroupByFunctionalTest.cpp
    JoinFunctionalTest.cpp
    LastFunctionalTest.cpp
    MaxFunctionalTest.cpp
    MinFunctionalTest.cpp
    RangeFunctionalTest.cpp
    SelectFunctionalTest.cpp
    SkipFunctionalTest.cpp
    SkipWhileFunctionalTest.cpp
    SortFunctionalTest.cpp
    SumFunctionalTest.cpp
    TakeFunctionalTest.cpp
    TakeWhileFunctionalTest.cpp
    WhereFunctionalTest.cpp)

# important for this to go after add_executable and find_package
target_link_libraries(FunctionalTests PRIVATE
    GTest::gtest_main
    DataStructures)

target_link_libraries(DetachedFunctionalTests PRIVATE
    GTest::gtest_main
    DataStructures)

gtest_discover_tests(FunctionalTests)