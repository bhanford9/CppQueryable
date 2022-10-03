#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "../../QueryableType.hpp"
#include "../../Utilities/Condition.hpp"
#include "../../Sorters/VectorSorter.hpp"
#include "WhereQueryableData.hpp"

template<typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableVectorData : public WhereQueryableData<TObj, std::vector, TObj, TAllocator>
{
public:
  WhereQueryableVectorData(
    std::shared_ptr<IQueryableData<TObj>> && data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhereQueryable Vector Data Constructor 0" << std::endl;
  }
  WhereQueryableVectorData(
    std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> && data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(std::move(data), std::move(condition))
  {
    // std::cout << "WhereQueryable Vector Data Constructor 1" << std::endl;
  }
  WhereQueryableVectorData(
    const std::shared_ptr<QueryableData<TObj, std::vector, TObj, TAllocator>> & data,
    std::function<bool(TObj)> && condition)
    : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(data, std::move(condition))
  {
    // std::cout << "WhereQueryable Vector Data Constructor 3" << std::endl;
  }
  WhereQueryableVectorData(const WhereQueryableVectorData<TObj, TAllocator> & other)
    : WhereQueryableData<TObj, std::vector, TObj, TAllocator>(other)
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

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::vector<TObj, TAllocator> data(this->items->get_allocator());

    for (const TObj & value : *this)
    {
        data.push_back(value);
    }

    return std::make_shared<QueryableVectorData<TObj, TAllocator>>(std::move(data));
  }
};

#endif
