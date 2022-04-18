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
  bool sizeIsCalculated;

  uint64_t IncrementBeginForwardPastFalseConditions()
  {
    uint64_t iterated = 1;

    // TODO apply this to the other methods as well so we are not copying end() on every iteration
    TForwardIterator last = this->items->end();
    while (condition && this->beginIterator != last && !condition(*this->beginIterator))
    {
      ++this->beginIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t IncrementEndForwardPastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->endIterator != this->items->end() && !condition(*this->endIterator))
    {
      ++this->endIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t IncrementBeginReversePastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->rbeginIterator != this->items->rend() && !condition(*this->rbeginIterator))
    {
      ++this->rbeginIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t IncrementEndReversePastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->rendIterator != this->items->rend() && !condition(*this->rendIterator))
    {
      ++this->rendIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t DecrementBeginForwardPastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->beginIterator != this->items->begin() && !condition(*this->beginIterator))
    {
      --this->beginIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t DecrementEndForwardPastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->endIterator != this->items->begin() && !condition(*this->endIterator))
    {
      --this->endIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t DecrementBeginReversePastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->rbeginIterator != this->items->rbegin() && !condition(*this->rbeginIterator))
    {
      --this->rbeginIterator;
      // iterated++;
    }

    return iterated;
  }

  uint64_t DecrementEndReversePastFalseConditions()
  {
    uint64_t iterated = 1;

    while (condition && this->rendIterator != this->items->rbegin() && !condition(*this->rendIterator))
    {
      --this->rendIterator;
      // iterated++;
    }

    return iterated;
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
    : QueryableData<TObj, TIterable, TArgs...>(std::move(data))
  {
    this->sizeIsCalculated = false;
    this->condition += condition;
  }
  WhereQueryableData(const WhereQueryableData<TObj, TIterable, TArgs...> & other)
    : QueryableData<TObj, TIterable, TArgs...>(other)
  {
    this->sizeIsCalculated = other.sizeIsCalculated;
    this->condition = other.condition;
  }

  virtual ~WhereQueryableData() { }

  // TODO --> this is a pretty bad method to call for this class. finding a way
  //    to track this instead of iterating over the container would be good.
  virtual size_t Count() override
  {
    if (this->sizeIsCalculated)
    {
      return this->size;
    }

    size_t count = 0;

    for (TObj item : *this->items)
    {
      if (condition(item))
      {
        count++;
      }
    }

    this->size = count;
    this->sizeIsCalculated = true;

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

  virtual void InternalAdd(TObj item) = 0;

  virtual IQueryableData<TObj> & Next(IteratorType type, uint64_t & iterated) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: ++this->beginIterator; iterated = this->IncrementBeginForwardPastFalseConditions(); break;
      case IteratorType::EndForward: ++this->endIterator; iterated = this->IncrementEndForwardPastFalseConditions(); break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; iterated = this->IncrementBeginReversePastFalseConditions(); break;
      case IteratorType::EndReverse: default: ++this->rendIterator; iterated = this->IncrementEndReversePastFalseConditions(); break;
    }
    return *this;
  }

  virtual IQueryableData<TObj> & Prev(IteratorType type, uint64_t & iterated) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: --this->beginIterator; iterated = this->DecrementBeginForwardPastFalseConditions(); break;
      case IteratorType::EndForward: --this->endIterator; iterated = this->DecrementEndForwardPastFalseConditions(); break;
      case IteratorType::BeginReverse: --this->rbeginIterator; iterated = this->DecrementBeginReversePastFalseConditions(); break;
      case IteratorType::EndReverse: default: --this->rendIterator; iterated = this->DecrementEndReversePastFalseConditions(); break;
    }

    return *this;
  }

  virtual IQueryableData<TObj> & Add(int addend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (type)
    {
      case IteratorType::BeginForward:
        while (this->beginIterator != this->items->end() && addend-- > 0)
        {
          ++this->beginIterator;
          this->IncrementBeginForwardPastFalseConditions();
        }
        break;
      case IteratorType::EndForward:
        while (this->endIterator != this->items->end() && addend-- > 0)
        {
          ++this->endIterator;
          this->IncrementEndForwardPastFalseConditions();
        }
        break;
      case IteratorType::BeginReverse:
        while (this->rbeginIterator != this->items->rend() && addend-- > 0)
        {
          ++this->rbeginIterator;
          this->IncrementBeginReversePastFalseConditions();
        }
        break;
      case IteratorType::EndReverse: default:
        while (this->rendIterator != this->items->rend() && addend-- > 0)
        {
          ++this->rendIterator;
          this->IncrementBeginReversePastFalseConditions();
        }
        break;
    }

    return *this;
  }

  virtual IQueryableData<TObj> & Subtract(int subtrahend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    bool isFirst = false;

    switch (type)
    {
      case IteratorType::BeginForward:
        while (subtrahend-- > 0)
        {
          isFirst = this->beginIterator == this->items->begin();
          --this->beginIterator;
          this->DecrementBeginForwardPastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::EndForward:
        while (subtrahend-- > 0)
        {
          isFirst = this->endIterator == this->items->begin();
          --this->endIterator;
          this->DecrementEndForwardPastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::BeginReverse:
        while (subtrahend-- > 0)
        {
          isFirst = this->rbeginIterator == this->items->rbegin();
          --this->rbeginIterator;
          this->DecrementBeginReversePastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::EndReverse:
        while (subtrahend-- > 0)
        {
          isFirst = this->rendIterator == this->items->rbegin();
          --this->rendIterator;
          this->DecrementBeginReversePastFalseConditions();

          if (isFirst) break;
        }
        break;
    }

    return *this;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> begin() override
  {
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

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rbegin() override
  {
    // TODO
    this->rbeginIterator = this->items->rbegin();
    int startIndex = this->IncrementBeginReversePastFalseConditions() - 1;
    QueryableIterator<TObj> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rend() override
  {
    // TODO
    this->rendIterator = this->items->rend();

    if (!this->sizeIsCalculated)
    {
      this->Count();
    }

    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndReverse);
    return retVal;
  }
};

#endif
