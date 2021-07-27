#ifndef CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H
#define CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H

#include <deque>
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

#include "Queryable.h"
#include "QueryableDeque.h"
#include "QueryableList.h"
#include "QueryableMultiSet.h"
#include "QueryableSet.h"
#include "QueryableVector.h"

namespace QueryBuilder
{
  template<typename T>
  static QueryableVector<T> BuildQueryable(std::vector<T> items)
  {
    return QueryableVector<T>(items);
  }

  template<typename T, typename TCompare = std::less<T>>
  static QueryableSet<T> BuildQueryable(std::set<T> items)
  {
    return QueryableSet<T>(items);
  }

  template<typename T, typename TCompare = std::less<T>>
  static QueryableMultiSet<T> BuildQueryable(std::multiset<T> items)
  {
    return QueryableMultiSet<T>(items);
  }

  template<typename T>
  static QueryableList<T> BuildQueryable(std::list<T> items)
  {
    return QueryableList<T>(items);
  }

  template<typename T>
  static QueryableDeque<T> BuildQueryable(std::deque<T> items)
  {
    return QueryableDeque<T>(items);
  }
};

#endif
