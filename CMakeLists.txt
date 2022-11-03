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
    
set(HEADER_FILES
    DataStructures/Animal.hpp
    DataStructures/AnimalLibrary.hpp
    DataStructures/Base.hpp
    DataStructures/Derived.hpp
    DataStructures/DogWalker.hpp
    DataStructures/Gender.hpp
    DataStructures/People.hpp
    DataStructures/Person.hpp
    DataStructures/PersonAndPet.hpp
    DataStructures/PersonAndPetLibrary.hpp
    DataStructures/PersonLibrary.hpp
    DataStructures/Point.hpp
    Queryable/IBaseQueryable.hpp
    Queryable/InternalQueryable.hpp
    Queryable/InternalQueryables/DequeInternalQueryable.hpp
    Queryable/InternalQueryables/ListInternalQueryable.hpp
    Queryable/InternalQueryables/MapInternalQueryable.hpp
    Queryable/InternalQueryables/MultiSetInternalQueryable.hpp
    Queryable/InternalQueryables/QueryableForwardDeclare.hpp
    Queryable/InternalQueryables/SetInternalQueryable.hpp
    Queryable/InternalQueryables/SortedInternalQueryable.hpp
    Queryable/InternalQueryables/VectorInternalQueryable.hpp
    Queryable/IQueryable.hpp
    Queryable/ISortedQueryable.hpp
    Queryable/Iterators/IteratorType.hpp
    Queryable/Iterators/QueryableIterator.hpp
    Queryable/Queryable.hpp
    Queryable/QueryableAliases.hpp
    Queryable/QueryableData/ConstRandomAccessQueryableData.hpp
    Queryable/QueryableData/IQueryableData.hpp
    Queryable/QueryableData/QueryableData.hpp
    Queryable/QueryableData/QueryableDequeData.hpp
    Queryable/QueryableData/QueryableListData.hpp
    Queryable/QueryableData/QueryableMapData.hpp
    Queryable/QueryableData/QueryableMultiSetData.hpp
    Queryable/QueryableData/QueryableSetData.hpp
    Queryable/QueryableData/QueryableVectorData.hpp
    Queryable/QueryableData/RandomAccessQueryableData.hpp
    Queryable/QueryableData/SelectQueryableData/SelectQueryableData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableDequeData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableListData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableMapData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableMultiSetData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableSetData.hpp
    Queryable/QueryableData/SkipWhileQueryableData/SkipWhileQueryableVectorData.hpp
    Queryable/QueryableData/SortedQueryableData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableDequeData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableListData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableMapData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableMultiSetData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableSetData.hpp
    Queryable/QueryableData/TakeWhileQueryableData/TakeWhileQueryableVectorData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableDequeData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableListData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableMapData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableMultiSetData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableSetData.hpp
    Queryable/QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp
    Queryable/QueryablesForwardDeclarations.hpp
    Queryable/QueryableType.hpp
    Queryable/QueryBuilder.hpp
    Queryable/Sorters/DequeSorter.hpp
    Queryable/Sorters/ISorter.hpp
    Queryable/Sorters/ListSorter.hpp
    Queryable/Sorters/Sorter.hpp
    Queryable/Sorters/VectorSorter.hpp
    Queryable/TypeConstraintUtil.hpp
    Queryable/Utilities/Backtrace.hpp
    Queryable/Utilities/Casting.hpp
    Queryable/Utilities/Condition.hpp
    Queryable/Utilities/Grouping.hpp
    Queryable/Utilities/IWhileCondition.hpp
    Queryable/Utilities/PersistentContainer.hpp
    Queryable/Utilities/StaticBuilders/InternalQueryableStaticBuilder.hpp
    Queryable/Utilities/StaticBuilders/QueryableStaticBuilder.hpp
    Queryable/Utilities/WhileCondition.hpp)

    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin )
add_executable(
    CppQueryable
    
    main.cpp
    
    # don't actually want these in here, but helps with development
    ${HEADER_FILES})

target_include_directories(CppQueryable PRIVATE ${HEADER_FILES})

# important for this to go after add_executable and find_package
target_link_libraries(CppQueryable PRIVATE
    DataStructures)