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
#include "IGroup.h"

template<
  typename TKey,
  typename TData,
  template<typename, typename ...> typename TIterable = std::vector,
  typename TKeyCompare = std::less<TKey>,
  typename TDataCompare = std::less<TData>>
class Group : public QueryableData<TData, TIterable>, public IGroup<TKey, TData, TKeyCompare, TDataCompare>
{
  // This creates diamond inheritance.
  // The tasking is delibrately divided between the parent classes:
  //   - QueryableData handles the initialization of the iterator operations
  //   - IGroup handles the runtime execution of inherited memebers
  //
  // Might want to figure out if there is a better way to architect the code to avoid this

private:
  typedef QueryableData<TData, TIterable> TQueryableData;
  typedef IGroup<TKey, TData, TKeyCompare, TDataCompare> TGroup;

public:
  Group() : TQueryableData(), TGroup() { }
  Group(
    QueryableType type,
    TKeyCompare keyCompare = TKeyCompare(),
    TDataCompare dataCompare = TDataCompare())
    : TQueryableData(), TGroup()
  {
    this->keyCompare = keyCompare;

    switch (type)
    {
      case QueryableType::Deque:
        {
          std::deque<TData> localDeque;
          this->data = std::make_shared<QueryableDequeData<TData>>(localDeque);
        }
        break;
      case QueryableType::List:
        {
          std::list<TData> localList;
          this->data = std::make_shared<QueryableListData<TData>>(localList);
        }
        break;
      case QueryableType::MultiSet:
        {
          std::multiset<TData> localMultiSet(dataCompare);
          this->data = std::make_shared<QueryableMultiSetData<TData>>(localMultiSet);
        }
        break;
      case QueryableType::Set:
        {
          std::set<TData> localSet(dataCompare);
          this->data = std::make_shared<QueryableSetData<TData>>(localSet);
        }
        break;
      case QueryableType::Vector:
      default:
        {
          std::vector<TData> localVector;
          this->data = std::make_shared<QueryableVectorData<TData>>(localVector);
        }
        break;
    }
  }

  Group(
    TKey key,
    QueryableType type,
    TKeyCompare keyCompare = TKeyCompare(),
    TDataCompare dataCompare = TDataCompare())
    : Group(type, keyCompare, dataCompare)
  {
    this->key = key;
  }
  Group(const Group& group)
    : TQueryableData(group), TGroup()
  {
  }

  virtual ~Group() { }

  void AddMany(TIterable<TData> data)
  {
    for (TData d : data)
    {
      this->Add(d);
    }
  }

  Iterator<TData> begin() { return TGroup::begin(); }
  Iterator<TData> end() { return TGroup::end(); }
  Iterator<TData> rbegin() { return TGroup::rbegin(); }
  Iterator<TData> rend() { return TGroup::rend(); }
  void Clear() { TGroup::Clear(); }
  void Add(TData obj) { TGroup::Add(obj); }
  int Count() { return TGroup::Count(); }
  void RemoveLast() { TGroup::RemoveLast(); }
  void RemoveFirst() { TGroup::RemoveFirst(); }
  std::vector<TData> ToVector() { return TGroup::ToVector(); }
  void Sort(std::function<bool(TData, TData)> compare) { return TGroup::Sort(compare); }
  void AddCondition(std::function<bool(const TData &)> condition) { TGroup::AddCondition(condition); }
  bool PassesCondition(const TData & obj) const { return TGroup::PassesCondition(obj); }
};

#endif
