cmake_minimum_required(VERSION 3.16.3)
project(TimePerformanceTests VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin/Test )

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/DataStructures)

set(HEADER_FILES
    BaseTimeTest.hpp
    TestSuites/AnyTimeTest.hpp
    TestSuites/ForEachTimeTest.hpp
    TestSuites/WhereTimeTest.hpp
    Utilities/Duration.hpp
    Utilities/TimeStats.hpp
    Utilities/TimingTypes.hpp
    Utilities/TimingUtilities.hpp)

add_executable(
    TimePerformanceTests
    
    ../../CustomTestMain.cpp
    AnyTimeTest.cpp
    ForEachTimeTest.cpp
    WhereTimeTest.cpp

    ${HEADER_FILES}
)

target_link_libraries(TimePerformanceTests
    DataStructures)