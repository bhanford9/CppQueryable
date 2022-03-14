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
  template<typename T, typename TAllocator = std::allocator<T>>
  static VectorInternalQueryable<T, TAllocator> BuildQueryable(std::vector<T, TAllocator> items)
  {
    return VectorInternalQueryable<T, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static SetInternalQueryable<T, TLessThan, TAllocator> BuildQueryable(std::set<T, TLessThan, TAllocator> items)
  {
    return SetInternalQueryable<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static MultiSetInternalQueryable<T, TLessThan, TAllocator> BuildQueryable(std::multiset<T, TLessThan, TAllocator> items)
  {
    return MultiSetInternalQueryable<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static ListInternalQueryable<T, TAllocator> BuildQueryable(std::list<T, TAllocator> items)
  {
    return ListInternalQueryable<T, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static DequeInternalQueryable<T, TAllocator> BuildQueryable(std::deque<T, TAllocator> items)
  {
    return DequeInternalQueryable<T, TAllocator>(items);
  }
};


#endif
