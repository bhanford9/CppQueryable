#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "../../Utilities/Condition.h"
#include "WhereQueryableData.h"

template<typename TOriginal>
class WhereQueryableMultiSetData : public WhereQueryableData<TOriginal, std::multiset>
{
public:
  WhereQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<bool(TOriginal)> condition)
    : WhereQueryableData<TOriginal, std::multiset>(std::move(data), condition)
  {
  }

  virtual ~WhereQueryableMultiSetData() { }

  void Add(TOriginal item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.insert(item);
    this->size++;
  }

  void Sort(std::function<bool(TOriginal, TOriginal)> compare = [](TOriginal a, TOriginal b) { return a < b; }) override
  {
    // already sorted
  }

  virtual void Update(Iterator<TOriginal> first, Iterator<TOriginal> last, std::function<bool(TOriginal, TOriginal)> compare) override
  {
    this->original.get()->Update(first, last, compare);
  }

};

#endif
