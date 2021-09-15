#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableListData : public WhereQueryableData<TOriginal, std::list>
{
public:
  WhereQueryableListData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::list>(std::move(data), condition)
  {
  }

  virtual ~WhereQueryableListData() { }

  void Add(TOriginal item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
