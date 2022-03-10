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
  typename TAllocator,
  typename TObjOut>
class VectorQueryable : public Queryable<TObj, std::vector, TObjOut, TAllocator>
{
public:
  VectorQueryable(TAllocator allocator = {}) :
    Queryable<TObj, std::vector, TObjOut, TAllocator>(QueryableType::Vector)
  {
    std::vector<TObj> localVector(allocator);
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator, TObjOut>>(localVector);
  }

  VectorQueryable(const std::vector<TObj, TAllocator> & vector)
  {
    this->type = QueryableType::Vector;
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator, TObjOut>>(vector);
  }

  VectorQueryable(const VectorQueryable<TObj, TAllocator, TObjOut> & other)
  {
    this->type = QueryableType::Vector;
    this->items = other.items;
  }

  VectorQueryable(const Queryable<TObj, std::vector, TObjOut, TAllocator> & other)
    : Queryable<TObj, std::vector, TObjOut, TAllocator>(other)
  {
    this->type = QueryableType::Vector;
  }

  virtual Queryable<TObj, std::vector, TObjOut, TAllocator> & Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::move(std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(std::move(this->items), std::move(condition)));
    return *this;
  }

  virtual Queryable<TObj, std::vector, TObjOut, TAllocator> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) override
  {
    // don't think anything special needs done other than just calling sort
    VectorSorter<TObj, TAllocator> sorter;
    this->items->Sort(sorter, lessThan);
    return *this;
  }
};

#endif
