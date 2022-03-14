#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLERS_VECTORQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLERS_VECTORQUERYABLE_H

#include <iostream>
#include <vector>

#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableVectorData.hpp"

template<
  typename TObj,
  typename TAllocator>
class VectorQueryable : public Queryable<TObj, std::vector, TAllocator>
{
public:

  VectorQueryable(const VectorInternalQueryable<TObj, TAllocator> && other)
    : Queryable<TObj, std::vector, TAllocator>(std::move(other))
  {
  }

  VectorQueryable(const std::vector<TObj, TAllocator> & iterable)
    : Queryable<TObj, std::vector, TAllocator>(iterable)
  {
  }
};

#endif
