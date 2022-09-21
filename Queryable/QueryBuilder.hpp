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
  // This will work out better if the public facing types are the aliases and the actual
  // child classes are only used internally to the library
  template<typename T, typename ...TArgs>
  IQueryable<T, std::deque, TArgs...> BuildQueryable2(std::deque<T, TArgs...> items)
  {
    IQueryable<T, std::deque, TArgs...> queryable(
      std::make_shared<QueryableDeque<T, TArgs...>>(
        QueryableDeque<T, TArgs...>::FromDeque(items)));
    return queryable;
  }
  template<typename T>
  IQueryable<T, std::deque> BuildQueryable2(std::deque<T> items)
  {
    IQueryable<T, std::deque> queryable(
      std::make_shared<QueryableDeque<T>>(
        QueryableDeque<T>::FromDeque(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  IQueryable<T, std::list, TArgs...> BuildQueryable2(std::list<T, TArgs...> items)
  {
    IQueryable<T, std::list, TArgs...> queryable(
      std::make_shared<QueryableList<T, TArgs...>>(
        QueryableList<T, TArgs...>::FromList(items)));
    return queryable;
  }
  template<typename T>
  IQueryable<T, std::list> BuildQueryable2(std::list<T> items)
  {
    IQueryable<T, std::list> queryable(
      std::make_shared<QueryableList<T>>(
        QueryableList<T>::FromList(items)));
    return queryable;
  }

  template<typename TKey, typename TValue, typename ...TArgs>
  inline IQueryable<TKey, std::map, TValue, TArgs...> BuildQueryable2(std::map<TKey, TValue, TArgs...> items)
  {
    IQueryable<TKey, std::map, TValue, TArgs...> queryable(
      std::make_shared<QueryableMap<TKey, TValue, TArgs...>>(
        QueryableMap<TKey, TValue, TArgs...>::FromMap2(items)));
    return queryable;
  }
  // template<typename TKey, typename TValue>
  // inline IQueryable<TKey, std::map, TValue> BuildQueryable2(std::map<TKey, TValue> items)
  // {
  //   IQueryable<TKey, std::map, TValue> queryable(
  //     std::make_shared<QueryableMap<TKey, TValue>>(
  //       QueryableMap<TKey, TValue>::FromMap2(items)));
  //   return queryable;
  // }

  template<typename T, typename ...TArgs>
  ISortedQueryable<T, std::multiset, TArgs...> BuildQueryable2(std::multiset<T, TArgs...> items)
  {
    ISortedQueryable<T, std::multiset, TArgs...> queryable(
      std::make_shared<QueryableMultiSet<T, TArgs...>>(
        QueryableMultiSet<T, TArgs...>::FromMultiSet2(items)));
    return queryable;
  }
  template<typename T>
  ISortedQueryable<T, std::multiset> BuildQueryable2(std::multiset<T> items)
  {
    ISortedQueryable<T, std::multiset> queryable(
      std::make_shared<QueryableMultiSet<T>>(
        QueryableMultiSet<T>::FromMultiSet(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  ISortedQueryable<T, std::set, TArgs...> BuildQueryable2(std::set<T, TArgs...> items)
  {
    ISortedQueryable<T, std::set, TArgs...> queryable(
      std::make_shared<QueryableSet<T, TArgs...>>(
        QueryableSet<T, TArgs...>::FromSet2(items)));
    return queryable;
  }
  template<typename T>
  ISortedQueryable<T, std::set> BuildQueryable2(std::set<T> items)
  {
    ISortedQueryable<T, std::set> queryable(
      std::make_shared<QueryableSet<T>>(
        QueryableSet<T>::FromSet(items)));
    return queryable;
  }

  template<typename T, typename ...TArgs>
  IQueryable<T, std::vector, TArgs...> BuildQueryable2(std::vector<T, TArgs...> items)
  {
    IQueryable<T, std::vector, TArgs...> queryable(
      std::make_shared<QueryableVector<T, TArgs...>>(
        QueryableVector<T, TArgs...>::FromVector(items)));
    return queryable;
  }
  template<typename T>
  IQueryable<T, std::vector> BuildQueryable2(std::vector<T> items)
  {
    IQueryable<T, std::vector> queryable(
      std::make_shared<QueryableVector<T>>(
        QueryableVector<T>::FromVector(items)));
    return queryable;
  }
};


#endif
