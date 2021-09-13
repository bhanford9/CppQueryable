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
// map
// multimap
// forward_list
// stack
// queue
// priority_queue

#include "Queryable.h"

namespace QueryBuilder
{
  template<typename T>
  static Queryable<T> BuildQueryable(std::vector<T> items)
  {
    return Queryable<T>(items);
  }

  template<typename T>
  static Queryable<T> BuildQueryable(std::set<T, std::function<bool(T, T)>> items)
  {
    return Queryable<T>(items);
  }

  template<typename T>
  static Queryable<T> BuildQueryable(std::multiset<T, std::function<bool(T, T)>> items)
  {
    return Queryable<T>(items);
  }

  template<typename T>
  static Queryable<T> BuildQueryable(std::list<T> items)
  {
    return Queryable<T>(items);
  }

  template<typename T>
  static Queryable<T> BuildQueryable(std::deque<T> items)
  {
    return Queryable<T>(items);
  }
};

#endif
