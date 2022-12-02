cmake_minimum_required(VERSION 3.16.3)
project(TimePerformanceTests VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Test )

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/DataStructures)

set(HEADER_FILES
    BaseTimeTest.hpp
    TestSuites/AggregateTimeTest.hpp
    TestSuites/AllTimeTest.hpp
    TestSuites/AnyTimeTest.hpp
    TestSuites/AtTimeTest.hpp
    TestSuites/AverageTimeTest.hpp
    TestSuites/ForEachTimeTest.hpp
    TestSuites/WhereTimeTest.hpp
    Utilities/Duration.hpp
    Utilities/TimeStats.hpp
    Utilities/TimingTypes.hpp
    Utilities/TimingUtilities.hpp)

add_executable(
    TimePerformanceTests
    
    ../../CustomTestMain.cpp
    AggregateTimeTest.cpp
    AllTimeTest.cpp
    AnyTimeTest.cpp
    AtTimeTest.cpp
    AverageTimeTest.cpp
    ForEachTimeTest.cpp
    WhereTimeTest.cpp

    ${HEADER_FILES}
)

target_link_libraries(TimePerformanceTests
    DataStructures)