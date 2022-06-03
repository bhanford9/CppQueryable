#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDATA_H

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

// TODO --> add TOut template argument
template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class WhereQueryableData : public QueryableData<TObj, TIterable, TArgs...>
{
  // static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  // TODO --> use parent's by changing it to a using
  typedef typename std::vector<TObj>::iterator TVectorIterator;

  using TForwardIterator = typename QueryableData<TObj, TIterable, TArgs...>::TForwardIterator;
  using TReverseIterator = typename QueryableData<TObj, TIterable, TArgs...>::TReverseIterator;

  Condition<TObj> condition;
  std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> original;
  bool sizeIsCalculated;

  void IncrementPastFalseConditions(IteratorType type, uint64_t & iterated)
  {
    while (this->original->CanIncrement(type) && this->condition && !this->condition(this->original->Get(type)))
    {
      uint64_t internalIterated = 1;
      this->original->Next(type, internalIterated);
      iterated += internalIterated;
    }
  }

  void DecrementPastFalseConditions(IteratorType type, uint64_t & iterated)
  {
    while (this->original->CanDecrement(type) && this->condition && !this->condition(this->original->Get(type)))
    {
      uint64_t internalIterated = 1;
      this->original->Prev(type, internalIterated);
      iterated += internalIterated;
    }
  }

public:
  // WhereQueryableData(
  //   std::shared_ptr<IQueryableData<TObj>> && data,
  //   std::function<bool(TObj)> && condition)
  //   : QueryableData<TObj, TIterable, TArgs...>(std::move(data))
  // {
  //   this->condition += condition;
  // }
  WhereQueryableData(
    std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data,
    std::function<bool(TObj)> && condition)
    // : QueryableData<TObj, TIterable, TArgs...>(std::move(data))
  {
    // std::cout << "WhereQueryableDAta move constructor" << std::endl;
    this->original = std::move(data);
    this->sizeIsCalculated = false;
    this->condition += condition;
  }
  WhereQueryableData(
    const std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> & data,
    std::function<bool(TObj)> && condition)
    // : QueryableData<TObj, TIterable, TArgs...>(*data)
  {
    // std::cout << "WhereQueryableDAta copy constructor" << std::endl;
    this->original = data;
    this->sizeIsCalculated = false;
    this->condition += condition;
  }
  WhereQueryableData(const WhereQueryableData<TObj, TIterable, TArgs...> & other)
    : QueryableData<TObj, TIterable, TArgs...>(other)
  {
    // std::cout << "WhereQueryableDAta copy constructor" << std::endl;
    this->original = other.original;
    this->sizeIsCalculated = other.sizeIsCalculated;
    this->condition = other.condition;
  }

  virtual ~WhereQueryableData() { }

  // TODO --> this is a pretty bad method to call for this class. finding a way
  //    to track this instead of iterating over the container would be good.
  virtual size_t Count() override
  {
    return this->original->Count();
    // if (this->sizeIsCalculated)
    // {
    //   return this->size;
    // }

    // size_t count = 0;

    // for (TObj item : *this->original)
    // {
    //   if (condition(item))
    //   {
    //     count++;
    //   }
    // }

    // this->size = count;
    // this->sizeIsCalculated = true;

    // return count;
  }

  virtual void Add(TObj item) override
  {
    if (this->condition(item))
    {
      this->InternalAdd(item);
      this->size++;
    }
  }

  virtual TIterable<TObj, TArgs...> & GetContainer() override
  {
    return this->original->GetContainer();
  }

  virtual void InternalAdd(TObj item) = 0;

  virtual TObj & Get(IteratorType type) override
  {
    //   std::cout << "Where Queryable Get" << std::endl;
    this->value = this->original->Get(type);
    return this->value;
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

  virtual IQueryableData<TObj> & Next(IteratorType type, uint64_t & iterated) override
  {
    //   std::cout << "Where Queryable Next" << std::endl;
    this->original->Next(type, iterated);
    this->IncrementPastFalseConditions(type, iterated);
    return *this;
  }

  virtual IQueryableData<TObj> & Prev(IteratorType type, uint64_t & iterated) override
  {
    this->original->Prev(type, iterated);
    this->DecrementPastFalseConditions(type, iterated);
    return *this;
  }

  virtual IQueryableData<TObj> & Add(int addend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    uint64_t dummy = 0;
    while (this->original->CanIncrement(type) && addend-- > 0)
    {
      this->Next(type, dummy);
    }

    return *this;
  }

  virtual IQueryableData<TObj> & Subtract(int subtrahend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    uint64_t dummy = 0;
    while (this->original->CanDecrement(type) && subtrahend-- > 0)
    {
      this->Prev(type, dummy);
    }

    return *this;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "WhereQueryableData::begin" << std::endl;
    QueryableIterator<TObj> child = this->original->begin();

    uint64_t startIndex = child.index;
    this->IncrementPastFalseConditions(IteratorType::BeginForward, startIndex);
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginForward);

    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> end() override
  {
    // std::cout << "WhereQueryableData::end" << std::endl;
    QueryableIterator<TObj> child = this->original->end();

    uint64_t startIndex = child.index;
    // uint64_t iterated = 0;
    // this->DecrementPastFalseConditions(IteratorType::EndForward, iterated);
    // startIndex -= iterated;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::EndForward);

    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rbegin() override
  {
    // TODO
    this->original->rbegin();
    uint64_t startIndex = 0;
    this->IncrementPastFalseConditions(IteratorType::BeginReverse, startIndex);
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rend() override
  {
    // TODO
    this->original->rend();

    if (!this->sizeIsCalculated)
    {
      this->Count();
    }

    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndReverse);
    return retVal;
  }
};

#endif
