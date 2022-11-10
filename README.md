Currently being used for notes...

cpp-like functions already exist for most of the common funcitonalities:  
https://en.cppreference.com/w/cpp/algorithm

- These functions are highly optimized and should be used for most simple situations
- These functions use templated parameters instead of std::function which performs much better but is more difficult to understand and maintain
    - CppQueryable will probably have to move to doing this as well in order to keep up
- Some of these functionalities are not available in C++11 and CppQueryable is currently aimed at C++11
- CppQueryable is a convenience wrapper that allows you to chain funcitonalities while persisting time complexity
- CppQueryable has performance overhead for both memory and time (note, time overhead does not mean increase in time complexity)
- CppQueryable should never be used for projects with strict time/memory constraints
- Performance specifics will be made public as data is gathered and formalized
- CppQueryable is not currently using SIMD methods, but will be in the future to increase performance
- I wrote the majority of CppQueryable before realizing this algorithm library had all these functionalities
