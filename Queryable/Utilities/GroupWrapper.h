#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUPWRAPPER_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUPWRAPPER_H

#include <iostream>
#include <memory>

#include "../QueryableData/IQueryableData.h"
#include "../QueryableData/GroupQueryableData/GroupQueryableDequeData.h"
#include "../Iterators/Iterator.h"
#include "../QueryableType.h"
#include "Group.h"

template <typename T>
class Queryable;

template<typename TKey, typename TData>
class GroupWrapper : Group<TKey, TData>
{
private:
  std::shared_ptr<Group<TKey, TData>> internalGroup;

protected:
  virtual IQueryableData<TData> & GetData() const = 0;

public:
  GroupWrapper(Group<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<Group<TKey, TData>>(group);
  }

  GroupWrapper(GroupQueryableDequeData<TKey, TData> & group)
  {
    this->internalGroup = std::make_shared<GroupQueryableDequeData<TKey, TData>>(group);
  }

  /*
    Left todo:
     1. create each individual group container constructor
     2. have each of these inherited methods point to the internalGroup's corresponding method
  */

  virtual ~GroupWrapper() { }

  virtual bool HasKey(TKey key) const = 0;
  virtual TKey GetKey() const = 0;
  virtual QueryableType GetType() const = 0;
  virtual bool operator<(const Group<TKey, TData> & other) const = 0;

  Iterator<TData> begin() { return this->GetData().begin(); }
  Iterator<TData> end() { return this->GetData().end(); }
  Iterator<TData> rbegin() { return this->GetData().rbegin(); }
  Iterator<TData> rend() { return this->GetData().rend(); }
  int Count() const { return this->GetData().Count(); }

  // Important to document that this should not be used within looping code
  Queryable<TData> ToQueryable()
  {
    return Queryable<TData>(std::make_shared<IQueryableData<TData>>(this->GetData()), this->GetType());
  }
};

#endif
