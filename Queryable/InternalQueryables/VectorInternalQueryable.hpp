#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VECTORINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VECTORINTERNALQUERYABLE_H

#include <iostream>
#include <vector>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableVectorData.hpp"

template<
  typename TObj,
  typename TAllocator>
class VectorInternalQueryable : public InternalQueryable<TObj, std::vector, TAllocator>
{
public:
  VectorInternalQueryable(TAllocator allocator = {}) :
    InternalQueryable<TObj, std::vector, TAllocator>(QueryableType::Vector)
  {
    std::vector<TObj> localVector(allocator);
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(localVector);
  }

  VectorInternalQueryable(const std::vector<TObj, TAllocator> & vector)
  {
    this->type = QueryableType::Vector;
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(vector);
  }

  VectorInternalQueryable(const VectorInternalQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::Vector;
    this->items = other.items;
  }

  VectorInternalQueryable(const InternalQueryable<TObj, std::vector, TAllocator> & other)
    : InternalQueryable<TObj, std::vector, TAllocator>(other)
  {
    this->type = QueryableType::Vector;
  }
  VectorInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, std::vector, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual InternalQueryable<TObj, std::vector, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }
};

#endif
