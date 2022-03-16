#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_IGROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_IGROUP_H

#include <iostream>
#include <memory>

#include "../QueryableData/IQueryableData.hpp"
#include "../Iterators/Iterator.hpp"
#include "../QueryableType.hpp"

template<typename TKey, typename TData>
class IGroup
{
protected:

public:
  virtual IQueryableData<TData> & GetData() = 0;
  IGroup() { }
  IGroup(const IGroup & group) { }
  virtual ~IGroup() { }

  virtual bool HasKey(TKey key) const = 0;
  virtual TKey GetKey() const = 0;
  virtual QueryableType GetType() const = 0;
  virtual bool operator<(const IGroup<TKey, TData> & other) const = 0;
};

#endif
