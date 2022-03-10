#ifndef CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H
#define CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H

#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

// things left to investigate adding support for
// array
// map
// multimap
// forward_list
// stack
// queue
// priority_queue

#include "Queryable.hpp"
#include "Queryables/DequeQueryable.hpp"
#include "Queryables/ListQueryable.hpp"
#include "Queryables/MultiSetQueryable.hpp"
#include "Queryables/SetQueryable.hpp"
#include "Queryables/VectorQueryable.hpp"

namespace QueryBuilder
{
  template<typename T, typename TAllocator = std::allocator<T>, typename TOut = T>
  static VectorQueryable<T, TAllocator, TOut> BuildQueryable(std::vector<T, TAllocator> items)
  {
    return VectorQueryable<T, TAllocator, TOut>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static SetQueryable<T, TLessThan, TAllocator> BuildQueryable(std::set<T, TLessThan, TAllocator> items)
  {
    return SetQueryable<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static MultiSetQueryable<T, TLessThan, TAllocator> BuildQueryable(std::multiset<T, TLessThan, TAllocator> items)
  {
    return MultiSetQueryable<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static ListQueryable<T, TAllocator> BuildQueryable(std::list<T, TAllocator> items)
  {
    return ListQueryable<T, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static DequeQueryable<T, TAllocator> BuildQueryable(std::deque<T, TAllocator> items)
  {
    return DequeQueryable<T, TAllocator>(items);
  }
};

#endif
