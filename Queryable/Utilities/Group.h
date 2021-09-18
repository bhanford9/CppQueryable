#ifndef CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H
#define CPPQUERYABLE_QUERYABLE_UTILITIES_GROUP_H

#include <functional>
#include <iostream>
#include <memory>

#include "../QueryableData/IQueryableData.h"
#include "../Iterators/Iterator.h"
#include "../Queryable.h"
#include "../QueryableType.h"

template<typename TKey, typename TData>
class Group
{
protected:
  virtual IQueryableData<TData> & GetData() const = 0;

public:
  Group() { }
  virtual ~Group() { }

  virtual bool HasKey(TKey key) const = 0;
  virtual TKey GetKey() const = 0;
  virtual QueryableType GetType() const = 0;

  Iterator<TData> begin() { return this->GetData().begin(); }
  Iterator<TData> end() { return this->GetData().end(); }
  Iterator<TData> rbegin() { return this->GetData().rbegin(); }
  Iterator<TData> rend() { return this->GetData().rend(); }

  // Important to document that this should not be used within looping code
  Queryable<TData> ToQueryable()
  {
    return Queryable<TData>(std::make_shared<IQueryableData<TData>>(this->GetData()), this->GetType());
  }
};

#endif
