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
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(vector);
  }

  VectorQueryable(const VectorQueryable<TObj, TAllocator> & other)
  {
    this->type = QueryableType::Vector;
    this->items = other.items;
  }

  VectorQueryable(const Queryable<TObj, std::vector, TAllocator> & other)
    : Queryable<TObj, std::vector, TAllocator>(other)
  {
    this->type = QueryableType::Vector;
  }
  VectorQueryable(
    std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> && queryableData,
    QueryableType type)
      : Queryable<TObj, std::vector, TAllocator>(std::move(queryableData), type)
  {
  }

  virtual Queryable<TObj, std::vector, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }

  virtual Queryable<TObj, std::vector, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    // don't think anything special needs done other than just calling sort
    VectorSorter<TObj, TAllocator> sorter;
    this->items->Sort(sorter, lessThan);
    return *this;
  }
};

#endif
