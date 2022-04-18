#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLERS_SETQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLERS_SETQUERYABLE_H

#include <iostream>
#include <set>

#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableSetData.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class SetQueryable : public Queryable<TObj, std::set, TLessThan, TAllocator>
{
public:
  SetQueryable()
  {
    this->queryable = std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>();
  }
  virtual ~SetQueryable() { }

  SetQueryable(const SetInternalQueryable<TObj, TLessThan, TAllocator> && other)
    : Queryable<TObj, std::set, TLessThan, TAllocator>(std::move(other))
  {
  }

  SetQueryable(const std::set<TObj, TLessThan, TAllocator> & iterable)
  {
    this->queryable = std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>(iterable);
  }

  SetQueryable(const std::set<TObj, TLessThan, TAllocator> && iterable)
  {
    this->queryable = std::make_shared<SetInternalQueryable<TObj, TLessThan, TAllocator>>(std::move(iterable));
  }
};

#endif
