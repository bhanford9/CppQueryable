#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_IGROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_IGROUP_H

#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "../QueryableData/IQueryableData.h"
#include "../QueryableData/QueryableDequeData.h"
#include "../QueryableData/QueryableListData.h"
#include "../QueryableData/QueryableMultiSetData.h"
#include "../QueryableData/QueryableSetData.h"
#include "../QueryableData/QueryableVectorData.h"
#include "../QueryableType.h"

template<
  typename TKey,
  typename TData,
  typename TKeyCompare = std::less<TKey>,
  typename TDataCompare = std::less<TData>>
class IGroup : virtual public IQueryableData<TData>
{
protected:
  TKey key;
  TKeyCompare keyCompare;
  std::shared_ptr<IQueryableData<TData>> data;

public:
  IGroup() { }
  virtual ~IGroup() { }

  void Add(TData item) override
  {
    this->data.get()->Add(item);
  }

  int Count() override
  {
    return this->data.get()->Count();
  }

  void RemoveLast() override
  {
    this->data.get()->RemoveLast();
  }

  void RemoveFirst() override
  {
    this->data.get()->RemoveLast();
  }

  void Sort(std::function<bool(TData, TData)> compare) override
  {
    this->data.get()->Sort(compare);
  }

  void Clear() override
  {
    this->data.get()->Clear();
  }

  std::vector<TData> ToVector() override
  {
    return this->data.get()->ToVector();
  }

  Iterator<TData> begin() override
  {
    return this->data.get()->begin();
  }

  Iterator<TData> end() override
  {
    return this->data.get()->end();
  }

  Iterator<TData> rbegin() override
  {
    return this->data.get()->rbegin();
  }

  Iterator<TData> rend() override
  {
    return this->data.get()->rend();
  }

  void AddCondition(std::function<bool(TData)> condition) override
  {
    this->data.get()->AddCondition(condition);
  }

  bool PassesCondition(TData obj) override
  {
    return this->data.get()->PassesCondition(obj);
  }

  TKey GetKey() const
  {
    return this->key;
  }

  bool operator<(const IGroup & other) const
  {
    return this->keyCompare(this->key, other.GetKey());
  }
};

#endif
