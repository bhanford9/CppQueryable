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

#include "IQueryable.hpp"
#include "ISortedQueryable.hpp"
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

//   template<typename T, typename TAllocator = std::allocator<T>>
//   DequeInternalQueryable<T, TAllocator> BuildQueryable(std::deque<T, TAllocator> items)
//   {
//     return DequeInternalQueryable<T, TAllocator>(items);
//   }

//   template<typename T, typename TAllocator = std::allocator<T>>
//   ListInternalQueryable<T, TAllocator> BuildQueryable(std::list<T, TAllocator> items)
//   {
//     return ListInternalQueryable<T, TAllocator>(items);
//   }

//   template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
//   MultiSetInternalQueryable<T, TLessThan, TAllocator> BuildQueryable(std::multiset<T, TLessThan, TAllocator> items)
//   {
//     return MultiSetInternalQueryable<T, TLessThan, TAllocator>(items);
//   }

//   template<typename T, typename TLessThan = std::less<T>, typename TAllocator = std::allocator<T>>
//   SetInternalQueryable<T, TLessThan, TAllocator> BuildQueryable(std::set<T, TLessThan, TAllocator> items)
//   {
//     return SetInternalQueryable<T, TLessThan, TAllocator>(items);
//   }

//   template<typename T, typename TAllocator = std::allocator<T>>
//   VectorInternalQueryable<T, TAllocator> BuildQueryable(std::vector<T, TAllocator> items)
//   {
//     return VectorInternalQueryable<T, TAllocator>(items);
//   }

  // This will work out better if the public facing types are the aliases and the actual
  // child classes are only used internally to the library
  template<typename T, typename ...TArgs>
  IQueryable<T, TArgs...> BuildQueryable2(std::deque<T, TArgs...> items)
  {
    IQueryable<T, TArgs...> queryable(
      std::make_shared<QueryableDeque<T, TArgs...>>(
        QueryableDeque<T, TArgs...>::FromDeque(items)));
    return queryable;
  }
  template<typename T>
  IQueryable<T> BuildQueryable2(std::deque<T> items)
  {
    IQueryable<T> queryable(
      std::make_shared<QueryableDeque<T>>(
        QueryableDeque<T>::FromDeque(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  IQueryable<T, TArgs...> BuildQueryable2(std::list<T, TArgs...> items)
  {
    IQueryable<T, TArgs...> queryable(
      std::make_shared<QueryableList<T, TArgs...>>(
        QueryableList<T, TArgs...>::FromList(items)));
    return queryable;
  }
  template<typename T>
  IQueryable<T> BuildQueryable2(std::list<T> items)
  {
    IQueryable<T> queryable(
      std::make_shared<QueryableList<T>>(
        QueryableList<T>::FromList(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  ISortedQueryable<T, TArgs...> BuildQueryable2(std::multiset<T, TArgs...> items)
  {
    ISortedQueryable<T, TArgs...> queryable(
      std::make_shared<QueryableMultiSet<T, TArgs...>>(
        QueryableMultiSet<T, TArgs...>::FromMultiSet(items)));
    return queryable;
  }
  template<typename T>
  ISortedQueryable<T> BuildQueryable2(std::multiset<T> items)
  {
    ISortedQueryable<T> queryable(
      std::make_shared<QueryableMultiSet<T>>(
        QueryableMultiSet<T>::FromMultiSet(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  ISortedQueryable<T, TArgs...> BuildQueryable2(std::set<T, TArgs...> items)
  {
    ISortedQueryable<T, TArgs...> queryable(
      std::make_shared<QueryableSet<T, TArgs...>>(
        QueryableSet<T, TArgs...>::FromSet(items)));
    return queryable;
  }
  template<typename T>
  ISortedQueryable<T> BuildQueryable2(std::set<T> items)
  {
    ISortedQueryable<T> queryable(
      std::make_shared<QueryableSet<T>>(
        QueryableSet<T>::FromSet(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  IQueryable<T, TArgs...> BuildQueryable2(std::vector<T, TArgs...> items)
  {
    IQueryable<T, TArgs...> queryable(
      std::make_shared<QueryableVector<T, TArgs...>>(
        QueryableVector<T, TArgs...>::FromVector(items)));
    return queryable;
  }
  template<typename T>
  IQueryable<T> BuildQueryable2(std::vector<T> items)
  {
    IQueryable<T> queryable(
      std::make_shared<QueryableVector<T>>(
        QueryableVector<T>::FromVector(items)));
    return queryable;
  }
};


#endif
