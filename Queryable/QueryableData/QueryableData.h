#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <set>
#include <vector>

#include "../TypeConstraintUtil.h"
#include "IQueryableData.h"

template<typename TObj, template<typename...> typename TIterable>
class QueryableData : public IQueryableData<TObj>
{
  static_assert(can_iterate<TIterable<TObj>>::value, "Class must be able to be iterated over");
  static_assert(has_size_method<TIterable<TObj>>::value, "Class must have a size method");

protected:
  TIterable<TObj> items;

public:
  QueryableData() { }
  QueryableData(TIterable<TObj> items)
  {
    this->Initialize(items);
  }

  void Initialize(TIterable<TObj> items)
  {
    this->items = items;
  }

  TIterable<TObj> GetItems()
  {
    return this->items;
  }

  void Clear() override
  {
    this->items.clear();
  }

  std::vector<TObj> ToVector() override
  {
    std::vector<TObj> objs;

    for (TObj item : this->items)
    {
      objs.push_back(item);
    }

    return objs;
  }
};

#endif
