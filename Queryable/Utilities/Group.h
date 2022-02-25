#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H

#include <iostream>
#include <memory>
#include <vector>

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

// template<typename TObj, typename ...TArgs>
// class Queryable;

template<typename TKey, typename TData>
class Group : public IGroup<TKey, TData>
{
private:
  std::shared_ptr<IGroup<TKey, TData>> internalGroup;

protected:
  virtual IQueryableData<TData, TData> & GetData() override
  {
    return this->internalGroup.get()->GetData();
  }

public:
  Group() { }

  Group(const Group<TKey, TData> & other)
  {
    this->internalGroup = other.internalGroup;
  }

  Group(const GroupQueryableDequeData<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<GroupQueryableDequeData<TKey, TData>>(group);
  }

  Group(const GroupQueryableListData<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<GroupQueryableListData<TKey, TData>>(group);
  }

  Group(const GroupQueryableMultiSetData<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<GroupQueryableMultiSetData<TKey, TData>>(group);
  }

  Group(const GroupQueryableSetData<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<GroupQueryableSetData<TKey, TData>>(group);
  }

  Group(const GroupQueryableVectorData<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<GroupQueryableVectorData<TKey, TData>>(group);
  }

  virtual ~Group() { }

  virtual bool HasKey(TKey key) const override
  {
    return this->internalGroup.get()->HasKey(key);
  }

  virtual TKey GetKey() const override
  {
    return this->internalGroup.get()->GetKey();
  }

  virtual QueryableType GetType() const override
  {
    return this->internalGroup.get()->GetType();
  }

  virtual bool operator<(const IGroup<TKey, TData> & other) const override
  {
    return *this->internalGroup.get() < other;
  }

  virtual Iterator<TData> begin()
  {
    return this->GetData().begin();
  }

  virtual Iterator<TData> end()
  {
    return this->GetData().end();
  }

  virtual Iterator<TData> rbegin()
  {
    return this->GetData().rbegin();
  }

  virtual Iterator<TData> rend()
  {
    return this->GetData().rend();
  }

  virtual int Count()
  {
    return this->GetData().Count();
  }

  virtual void Add(TData item)
  {
    this->GetData().Add(item);
  }

  virtual std::vector<TData> ToVector()
  {
    return this->GetData().ToVector();
  }

  // virtual Queryable<TData> ToQueryable()
  // {
  //   return this->internalGroup.get()->ToQueryable();
  // }
};

#endif
