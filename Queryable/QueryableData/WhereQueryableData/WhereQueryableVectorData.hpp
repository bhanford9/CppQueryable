#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "WhereQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableVectorData : public WhereQueryableData<TObj, std::vector, TAllocator>
{
public:
  WhereQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhereQueryable Vector Data Constructor 0" << std::endl;
  }
  WhereQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> && data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::vector, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhereQueryable Vector Data Constructor 1" << std::endl;
  }
  WhereQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TAllocator>> & data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::vector, TAllocator>(data, std::move(condition))
  {
    // std::cout << "WhereQueryable Vector Data Constructor 3" << std::endl;
  }
  WhereQueryableVectorData(const WhereQueryableVectorData<TObj, TAllocator> & other)
    : WhereQueryableData<TObj, std::vector, TAllocator>(other)
  {
    // std::cout << "WhereQueryable Vector Data Constructor 2" << std::endl;
  }

  virtual ~WhereQueryableVectorData() { }

  virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  {
    return std::make_shared<WhereQueryableVectorData<TObj, TAllocator>>(*this);
  }

  virtual IQueryableData<TObj> & Add(int addend, IteratorType type) override
  {
    // std::cout << "[VectorWhere+]" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    return *this;
  }

  virtual IQueryableData<TObj> & Subtract(int subtrahend, IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return *this;
  }

  virtual void InternalAdd(TObj item) override
  {
    this->items->push_back(item);
  }

  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "WhereQueryableVectorData::begin" << std::endl;
    this->beginIterator = this->items->begin();

    int startIndex = this->IncrementBeginForwardPastFalseConditions() - 1;
    // std::cout << "where queryable data start index: " << startIndex << std::endl;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginForward);
    // std::cout << "returning from where queryable begin" << std::endl;
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> end() override
  {
    // std::cout << "WhereQueryableVectorData::end" << std::endl;
    // std::cout << "within where queryable end" << std::endl;
    this->endIterator = this->items->end();

    if (!this->sizeIsCalculated)
    {
      this->Count();
    }

    // although not ideal, it is simpler to keep end the true end
    // this->DecrementEndForwardPastFalseConditions();
    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndForward);
    // std::cout << "leaving where queryable end" << std::endl;
    return retVal;
  }
};

#endif
