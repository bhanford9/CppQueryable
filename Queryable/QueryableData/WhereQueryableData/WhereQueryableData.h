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

#include "../../TypeConstraintUtil.h"
#include "../../Utilities/Condition.h"
#include "../IQueryableData.h"
#include "../QueryableData.h"

template<typename TObj, template<typename, typename ...> typename TIterable, typename ...TArgs>
class WhereQueryableData : public QueryableData<TObj, TObj, TIterable, TArgs...>
{
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  // TODO --> use parent's by changing it to a using
  typedef typename std::vector<TObj>::iterator TVectorIterator;

  Condition<TObj> condition;

  void IncrementBeginForwardPastFalseConditions()
  {
    while (condition && this->beginIterator != this->items.end() && !condition(*this->beginIterator))
    {
      ++this->beginIterator;
      this->index++;
    }
  }

  void IncrementEndForwardPastFalseConditions()
  {
    while (condition && this->endIterator != this->items.end() && !condition(*this->endIterator))
    {
      ++this->endIterator;
      this->index++;
    }
  }

  void IncrementBeginReversePastFalseConditions()
  {
    while (condition && this->rbeginIterator != this->items.rend() && !condition(*this->rbeginIterator))
    {
      ++this->rbeginIterator;
      this->index++;
    }
  }

  void IncrementEndReversePastFalseConditions()
  {
    while (condition && this->rendIterator != this->items.rend() && !condition(*this->rendIterator))
    {
      ++this->rendIterator;
      this->index++;
    }
  }

  void DecrementBeginForwardPastFalseConditions()
  {
    while (condition && this->beginIterator != this->items.begin() && !condition(*this->beginIterator))
    {
      --this->beginIterator;
      this->index--;
    }
  }

  void DecrementEndForwardPastFalseConditions()
  {
    while (condition && this->endIterator != this->items.begin() && !condition(*this->endIterator))
    {
      --this->endIterator;
      this->index--;
    }
  }

  void DecrementBeginReversePastFalseConditions()
  {
    while (condition && this->rbeginIterator != this->items.rbegin() && !condition(*this->rbeginIterator))
    {
      --this->rbeginIterator;
      this->index--;
    }
  }

  void DecrementEndReversePastFalseConditions()
  {
    while (condition && this->rendIterator != this->items.rbegin() && !condition(*this->rendIterator))
    {
      --this->rendIterator;
      this->index--;
    }
  }

public:
  WhereQueryableData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : QueryableData<TObj, TObj, TIterable, TArgs...>(std::move(data))
  {
    this->condition += condition;
  }
  WhereQueryableData(const WhereQueryableData & other)
    : QueryableData<TObj, TObj, TIterable, TArgs...>(other)
  {
  }

  virtual ~WhereQueryableData() { }

