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
  std::function<TCurrent(TOriginal)> selector;
  std::shared_ptr<QueryableData<TOriginal, TIterable, TArgs...>> original;

public:
  SelectQueryableData(
    std::shared_ptr<QueryableData<TOriginal, TIterable, TArgs...>> && data,
    std::function<TCurrent(TOriginal) > selector) :
      selector(selector),
      original(std::move(data))
  {
    // std::cout << "select queryable parent data moving" << std::endl;
    this->size = original->Count();
  }
  SelectQueryableData(
    const std::shared_ptr<QueryableData<TOriginal, TIterable, TArgs...>> & data,
    std::function<TCurrent(TOriginal) > selector) :
      selector(selector),
      original(data)
  {
    // std::cout << "select queryable parent data copying" << std::endl;
    this->size = original->Count();
  }
  SelectQueryableData(const SelectQueryableData<TOriginal, TCurrent, TIterable, TArgs...> & data) :
    selector(data.selector),
    original(data.original)
  {
    this->size = original->Count();
  }

  virtual ~SelectQueryableData() { }





    // TODO --> this is going to fail for select->sort
  // virtual TIterable<TCurrent, TArgs...> & GetContainer() override
  // {
  //   return *this->items;
  // }



  // cpp sorting algorithms are dependent on swaping references of values within the container.
  // The corresponding referenced value is a completely different thing after Select has been
  // done, but the entire contianer is not realized due to the deferred nature of the selection.
  //
  // In order for this to work, some kind of ToRealizedQueryableData will need to be in place
  // for all QueryableData objects that performs any of the "deferred" actions in the chain of
  // QueryableDatas and returns it as its most basic type of QueryableData
  //
  // Every child class will need to do its own Sort implemnetation so it can inately know what
  // kind of base QueryableData instantiation to resolve to.
//   virtual void Sort(std::shared_ptr<ISorter<TOriginal, TIterable, TArgs...>> sorter)
//   {
//     this->original->Sort(sorter);
//   }


  virtual bool CanIncrement(IteratorType type) override
  {
    return this->original->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->original->CanDecrement(type);
  }

  // I think this will make it so sorting won't work for Deque/Vector after calling Select
  // potential fix may be check this scenario and ToList it before trying to sort
  virtual TCurrent & Get(IteratorType type) override
  {
    switch (type)
    {
    //   case IteratorType::BeginForward: return *this->beginIterator;
    //   case IteratorType::EndForward: return *this->endIterator;
    //   case IteratorType::BeginReverse: return *this->rbeginIterator;
    //   case IteratorType::EndReverse: default: return *this->rendIterator;
      case IteratorType::BeginForward: { this->value = this->selector(this->original->Get(type)); return this->value; }
      case IteratorType::EndForward: { this->value = this->selector(this->original->Get(type)); return this->value; }
      // case IteratorType::BeginReverse: { this->value = this->selector(this->original->Get(type)); return this->value; }
      // case IteratorType::EndReverse: 
      default: { this->value = this->selector(this->original->Get(type)); return this->value; }
    }
    // std::cout << "Select Data Get" << std::endl;
    // this->value = this->selector(this->original->Get(type));
    // return this->value;
  }

  virtual const TCurrent & ConstGet(IteratorType type) override
  {
    switch (type)
    {
    //   case IteratorType::BeginForward: return *this->beginIterator;
    //   case IteratorType::EndForward: return *this->endIterator;
    //   case IteratorType::BeginReverse: return *this->rbeginIterator;
    //   case IteratorType::EndReverse: default: return *this->rendIterator;
      case IteratorType::BeginForward: { this->value = this->selector(this->original->Get(type)); return this->value; }
      case IteratorType::EndForward: { this->value = this->selector(this->original->Get(type)); return this->value; }
      // case IteratorType::BeginReverse: { this->value = this->selector(this->original->Get(type)); return this->value; }
      // case IteratorType::EndReverse:
      default: { this->value = this->selector(this->original->Get(type)); return this->value; }
    }
    // std::cout << "Select Data ConstGet" << std::endl;
    // this->value = this->selector(this->original->ConstGet(type));
    // return this->value;
  }

  virtual IQueryableData<TCurrent> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
  {
    // std::cout << "Select Can Increment: " << this->original->CanIncrement(type) << std::endl;
    // std::cout << "Select Data Next before value: " << this->original->Get(type) << std::endl;
    this->original->Next(type, iterated, isForcingToEnd);
    return *this;
  }

  virtual IQueryableData<TCurrent> & Prev(IteratorType type, size_t & iterated) override
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

  // virtual QueryableIterator<TCurrent> rbegin() override
  // {
  //   this->original->rbegin();
  //   QueryableIterator<TCurrent> retVal(this->Clone(), 0, IteratorType::BeginReverse);
  //   return retVal;
  // }

  // virtual QueryableIterator<TCurrent> rend() override
  // {
  //   this->original->rend();
  //   QueryableIterator<TCurrent> retVal(this->Clone(), this->original->Count(), IteratorType::EndReverse);
  //   return retVal;
  // }
};

#endif
