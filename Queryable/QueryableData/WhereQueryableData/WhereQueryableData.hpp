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

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class WhereQueryableData : public QueryableData<TObj, TIterable, TArgs...>
{
protected:
  typedef typename std::vector<TObj>::iterator TVectorIterator;

  using TForwardIterator = typename QueryableData<TObj, TIterable, TArgs...>::TForwardIterator;
  // using TReverseIterator = typename QueryableData<TObj, TIterable, TArgs...>::TReverseIterator;

  Condition<TObj> condition;
  std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> original;
  bool sizeIsCalculated;

  void IncrementPastFalseConditions(IteratorType type, size_t & iterated, bool & isForcingToEnd)
  {
    while (this->original->CanIncrement(type) && this->condition && !this->condition(this->original->Get(type)))
    {
      size_t internalIterated = 1;
      this->original->Next(type, internalIterated, isForcingToEnd);
      iterated += internalIterated;
    }
  }

  void DecrementPastFalseConditions(IteratorType type, size_t & iterated)
  {
    while (this->original->CanDecrement(type) && this->condition && !this->condition(this->original->Get(type)))
    {
      size_t internalIterated = 1;
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
    //   return this->original->Count();
    // if (this->sizeIsCalculated)
    // {
    //   return this->size;
    // }

    size_t count = 0;

    // not sure I like needing to get the realized queryable data
    std::shared_ptr<IQueryableData<TObj>> realized = this->original->GetRealizedQueryableData();

    for (const TObj & item : *realized)
    {
      if (condition(item))
      {
        count++;
      }
    }

    this->size = count;
    // this->sizeIsCalculated = true;

    return count;
  }

  virtual void Add(TObj item) override
  {
    if (this->condition(item))
    {
      this->InternalAdd(item);
      this->size++;
    }
  }

//   virtual void Sort(std::shared_ptr<ISorter<TObj, TIterable, TArgs...>> sorter)
//   {
//     this->original->Sort(sorter);
//   }

  // virtual TIterable<TObj, TArgs...> & GetContainer() override
  // {
  //   return this->original->GetContainer();
  // }

  virtual void InternalAdd(TObj item) = 0;

  virtual TObj & Get(IteratorType type) override
  {
    //   std::cout << "Where Queryable Get" << std::endl;
    return this->original->Get(type);
    // *this->value = this->original->Get(type);
    // return *this->value;
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
    //   std::cout << "Where Queryable Next" << std::endl;
    this->original->Next(type, iterated, isForcingToEnd);
    
    if (!isForcingToEnd)
    {
      this->IncrementPastFalseConditions(type, iterated, isForcingToEnd);
    }
    
    return *this;
  }

  virtual IQueryableData<TObj> & Prev(IteratorType type, size_t & iterated) override
  {
    this->original->Prev(type, iterated);
    this->DecrementPastFalseConditions(type, iterated);
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

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "WhereQueryableData::begin" << std::endl;
    QueryableIterator<TObj> child = this->original->begin();

    size_t startIndex = child.index;
    bool isForcingToEnd = false;
    this->IncrementPastFalseConditions(IteratorType::BeginForward, startIndex, isForcingToEnd);
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

    size_t startIndex = child.index;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::EndForward);

    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rbegin() override
  {
    QueryableIterator<TObj> child = this->original->rbegin();

    size_t startIndex = child.index;
    bool isForcingToEnd = false;
    this->IncrementPastFalseConditions(IteratorType::BeginReverse, startIndex, isForcingToEnd);
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);

    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rend() override
  {
    QueryableIterator<TObj> child = this->original->end();

    size_t startIndex = child.index;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::EndReverse);

    return retVal;
  }
};

#endif