  inline virtual QueryableIterator<TObj> & operator++() override
  {
    this->index++;

    switch (this->type)
    {
      case IteratorType::BeginForward: ++this->beginIterator; this->IncrementBeginForwardPastFalseConditions(); break;
      case IteratorType::EndForward: ++this->endIterator; this->IncrementEndForwardPastFalseConditions(); break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; this->IncrementBeginReversePastFalseConditions(); break;
      case IteratorType::EndReverse: default: ++this->rendIterator; this->IncrementEndReversePastFalseConditions(); break;
    }

    // not sure if a cast is needed or not
    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TObj> & operator--() override
  {
    this->index--;

    switch (this->type)
    {
      case IteratorType::BeginForward: --this->beginIterator; this->DecrementBeginForwardPastFalseConditions(); break;
      case IteratorType::EndForward: --this->endIterator; this->DecrementEndForwardPastFalseConditions(); break;
      case IteratorType::BeginReverse: --this->rbeginIterator; this->DecrementBeginReversePastFalseConditions(); break;
      case IteratorType::EndReverse: default: --this->rendIterator; this->DecrementEndReversePastFalseConditions(); break;
    }

    // not sure if a cast is needed or not
    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TObj> & operator+(int addend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    this->index += addend; // potentially dangerous, but being lazy for now
    switch (this->type)
    {
      case IteratorType::BeginForward:
        while (this->beginIterator != this->items.end() && addend-- > 0)
        {
          ++this->beginIterator;
          this->IncrementBeginForwardPastFalseConditions();
        }
        break;
      case IteratorType::EndForward:
        while (this->endIterator != this->items.end() && addend-- > 0)
        {
          ++this->endIterator;
          this->IncrementEndForwardPastFalseConditions();
        }
        break;
      case IteratorType::BeginReverse:
        while (this->rbeginIterator != this->items.rend() && addend-- > 0)
        {
          ++this->rbeginIterator;
          this->IncrementBeginReversePastFalseConditions();
        }
        break;
      case IteratorType::EndReverse: default:
        while (this->rendIterator != this->items.rend() && addend-- > 0)
        {
          ++this->rendIterator;
          this->IncrementBeginReversePastFalseConditions();
        }
        break;
    }

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TObj> & operator+=(int addend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    this->index += addend; // potentially dangerous, but being lazy for now
    switch (this->type)
    {
      case IteratorType::BeginForward:
        while (this->beginIterator != this->items.end() && addend-- > 0)
        {
          ++this->beginIterator;
          this->IncrementBeginForwardPastFalseConditions();
        }
        break;
      case IteratorType::EndForward:
        while (this->endIterator != this->items.end() && addend-- > 0)
        {
          ++this->endIterator;
          this->IncrementEndForwardPastFalseConditions();
        }
        break;
      case IteratorType::BeginReverse:
        while (this->rbeginIterator != this->items.rend() && addend-- > 0)
        {
          ++this->rbeginIterator;
          this->IncrementBeginReversePastFalseConditions();
        }
        break;
      case IteratorType::EndReverse: default:
        while (this->rendIterator != this->items.rend() && addend-- > 0)
        {
          ++this->rendIterator;
          this->IncrementBeginReversePastFalseConditions();
        }
        break;
    }

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TObj> & operator-(int subtrahend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    bool isFirst = false;
    this->index -= subtrahend; // potentially dangerous, but being lazy for now

    switch (this->type)
    {
      case IteratorType::BeginForward:
        while (subtrahend-- > 0)
        {
          isFirst = this->beginIterator == this->items.begin();
          --this->beginIterator;
          this->DecrementBeginForwardPastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::EndForward:
        while (subtrahend-- > 0)
        {
          isFirst = this->endIterator == this->items.begin();
          --this->endIterator;
          this->DecrementEndForwardPastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::BeginReverse:
        while (subtrahend-- > 0)
        {
          isFirst = this->rbeginIterator == this->items.rbegin();
          --this->rbeginIterator;
          this->DecrementBeginReversePastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::EndReverse:
        while (subtrahend-- > 0)
        {
          isFirst = this->rendIterator == this->items.rbegin();
          --this->rendIterator;
          this->DecrementBeginReversePastFalseConditions();

          if (isFirst) break;
        }
        break;
    }

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TObj> & operator-=(int subtrahend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    bool isFirst = false;
    this->index -= subtrahend; // potentially dangerous, but being lazy for now

    switch (this->type)
    {
      case IteratorType::BeginForward:
        while (subtrahend-- > 0)
        {
          isFirst = this->beginIterator == this->items.begin();
          --this->beginIterator;
          this->DecrementBeginForwardPastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::EndForward:
        while (subtrahend-- > 0)
        {
          isFirst = this->endIterator == this->items.begin();
          --this->endIterator;
          this->DecrementEndForwardPastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::BeginReverse:
        while (subtrahend-- > 0)
        {
          isFirst = this->rbeginIterator == this->items.rbegin();
          --this->rbeginIterator;
          this->DecrementBeginReversePastFalseConditions();

          if (isFirst) break;
        }
        break;
      case IteratorType::EndReverse:
        while (subtrahend-- > 0)
        {
          isFirst = this->rendIterator == this->items.rbegin();
          --this->rendIterator;
          this->DecrementBeginReversePastFalseConditions();

          if (isFirst) break;
        }
        break;
    }

    return this->AsReferenceIterator();
  }

  virtual int Count() override
  {
    int count = 0;

    for (const TObj & item : this->items)
    {
      if (this->condition(item))
      {
        count++;
      }
    }

    return count;
  }

  virtual std::vector<TObj> ToVector() override
  {
    std::vector<TObj> objs;

    for (TObj item : this->items)
    {
      if (this->condition(item))
      {
        objs.push_back(item);
      }
    }

    return objs;
  }

  virtual void Sort(std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) override
  {
    // TODO
  }

  // virtual void Update(
  //   QueryableIterator<TObj> first,
  //   QueryableIterator<TObj> last,
  //   std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) override
  // {
  //   // TODO SFINAE require this constructor
  //   this->original.get()->Update(this->original.get()->begin(), this->original.get()->end(), compare);
  //   this->size = this->original.get()->Count();
  // }
  //
  // virtual void Update(TVectorIterator first, TVectorIterator last) override
  // {
  //   // TODO SFINAE require this constructor
  //   this->original.get()->Update(first, last);
  //   this->size = this->original.get()->Count();
  // }
};

#endif
