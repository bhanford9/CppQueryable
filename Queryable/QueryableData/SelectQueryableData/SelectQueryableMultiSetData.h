#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEMULTISETDATA_H

#include <iostream>
#include <set>

#include "SelectQueryableData.h"

template<typename TOriginal, typename TCurrent>
class SelectQueryableMultiSetData : public SelectQueryableData<TOriginal, TCurrent, std::multiset>
{
public:
  SelectQueryableMultiSetData(
    std::shared_ptr<IQueryableData<TOriginal>> data,
    std::function<TCurrent(TOriginal)> selector,
    std::function<bool(TCurrent, TCurrent)> compare = [](TCurrent a, TCurrent b) { return a < b; })
    : SelectQueryableData<TOriginal, TCurrent, std::multiset>(std::move(data), selector)
  {
    Iterator<TCurrent> dummy;
    this->Update(dummy, dummy, compare);
  }

  virtual ~SelectQueryableMultiSetData() { }

  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.insert(item);
    this->size++;
  }

  virtual void Update(Iterator<TCurrent> first, Iterator<TCurrent> last, std::function<bool(TCurrent, TCurrent)> compare) override
  {
    std::function<bool(TOriginal, TOriginal)> originalCompare =
      [&](TOriginal a, TOriginal b) { return compare(this->ToCurrent(a), this->ToCurrent(b)); };

    this->original.get()->Update(this->original.get()->begin(), this->original.get()->end(), originalCompare);
    this->size = this->original.get()->Count();
  }
};

#endif
