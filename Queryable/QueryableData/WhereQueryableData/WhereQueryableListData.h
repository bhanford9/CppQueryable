#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TObj>
class WhereQueryableListData : public WhereQueryableData<TObj, std::list>
{
public:
  WhereQueryableListData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::list>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableListData(const WhereQueryableListData<TObj> & other)
    : WhereQueryableData<TObj, std::list>(other)
  {
  }

  virtual ~WhereQueryableListData() { }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
