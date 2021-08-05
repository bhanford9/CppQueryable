#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H

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
  template<typename, typename ...> typename TIterable = std::vector,
  typename TKeyCompare = std::less<TKey>,
  typename TDataCompare = std::less<TData>>
class Group : public QueryableData<TData, TIterable>
{
private:
  TKey key;
  TKeyCompare keyCompare;
  std::shared_ptr<IQueryableData<TData>> items;

public:
  Group() { }
  Group(
    TKey key,
    QueryableType type,
    TKeyCompare keyCompare = TKeyCompare(),
    TDataCompare dataCompare = TDataCompare())
    : QueryableData<TData, TIterable>()
  {
    this->key = key;
    this->keyCompare = keyCompare;

    switch (type)
    {
      case QueryableType::Deque:
        {
          std::deque<TData> localDeque;
          this->items = std::make_shared<QueryableDequeData<TData>>(localDeque);
        }
        break;
      case QueryableType::List:
        {
          std::list<TData> localList;
          this->items = std::make_shared<QueryableListData<TData>>(localList);
        }
        break;
      case QueryableType::MultiSet:
        {
          std::multiset<TData, TDataCompare> localMultiSet(dataCompare);
          this->items = std::make_shared<QueryableMultiSetData<TData, TDataCompare>>(localMultiSet);
        }
        break;
      case QueryableType::Set:
        {
          std::set<TData, TDataCompare> localSet(dataCompare);
          this->items = std::make_shared<QueryableSetData<TData, TDataCompare>>(localSet);
        }
        break;
      case QueryableType::Vector:
      default:
        {
          std::vector<TData> localVector;
          this->items = std::make_shared<QueryableVectorData<TData>>(localVector);
        }
        break;
    }
  }
  Group(const Group& group)
    : QueryableData<TData, TIterable>(group)
  {
  }

  virtual ~Group() { }

  void Add(TIterable<TData> data)
  {
    for (TData d : data)
    {
      this->Add(d);
    }
  }

  void Add(TData item) override
  {
    this->items.get()->Add(item);

    for (TData data : *this->items.get())
    {
    }
  }

  int Count() override
  {
    return this->items.get()->Count();
  }

  void RemoveLast() override
  {
    this->items.get()->RemoveLast();
  }

  void RemoveFirst() override
  {
    this->items.get()->RemoveLast();
  }

  void Sort(std::function<bool(TData, TData)> compare) override
  {
    this->items.get()->Sort(compare);
  }

  void Clear() override
  {
    this->items.get()->Clear();
  }

  std::vector<TData> ToVector() override
  {
    return this->items.get()->ToVector();
  }

  Iterator<TData> begin() override
  {
    return this->items.get()->begin();
  }

  Iterator<TData> end() override
  {
    return this->items.get()->end();
  }

  Iterator<TData> rbegin() override
  {
    return this->items.get()->rbegin();
  }

  Iterator<TData> rend() override
  {
    return this->items.get()->rend();
  }

  TKey GetKey() const
  {
    return this->key;
  }

  bool operator<(const Group & other) const
  {
    return this->keyCompare(this->key, other.GetKey());
  }
};

#endif
