#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H

#include <iostream>
#include <memory>

#include "../QueryableData/IQueryableData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableDequeData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableListData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableMultiSetData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableSetData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableVectorData.h"
#include "../Iterators/Iterator.h"
#include "../QueryableType.h"
#include "IGroup.h"

template <typename T>
class Queryable;

template<typename TKey, typename TData>
class Group : public IGroup<TKey, TData>
{
private:
  TKey key;
  QueryableType type = QueryableType::Default;
  std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; };
  std::shared_ptr<IQueryableData<TData>> internalGroup;

protected:
public:
  virtual IQueryableData<TData> * GetData() override
  {
    return this->internalGroup.get();
  }

  Group() { }
  Group(const Group<TKey, TData> & other)
  {
    std::cout << "copy group" << std::endl;
    this->key = other.key;
    this->type = other.type;
    this->keyCompare = other.keyCompare;
    this->internalGroup = other.internalGroup;
  }

  Group(
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
  {
    this->key = key;
    this->type = type;
    this->keyCompare = keyCompare;
  }

  /// TODO --> change the internal group to be IQueryableData<TData>
  /// TODO --> change the constructor to require everything that GroupQueryableData requires
  ////       you have all these things within the GroupBy method any way

  Group(
    const GroupQueryableDequeData<TKey, TData> & group,
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : Group<TKey, TData>(key, type, keyCompare)
  {
    std::cout << "set internal group to group queryable deque data " << std::endl;
    this->internalGroup = std::move(std::make_shared<GroupQueryableDequeData<TKey, TData>>(group));
  }

  Group(const GroupQueryableListData<TKey, TData> & group,
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : Group<TKey, TData>(key, type, keyCompare)
  {
    this->internalGroup = std::make_shared<GroupQueryableListData<TKey, TData>>(group);
  }

  Group(const GroupQueryableMultiSetData<TKey, TData> & group,
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : Group<TKey, TData>(key, type, keyCompare)
  {
    this->internalGroup = std::make_shared<GroupQueryableMultiSetData<TKey, TData>>(group);
  }

  Group(const GroupQueryableSetData<TKey, TData> & group,
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : Group<TKey, TData>(key, type, keyCompare)
  {
    this->internalGroup = std::make_shared<GroupQueryableSetData<TKey, TData>>(group);
  }

  Group(const GroupQueryableVectorData<TKey, TData> & group,
    TKey key,
    QueryableType type,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; })
    : Group<TKey, TData>(key, type, keyCompare)
  {
    this->internalGroup = std::make_shared<GroupQueryableVectorData<TKey, TData>>(group);
  }

  virtual ~Group() { }

  virtual bool HasKey(TKey key) const override
  {
    return !(this->keyCompare(this->key, key) || this->keyCompare(key, this->key));
  }

  virtual TKey GetKey() const override
  {
    return this->key;
  }

  virtual QueryableType GetType() const override
  {
    return this->type;
  }

  virtual bool operator<(const IGroup<TKey, TData> & other) const override
  {
    return this->keyCompare(this->key, other.GetKey());
  }

  virtual Iterator<TData> begin()
  {
    std::cout << "group begin" << std::endl;

    std::cout << "data count: " << this->GetData()->Count() << std::endl;

    for (TData data : *this->GetData())
    {
      std::cout << "data: " << data << std::endl;
    }
    return this->GetData()->begin();
  }

  virtual Iterator<TData> end()
  {
    return this->GetData()->end();
  }

  virtual Iterator<TData> rbegin()
  {
    return this->GetData()->rbegin();
  }

  virtual Iterator<TData> rend()
  {
    return this->GetData()->rend();
  }

  virtual int Count()
  {
    return this->GetData()->Count();
  }

  virtual void Add(TData item)
  {
    std::cout << "group add item: " << item << std::endl;
    this->GetData()->Add(item);
  }

  // virtual Queryable<TData> ToQueryable()
  // {
  //   return this->internalGroup.get()->ToQueryable();
  // }
};

#endif
