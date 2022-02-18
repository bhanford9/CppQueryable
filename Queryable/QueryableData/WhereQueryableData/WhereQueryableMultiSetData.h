#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TObj>
class WhereQueryableMultiSetData : public WhereQueryableData<TObj, std::multiset>
{
public:
  WhereQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::multiset>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableMultiSetData(const WhereQueryableMultiSetData<TObj> & other)
    : WhereQueryableData<TObj, std::multiset>(other)
  {
  }

  virtual ~WhereQueryableMultiSetData() { }

  void Add(TObj item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.insert(item);
    this->size++;
  }

  // virtual void Update(QueryableIterator<TObj> first, QueryableIterator<TObj> last, std::function<bool(TObj, TObj)> compare) override
  // {
  //   this->original.get()->Update(first, last, compare);
  // }
};

#endif
