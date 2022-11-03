#ifndef CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H
#define CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H

#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

// things left to investigate adding support for
// array
// multimap
// forward_list
// stack
// queue
// priority_queue

#include "Queryable.hpp"
#include "QueryableAliases.hpp"

#include "Utilities/StaticBuilders/QueryableStaticBuilder.hpp"

namespace QueryBuilder
{
  template<typename T, typename TAllocator = std::allocator<T>>
  Queryable<T, std::deque, T, TAllocator> BuildQueryable(const std::deque<T, TAllocator> & items)
  {
    return Builders::FromDeque<T, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  Queryable<T, std::list, T, TAllocator> BuildQueryable(const std::list<T, TAllocator> & items)
  {
    return Builders::FromList<T, TAllocator>(items);
  }

  template<
    typename TKey,
    typename TValue,
    typename TKeyLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  Queryable<TKey, std::map, std::pair<const TKey, TValue>, TValue, TKeyLessThan, TAllocator> BuildQueryable(
    const std::map<TKey, TValue, TKeyLessThan, TAllocator> & items)
  {
    return Builders::FromMap<TKey, TValue, TKeyLessThan, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  Queryable<T, std::multiset, T, TLessThan, TAllocator> BuildQueryable(const std::multiset<T, TLessThan, TAllocator> & items)
  {
    return Builders::FromMultiSet<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
  Queryable<T, std::set, T, TLessThan, TAllocator> BuildQueryable(const std::set<T, TLessThan, TAllocator> & items)
  {
    return Builders::FromSet<T, TLessThan, TAllocator>(items);
  }

  template<typename T, typename TAllocator = std::allocator<T>>
  Queryable<T, std::vector, T, TAllocator> BuildQueryable(const std::vector<T, TAllocator> & items)
  {
    return Builders::FromVector<T, TAllocator>(items);
  }
};


#endif
