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
  typename TStoring,
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class WhereQueryableData : public QueryableData<TStoring, TIterable, TIterating, TArgs...>
{
protected:
  typedef typename std::vector<TStoring>::iterator TVectorIterator;

  using TForwardIterator = typename QueryableData<TStoring, TIterable, TIterating, TArgs...>::TForwardIterator;
  // using TReverseIterator = typename QueryableData<TStoring, TIterable, TArgs...>::TReverseIterator;

  Condition<TIterating> condition;
  std::shared_ptr<QueryableData<TStoring, TIterable, TIterating, TArgs...>> original;
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
  //   std::shared_ptr<IQueryableData<TStoring>> && data,
  //   std::function<bool(TStoring)> && condition)
  //   : QueryableData<TStoring, TIterable, TArgs...>(std::move(data))
  // {
  //   this->condition += condition;
  // }
  WhereQueryableData(
    std::shared_ptr<QueryableData<TStoring, TIterable, TIterating, TArgs...>> && data,
    std::function<bool(TIterating)> && condition)
    // : QueryableData<TStoring, TIterable, TArgs...>(std::move(data))
  {
    // std::cout << "WhereQueryableDAta move constructor" << std::endl;
    this->original = std::move(data);
    this->sizeIsCalculated = false;
    this->condition += condition;
  }
  WhereQueryableData(
    const std::shared_ptr<QueryableData<TStoring, TIterable, TIterating, TArgs...>> & data,
    std::function<bool(TIterating)> && condition)
    // : QueryableData<TStoring, TIterable, TArgs...>(*data)
  {
    // std::cout << "WhereQueryableDAta copy constructor" << std::endl;
    this->original = data;
    this->sizeIsCalculated = false;
    this->condition += condition;
  }
  WhereQueryableData(const WhereQueryableData<TStoring, TIterable, TIterating, TArgs...> & other)
    : QueryableData<TStoring, TIterable, TIterating, TArgs...>(other)
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
    std::shared_ptr<IQueryableData<TIterating>> realized = this->original->GetRealizedQueryableData();

    for (const TIterating & item : *realized)
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

  virtual void Add(TIterating item) override
  {
    if (this->condition(item))
    {
      this->InternalAdd(item);
      this->size++;
    }
  }

//   virtual void Sort(std::shared_ptr<ISorter<TStoring, TIterable, TArgs...>> sorter)
//   {
//     this->original->Sort(sorter);
//   }

  // virtual TIterable<TStoring, TArgs...> & GetContainer() override
  // {
  //   return this->original->GetContainer();
  // }

  virtual void InternalAdd(TIterating item) = 0;

  virtual TIterating & Get(IteratorType type) override
  {
    //   std::cout << "Where Queryable Get" << std::endl;
    return this->original->Get(type);
    //  *this->value = *this->original->Get(type);
    // return  *this->value;
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    return this->original->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->original->CanDecrement(type);
  }

  virtual const TIterating & ConstGet(IteratorType type) override
  {
    return this->original->ConstGet(type);
  }

  virtual IQueryableData<TIterating> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
  {
    //   std::cout << "Where Queryable Next" << std::endl;
    this->original->Next(type, iterated, isForcingToEnd);
    
    if (!isForcingToEnd)
    {
      this->IncrementPastFalseConditions(type, iterated, isForcingToEnd);
    }
    
    return *this;
  }

  virtual IQueryableData<TIterating> & Prev(IteratorType type, size_t & iterated) override
  {
    this->original->Prev(type, iterated);
    this->DecrementPastFalseConditions(type, iterated);
    return *this;
  }

  virtual IQueryableData<TIterating> & Add(int addend, IteratorType type) override
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

  virtual IQueryableData<TIterating> & Subtract(int subtrahend, IteratorType type) override
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

  virtual QueryableIterator<TIterating> begin() override
  {
    // std::cout << "WhereQueryableData::begin" << std::endl;
    QueryableIterator<TIterating> child = this->original->begin();

    size_t startIndex = child.index;
    bool isForcingToEnd = false;
    this->IncrementPastFalseConditions(IteratorType::BeginForward, startIndex, isForcingToEnd);
    QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::BeginForward);

    return retVal;
  }

  virtual QueryableIterator<TIterating> end() override
  {
    // std::cout << "WhereQueryableData::end" << std::endl;
    QueryableIterator<TIterating> child = this->original->end();

    size_t startIndex = child.index;
    QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::EndForward);

    return retVal;
  }

  virtual QueryableIterator<TIterating> rbegin() override
  {
    QueryableIterator<TIterating> child = this->original->rbegin();

    size_t startIndex = child.index;
    bool isForcingToEnd = false;
    this->IncrementPastFalseConditions(IteratorType::BeginReverse, startIndex, isForcingToEnd);
    QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);

    return retVal;
  }

  virtual QueryableIterator<TIterating> rend() override
  {
    QueryableIterator<TIterating> child = this->original->end();

    size_t startIndex = child.index;
    QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::EndReverse);

    return retVal;
  }
};

#endif
