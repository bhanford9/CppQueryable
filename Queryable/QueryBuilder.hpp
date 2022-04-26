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

#include "InternalQueryable.hpp"
#include "InternalQueryables/DequeInternalQueryable.hpp"
#include "InternalQueryables/ListInternalQueryable.hpp"
#include "InternalQueryables/MultiSetInternalQueryable.hpp"
#include "InternalQueryables/SetInternalQueryable.hpp"
#include "InternalQueryables/VectorInternalQueryable.hpp"
#include "Queryable.hpp"
#include "QueryableAliases.hpp"
#include "Queryables/DequeQueryable.hpp"
#include "Queryables/ListQueryable.hpp"
#include "Queryables/MultiSetQueryable.hpp"
#include "Queryables/SetQueryable.hpp"
#include "Queryables/VectorQueryable.hpp"

namespace QueryBuilder
{

  template<typename T, typename TAllocator = std::allocator<T>>
  static DequeInternalQueryable<T, TAllocator> BuildQueryable(std::deque<T, TAllocator> items)
  {
    return DequeInternalQueryable<T, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static ListInternalQueryable<T, TAllocator> BuildQueryable(std::list<T, TAllocator> items)
  {
    return ListInternalQueryable<T, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static MultiSetInternalQueryable<T, TLessThan, TAllocator> BuildQueryable(std::multiset<T, TLessThan, TAllocator> items)
  {
    return MultiSetInternalQueryable<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static SetInternalQueryable<T, TLessThan, TAllocator> BuildQueryable(std::set<T, TLessThan, TAllocator> items)
  {
    return SetInternalQueryable<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static VectorInternalQueryable<T, TAllocator> BuildQueryable(std::vector<T, TAllocator> items)
  {
    return VectorInternalQueryable<T, TAllocator>(items);
  }


  // This will work out better if the public facing types are the aliases and the actual
  // child classes are only used internally to the library
  template<typename T, typename TAllocator = std::allocator<T>>
  static QueryableDeque<T, TAllocator> BuildQueryable2(std::deque<T, TAllocator> items)
  {
    return QueryableDeque<T, TAllocator>::FromDeque(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static QueryableList<T, TAllocator> BuildQueryable2(std::list<T, TAllocator> items)
  {
    return QueryableList<T, TAllocator>::FromList(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static QueryableMultiSet<T, TLessThan, TAllocator> BuildQueryable2(std::multiset<T, TLessThan, TAllocator> items)
  {
    return QueryableMultiSet<T, TLessThan, TAllocator>::FromMultiSet(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  static QueryableSet<T, TLessThan, TAllocator> BuildQueryable2(std::set<T, TLessThan, TAllocator> items)
  {
    return QueryableSet<T, TLessThan, TAllocator>::FromSet(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  static QueryableVector<T, TAllocator> BuildQueryable2(std::vector<T, TAllocator> items)
  {
    return QueryableVector<T, TAllocator>::FromVector(items);
  }
};


#endif
