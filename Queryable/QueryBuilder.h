#ifndef CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H
#define CPPQUERYABLE_QUERYABLE_QUERYBUILDER_H

#include <vector>
#include <set>

#include "Queryable.h"
#include "QueryableVector.h"
#include "QueryableSet.h"

namespace QueryBuilder
{
  template<typename T>
  static QueryableVector<T> BuildQueryable(std::vector<T> items)
  {
    return QueryableVector<T>(items);
  }

  template<typename T>
  static QueryableSet<T> BuildQueryable(std::set<T> items)
  {
    return QueryableSet<T>(items);
  }
};

#endif
