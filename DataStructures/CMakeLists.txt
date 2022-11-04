set(HEADER_FILES 
    Animal.hpp
    AnimalLibrary.hpp
    Person.hpp
    PersonAndPetLibrary.hpp
    PersonLibrary.hpp)

add_library(
    DataStructures
    
    Animal.cpp
    AnimalLibrary.cpp
    Person.cpp
    PersonAndPetLibrary.cpp
    PersonLibrary.cpp
    
    ${HEADER_FILES})
    
target_include_directories(DataStructures PRIVATE ${PROJECT_SOURCE_DIR}/DataStructures)