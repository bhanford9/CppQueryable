#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDATA_H

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
#include "../../Utilities/IWhileCondition.hpp"
#include "../IQueryableData.hpp"
#include "../QueryableData.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class TakeWhileQueryableData : public QueryableData<TObj, TIterable, TArgs...>
{
protected:
  typedef typename std::vector<TObj>::iterator TVectorIterator;

  using TForwardIterator = typename QueryableData<TObj, TIterable, TArgs...>::TForwardIterator;
  // using TReverseIterator = typename QueryableData<TObj, TIterable, TArgs...>::TReverseIterator;

  std::shared_ptr<IWhileCondition<TObj>> condition;
  std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> original;
  bool sizeIsCalculated;

public:
  TakeWhileQueryableData(
    std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
  {
    // std::cout << "TakeWhileQueryableData move constructor" << std::endl;
    this->original = std::move(data);
    this->condition = std::move(condition);
  }
  TakeWhileQueryableData(
    const std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> & data,
    std::shared_ptr<IWhileCondition<TObj>> && condition)
  {
    // std::cout << "TakeWhileQueryableData copy constructor" << std::endl;
    this->original = data;
    this->condition = std::move(condition);
  }
  TakeWhileQueryableData(const TakeWhileQueryableData<TObj, TIterable, TArgs...> & other)
    : QueryableData<TObj, TIterable, TArgs...>(other)
  {
    // std::cout << "TakeWhileQueryableData copy constructor" << std::endl;
    this->original = other.original;
    this->condition = other.condition;
  }

  virtual ~TakeWhileQueryableData() { }

  // TODO --> this is a pretty bad method to call for this class. finding a way
  //    to track this instead of iterating over the container would be good.
  virtual size_t Count() override
  {
    // TODO --> size is calculated needs to act like the state of an IEnumerable
    //   where the size can simply be returned if it has already been enumerated

    // if (this->sizeIsCalculated)
    // {
    //   std::cout << "size is already calculated" << std::endl;
    //   return this->size;
    // }

    size_t count = 0;

    this->condition->Reset();

    // not sure I like needing to get the realized queryable data
    std::shared_ptr<IQueryableData<TObj>> realized = this->original->GetRealizedQueryableData();

    for (const TObj & item : *realized)
    {
      if (this->condition->Passes(item))
      {
        count++;
      }
      else
      {
        break;
      }
    }

    this->size = count;
    this->sizeIsCalculated = true;

    return count;
  }

  virtual void Add(TObj item) override
  {
    // pretty sure we don't want this method to exist
    // if (this->condition(item))
    // {
    //   this->InternalAdd(item);
    //   this->size++;
    // }
  }

  // virtual TIterable<TObj, TArgs...> & GetContainer() override
  // {
  //   return this->original->GetContainer();
  // }

  virtual void InternalAdd(TObj item) = 0;

  virtual TObj & Get(IteratorType type) override
  {
    return this->original->Get(type);
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    return this->original->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->original->CanDecrement(type);
  }

  virtual const TObj & ConstGet(IteratorType type) override
  {
    return this->original->ConstGet(type);
  }

  virtual IQueryableData<TObj> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
  {
    // std::cout << "While Queryable Next" << std::endl;

    if (!this->condition->Passes(this->original->Get(type)))
    {
      this->original->ForceEnd(type);
    }

    this->original->Next(type, iterated, isForcingToEnd);
    
    return *this;
  }

  virtual IQueryableData<TObj> & Prev(IteratorType type, size_t & iterated) override
  {
    // std::cout << "While Queryable Prev" << std::endl;

    if (!this->condition->Passes(this->original->Get(type)))
    {
        this->original->ForceBegin(type);
    }

    this->original->Prev(type, iterated);

    return *this;
  }

  virtual IQueryableData<TObj> & Add(int addend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    std::cout << "bad" << std::endl;
    size_t dummy = 0;
    while (this->original->CanIncrement(type) && addend-- > 0)
    {
      bool isForcingToEnd = false;
      this->Next(type, dummy, isForcingToEnd);
    }

    return *this;
  }

  virtual IQueryableData<TObj> & Subtract(int subtrahend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    std::cout << "bad" << std::endl;
    size_t dummy = 0;
    while (this->original->CanDecrement(type) && subtrahend-- > 0)
    {
      this->Prev(type, dummy);
    }

    return *this;
  }

  // remove the possibility to iterate if the first element does not pass condition
  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "TakeWhileQueryableData::begin" << std::endl;
    this->condition->Reset();
    QueryableIterator<TObj> child = this->original->begin();


    if (!this->condition->Passes(*child))
    {
      child = this->original->end();
    }

    size_t startIndex = child.index;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginForward);

    return retVal;
  }

  // End only serves as a check of the last element while iterating begin.
  // This will never be used to increment/decrement
  virtual QueryableIterator<TObj> end() override
  {
    // std::cout << "TakeWhileQueryableData::end" << std::endl;
    QueryableIterator<TObj> child = this->original->end();

    size_t startIndex = child.index;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::EndForward);

    return retVal;
  }

  // // remove the possibility to iterate if the first element does not pass condition
  // virtual QueryableIterator<TObj> rbegin() override
  // {
  //   this->condition->Reset();
  //   QueryableIterator<TObj> child = this->original->rbegin();

  //   if (!this->condition->Passes(*child))
  //   {
  //       child = this->original->rend();
  //   }

  //   size_t startIndex = child.index;
  //   QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);

  //   return retVal;
  // }

  // // Rend only serves as a check of the last element while iterating begin.
  // // This will never be used to increment/decrement
  // virtual QueryableIterator<TObj> rend() override
  // {
  //   QueryableIterator<TObj> child = this->original->end();

  //   size_t startIndex = child.index;
  //   QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::EndReverse);

  //   return retVal;
  // }
};

#endif
