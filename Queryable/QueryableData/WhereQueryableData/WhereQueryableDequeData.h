#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TObj>
class WhereQueryableDequeData : public WhereQueryableData<TObj, std::deque>
{
private:

public:
  WhereQueryableDequeData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::deque>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableDequeData(const WhereQueryableDequeData<TObj> & other)
    : WhereQueryableData<TObj, std::deque>(other)
  {
  }

  virtual ~WhereQueryableDequeData() { }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
