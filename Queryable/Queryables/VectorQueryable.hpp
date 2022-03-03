#ifndef CPPQUERYABLE_QUERYABLE_VECTORQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_VECTORQUERYABLE_H

#include <iostream>
#include <vector>
#include "QueryableForwardDeclare.hpp"
#include "../Queryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableVectorData.hpp"

template<
  typename TObj,
  typename TAllocator>
class VectorQueryable : public Queryable<TObj, std::vector, TAllocator>
{
public:
  VectorQueryable(TAllocator allocator = {}) :
    Queryable<TObj, std::vector, TAllocator>(QueryableType::Vector)
  {
    std::vector<TObj> localVector(allocator);
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(localVector);
  }

  VectorQueryable(const std::vector<TObj, TAllocator> & vector)
  {
    this->type = QueryableType::Vector;
    this->items = std::move(std::make_shared<QueryableVectorData<TObj, TAllocator>>(vector));
  }

  VectorQueryable(const VectorQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::Vector;
    this->items = other.items;
  }
};

#endif
