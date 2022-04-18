#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLERS_MULTISETQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLERS_MULTISETQUERYABLE_H

#include <iostream>
#include <set>

#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableMultiSetData.hpp"

template<
  typename TObj,
  typename TLessThan = std::less<TObj>,
  typename TAllocator = std::allocator<TObj>>
class MultiSetQueryable : public Queryable<TObj, std::multiset, TLessThan, TAllocator>
{
public:
  MultiSetQueryable()
  {
    this->queryable = std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>();
  }
  virtual ~MultiSetQueryable() { }

  MultiSetQueryable(const MultiSetInternalQueryable<TObj, TLessThan, TAllocator> && other)
    : Queryable<TObj, std::multiset, TLessThan, TAllocator>(std::move(other))
  {
  }

  MultiSetQueryable(const std::multiset<TObj, TLessThan, TAllocator> & iterable)
  {
    this->queryable = std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>(iterable);
  }

  MultiSetQueryable(const std::multiset<TObj, TLessThan, TAllocator> && iterable)
  {
    this->queryable = std::make_shared<MultiSetInternalQueryable<TObj, TLessThan, TAllocator>>(std::move(iterable));
  }
};

#endif
