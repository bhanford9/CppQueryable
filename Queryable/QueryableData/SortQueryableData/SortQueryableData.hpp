#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "../IQueryableData.hpp"
#include "../QueryableData.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename TLessThan = std::less<TObj>,
  typename ...TArgs>
class SortQueryableData : public QueryableData<TObj, TIterable, TArgs...>
{
protected:
  std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> original;
  TLessThan compare;
  bool hasSorted = false;

public:
  SortQueryableData(
    std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data,
    const TLessThan & compare) :
      original(std::move(data)),
      compare(compare)
  {
    // std::cout << "sort queryable parent data moving" << std::endl;
    this->size = original->Count();
    this->original->Sort(compare);
  }
  SortQueryableData(
    const std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> & data,
    const TLessThan & compare) :
      original(data),
      compare(compare)
  {
    // std::cout << "sort queryable parent data copying" << std::endl;
    this->size = original->Count();
    this->original->Sort(compare);
  }
  SortQueryableData(const SortQueryableData<TObj, TIterable, TArgs...> & data,
    const TLessThan & compare) :
    original(data.original),
    compare(compare)
  {
    this->size = original->Count();
    this->original->Sort(compare);
  }

  virtual ~SortQueryableData() { }

  virtual TIterable & GetContainer() override
  {
    return *this->original->GetContainer();
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    return this->original->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->original->CanDecrement(type);
  }

  virtual TCurrent & Get(IteratorType type) override
  {
    // std::cout << "Sort Data Get" << std::endl;
    this->value = this->original->Get(type);
    return this->value;
  }

  virtual const TCurrent & ConstGet(IteratorType type) override
  {
    // std::cout << "Select Data ConstGet" << std::endl;
    this->value = this->selector(this->original->ConstGet(type));
    return this->value;
  }

  virtual IQueryableData<TCurrent> & Next(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "Select Can Increment: " << this->original->CanIncrement(type) << std::endl;
    // std::cout << "Select Data Next before value: " << this->original->Get(type) << std::endl;
    this->original->Next(type, iterated);
    return *this;
  }

  virtual IQueryableData<TCurrent> & Prev(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "Select Data Prev" << std::endl;
    this->original->Prev(type, iterated);
    return *this;
  }

  virtual IQueryableData<TCurrent> & Add(int addend, IteratorType type) override
  {
    // std::cout << "Select Data Add" << std::endl;
    this->original->Add(addend, type);
    return *this;
  }

  virtual IQueryableData<TCurrent> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "Select Data Subtract" << std::endl;
    this->original->Add(subtrahend, type);
    return *this;
  }

  virtual QueryableIterator<TCurrent> begin() override
  {
    // std::cout << "Select Data begin" << std::endl;
    QueryableIterator<TOriginal> child = this->original->begin();
    QueryableIterator<TCurrent> retVal(this->Clone(), child.index, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TCurrent> end() override
  {
    // std::cout << "Select Data end" << std::endl;
    QueryableIterator<TOriginal> child = this->original->end();
    QueryableIterator<TCurrent> retVal(this->Clone(), child.index, IteratorType::EndForward);
    return retVal;
  }

  virtual QueryableIterator<TCurrent> rbegin() override
  {
    this->original->rbegin();
    QueryableIterator<TCurrent> retVal(this->Clone(), 0, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TCurrent> rend() override
  {
    this->original->rend();
    QueryableIterator<TCurrent> retVal(this->Clone(), this->original->Count(), IteratorType::EndReverse);
    return retVal;
  }

};

#endif