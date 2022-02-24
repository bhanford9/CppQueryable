#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLESETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TObj>
class WhereQueryableSetData : public WhereQueryableData<TObj, std::set>
{
protected:

  inline virtual void Add(std::set<TObj> items, TObj item) const
  {
    items.insert(item);
  }
public:
  WhereQueryableSetData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : WhereQueryableData<TObj, std::set>(std::move(data), std::move(condition))
  {
  }
  WhereQueryableSetData(const WhereQueryableSetData<TObj> & other)
    : WhereQueryableData<TObj, std::set>(other)
  {
  }

  virtual ~WhereQueryableSetData() { }

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
