#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VECTORINTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLES_VECTORINTERNALQUERYABLE_H

#include <iostream>
#include <memory>
#include <vector>
#include "QueryableForwardDeclare.hpp"
#include "../InternalQueryable.hpp"
#include "../QueryableType.hpp"
#include "../QueryableData/QueryableVectorData.hpp"
#include "../QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
#include "../QueryableData/SkipWhileQueryableData/SkipWhileQueryableVectorData.hpp"
#include "../QueryableData/TakeWhileQueryableData/TakeWhileQueryableVectorData.hpp"
#include "../Utilities/IWhileCondition.hpp"

template<typename TObj, typename TAllocator>
class VectorInternalQueryable : public InternalQueryable<TObj, std::vector, TObj, TAllocator>
{
public:
  VectorInternalQueryable(TAllocator allocator = {}) :
    InternalQueryable<TObj, std::vector, TObj, TAllocator>(QueryableType::Vector)
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
    : InternalQueryable<TObj, std::vector, TObj, TAllocator>(other)
  {
    this->type = QueryableType::Vector;
  }

  VectorInternalQueryable(const InternalQueryable<TObj, std::vector, TObj, TAllocator> & other)
    : InternalQueryable<TObj, std::vector, TObj, TAllocator>(other)
  {
    this->type = QueryableType::Vector;
  }
  
  VectorInternalQueryable(
    std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && queryableData,
    QueryableType type)
      : InternalQueryable<TObj, std::vector, TObj, TAllocator>(std::move(queryableData), type)
  {
  }

  VectorInternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TAllocator allocator = {})
  {
    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>(std::vector<TObj, TAllocator>(first, last, allocator));
    this->type = QueryableType::Vector;
  }

  virtual void Where(std::function<bool(const TObj &)> condition) override
  {
    this->items = std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(std::move(this->items), std::move(condition));
  }

  virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
  {
    this->items = std::move(std::make_shared<SkipWhileQueryableVectorData<TObj, TAllocator>>(
      std::move(this->items),
      std::move(condition)));
  }

  virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) override
  {
    this->items = std::move(std::make_shared<TakeWhileQueryableVectorData<TObj, TAllocator>>(
      std::move(this->items),
      std::move(condition)));
  }
};

#endif
