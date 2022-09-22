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

#include "Utilities/StaticBuilders/QueryableStaticBuilder.hpp"

namespace QueryBuilder
{
  // This will work out better if the public facing types are the aliases and the actual
  // child classes are only used internally to the library
  template<typename T, typename ...TArgs>
  IQueryable<T, std::deque, TArgs...> BuildQueryable2(const std::deque<T, TArgs...> & items)
  {
    return IQueryable<T, std::deque, TArgs...>(
      std::make_shared<QueryableDeque<T, TArgs...>>(
        Builders::FromDeque(items)));
  }
  template<typename T>
  IQueryable<T, std::deque> BuildQueryable2(const std::deque<T> & items)
  {
    return IQueryable<T, std::deque>(
      std::make_shared<QueryableDeque<T>>(
        Builders::FromDeque(items)));
  }

  template<typename T, typename ...TArgs>
  IQueryable<T, std::list, TArgs...> BuildQueryable2(const std::list<T, TArgs...> & items)
  {
    return IQueryable<T, std::list, TArgs...>(
      std::make_shared<QueryableList<T, TArgs...>>(
        Builders::FromList(items)));
  }
  template<typename T>
  IQueryable<T, std::list> BuildQueryable2(const std::list<T> & items)
  {
    return IQueryable<T, std::list>(
      std::make_shared<QueryableList<T>>(
        Builders::FromList(items)));
  }

  template<typename TKey, typename TValue, typename ...TArgs>
  inline IQueryable<std::pair<const TKey, TValue>, std::map, TArgs...> BuildQueryable2(const std::map<const TKey, TValue, TArgs...> & items)
  {
    return IQueryable<std::pair<const TKey, TValue>, std::map, TArgs...>(
      std::make_shared<QueryableMap<const TKey, TValue, TArgs...>>(
        Builders::FromMap(items)));
  }
  template<typename TKey, typename TValue>
  inline IQueryable<std::pair<const TKey, TValue>, std::map> BuildQueryable2(const std::map<const TKey, TValue> & items)
  {
    return IQueryable<std::pair<const TKey, TValue>, std::map>(
      std::make_shared<QueryableMap<const TKey, TValue>>(
        Builders::FromMap(items)));
  }

  template<typename T, typename ...TArgs>
  ISortedQueryable<T, std::multiset, TArgs...> BuildQueryable2(const std::multiset<T, TArgs...> & items)
  {
    return ISortedQueryable<T, std::multiset, TArgs...>(
      std::make_shared<QueryableMultiSet<T, TArgs...>>(
        Builders::FromMultiSet<T, TArgs...>(items)));
  }
  template<typename T>
  ISortedQueryable<T, std::multiset> BuildQueryable2(const std::multiset<T> & items)
  {
    return ISortedQueryable<T, std::multiset>(
      std::make_shared<QueryableMultiSet<T>>(
        Builders::FromMultiSet(items)));  }

  template<typename T, typename ...TArgs>
  ISortedQueryable<T, std::set, TArgs...> BuildQueryable2(const std::set<T, TArgs...> & items)
  {
    return ISortedQueryable<T, std::set, TArgs...>(
      std::make_shared<QueryableSet<T, TArgs...>>(
        Builders::FromSet<T, TArgs...>(items)));
  }
  template<typename T>
  ISortedQueryable<T, std::set> BuildQueryable2(const std::set<T> & items)
  {
    return ISortedQueryable<T, std::set>(
      std::make_shared<QueryableSet<T>>(
        Builders::FromSet(items)));
  }

  template<typename T, typename ...TArgs>
  IQueryable<T, std::vector, TArgs...> BuildQueryable2(const std::vector<T, TArgs...> & items)
  {
    return IQueryable<T, std::vector, TArgs...>(
      std::make_shared<QueryableVector<T, TArgs...>>(
        Builders::FromVector(items)));
  }
  template<typename T>
  IQueryable<T, std::vector> BuildQueryable2(const std::vector<T> & items)
  {
    return IQueryable<T, std::vector>(
      std::make_shared<QueryableVector<T>>(
        Builders::FromVector(items)));
  }
};


#endif
