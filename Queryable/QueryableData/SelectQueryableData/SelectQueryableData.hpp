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

#include "../../TypeConstraintUtil.hpp"
#include "../../Utilities/Condition.hpp"
#include "../IQueryableData.hpp"
#include "../QueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class SelectQueryableData : public QueryableData<TCurrent, TIterable, TArgs...>
{
  // static_assert(can_iterate<TIterable<TOriginal, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  std::function<TCurrent(TOriginal) > selector;
  std::shared_ptr<QueryableData<TOriginal, TIterable, TArgs...>> original;

public:
  SelectQueryableData(
    std::shared_ptr<QueryableData<TOriginal, TIterable, TArgs...>> && data,
    std::function<TCurrent(TOriginal) > selector) :
      original(std::move(data))
  {
    this->selector = selector;
    this->size = original->StorageSize();
  }
  SelectQueryableData(const SelectQueryableData<TOriginal, TCurrent, TIterable, TArgs...> & data) :
    original(data.original),
    selector(data.selector)
  {
  }

  virtual ~SelectQueryableData() { }

  inline virtual TCurrent & Get(IteratorType type) override
  {
    // std::cout << "Select Data Get" << std::endl;
    this->value = this->selector(this->original->Get(type));
    return this->value;
  }

  inline virtual const TCurrent & ConstGet(IteratorType type) override
  {
    // std::cout << "Select Data ConstGet" << std::endl;
    this->value = this->selector(this->original->ConstGet(type));
    return this->value;
  }

  inline virtual IQueryableData<TCurrent> & Next(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "Select Data Next" << std::endl;
    this->original->Next(type, iterated);
    return *this;
  }

  inline virtual IQueryableData<TCurrent> & Prev(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "Select Data Prev" << std::endl;
    this->original->Prev(type, iterated);
    return *this;
  }

  inline virtual IQueryableData<TCurrent> & Add(int addend, IteratorType type) override
  {
    // std::cout << "Select Data Add" << std::endl;
    this->original->Add(addend, type);
    return *this;
  }

  inline virtual IQueryableData<TCurrent> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "Select Data Subtract" << std::endl;
    this->original->Add(subtrahend, type);
    return *this;
  }

  virtual QueryableIterator<TCurrent> begin() override
  {
    // std::cout << "Select Data begin" << std::endl;
    this->original->begin();
    QueryableIterator<TCurrent> retVal(this, 0, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TCurrent> end() override
  {
    // std::cout << "Select Data end" << std::endl;
    this->original->end();
    QueryableIterator<TCurrent> retVal(this, this->original->Count(), IteratorType::EndForward);
    return retVal;
  }

  virtual QueryableIterator<TCurrent> rbegin() override
  {
    this->original->rbegin();
    QueryableIterator<TCurrent> retVal(this, 0, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TCurrent> rend() override
  {
    this->original->rend();
    QueryableIterator<TCurrent> retVal(this, this->original->Count(), IteratorType::EndReverse);
    return retVal;
  }
};

#endif
