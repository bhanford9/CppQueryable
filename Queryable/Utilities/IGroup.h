#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_IGROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_IGROUP_H

#include <iostream>
#include <memory>

#include "../QueryableData/IQueryableData.h"
#include "../Iterators/Iterator.h"
#include "../QueryableType.h"

template <typename T>
class Queryable;

template<typename TKey, typename TData>
class IGroup
{
protected:

public:
  virtual IQueryableData<TData> * GetData() = 0;
  IGroup() { }
  IGroup(const IGroup & group) { }
  virtual ~IGroup() { }

  virtual bool HasKey(TKey key) const = 0;
  virtual TKey GetKey() const = 0;
  virtual QueryableType GetType() const = 0;
  virtual bool operator<(const IGroup<TKey, TData> & other) const = 0;

  // virtual Iterator<TData> begin() { return this->GetData().begin(); }
  // virtual Iterator<TData> end() { return this->GetData().end(); }
  // virtual Iterator<TData> rbegin() { return this->GetData().rbegin(); }
  // virtual Iterator<TData> rend() { return this->GetData().rend(); }
  // virtual int Count() { return this->GetData().Count(); }
  // virtual void Add(TData item) { this->GetData().Add(item); }

  // Important to document that this should not be used within looping code
  // virtual Queryable<TData> ToQueryable()
  // {
  //   return Queryable<TData>(std::make_shared<IQueryableData<TData>>(this->GetData()), this->GetType());
  // }
};

#endif
