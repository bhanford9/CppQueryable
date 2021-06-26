#ifndef CPPQUERYABLE_QUERYABLE_TYPECONSTRAINTUTIL_H
#define CPPQUERYABLE_QUERYABLE_TYPECONSTRAINTUTIL_H

#include <type_traits>
#include <utility>

template <class...> using void_t = void;

struct has_begin_end_impl {
  template<typename T, typename Begin = decltype(std::declval<const T&>().begin()),
                       typename End   = decltype(std::declval<const T&>().end())>
  static std::true_type test(int);
  template<typename...>
  static std::false_type test(...);
};

template<typename T>
struct can_iterate : decltype(has_begin_end_impl::test<T>(0)) {};

template<typename T, typename = void>
struct is_less_comparable : std::false_type { };
template<typename T>
struct is_less_comparable<T, void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

template<typename T, typename = void>
struct is_equatable : std::false_type { };
template<typename T>
struct is_equatable<T, void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

template<typename T, typename = void>
struct is_aggregatable : std::false_type { };
template<typename T>
struct is_aggregatable<T, void_t<decltype(std::declval<T>() += std::declval<T>())>> : std::true_type {};

template<typename T, typename = void>
struct is_addable : std::false_type { };
template<typename T>
struct is_addable<T, void_t<decltype(std::declval<T>() + std::declval<T>())>> : std::true_type {};

template<typename T, typename = void>
struct has_size_method : std::false_type { };
template<typename T>
struct has_size_method<T, void_t<decltype(std::declval<T>().size())>> : std::true_type {};

#endif
