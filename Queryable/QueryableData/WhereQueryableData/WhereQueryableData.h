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
    std::cout << "passing" << std::endl;
    while (condition && this->beginIterator != this->items.end() && !condition(*this->beginIterator))
    {
      ++this->beginIterator;
    }
  }

  void IncrementEndForwardPastFalseConditions()
  {
    while (condition && this->endIterator != this->items.end() && !condition(*this->endIterator))
    {
      ++this->endIterator;
    }
  }

  void IncrementBeginReversePastFalseConditions()
  {
    while (condition && this->rbeginIterator != this->items.rend() && !condition(*this->rbeginIterator))
    {
      ++this->rbeginIterator;
    }
  }

  void IncrementEndReversePastFalseConditions()
  {
    while (condition && this->rendIterator != this->items.rend() && !condition(*this->rendIterator))
    {
      ++this->rendIterator;
    }
  }

  void DecrementBeginForwardPastFalseConditions()
  {
    while (condition && this->beginIterator != this->items.begin() && !condition(*this->beginIterator))
    {
      --this->beginIterator;
    }
  }

  void DecrementEndForwardPastFalseConditions()
  {
    while (condition && this->endIterator != this->items.begin() && !condition(*this->endIterator))
    {
      --this->endIterator;
    }
  }

  void DecrementBeginReversePastFalseConditions()
  {
    while (condition && this->rbeginIterator != this->items.rbegin() && !condition(*this->rbeginIterator))
    {
      --this->rbeginIterator;
    }
  }

  void DecrementEndReversePastFalseConditions()
  {
    while (condition && this->rendIterator != this->items.rbegin() && !condition(*this->rendIterator))
    {
      --this->rendIterator;
    }
  }

public:
  WhereQueryableData(
    std::shared_ptr<IQueryableData<TObj, TObj>> data,
    std::function<bool(TObj)> condition)
    : QueryableData<TObj, TObj, TIterable, TArgs...>(std::move(data))
  {
    this->condition += condition;
      std::cout << "WhereQueryableData Constructor 1" << std::endl;
      std::cout << "incoming data size: " << data->Count() << std::endl;
  }
  WhereQueryableData(const WhereQueryableData & other)
    : QueryableData<TObj, TObj, TIterable, TArgs...>(other)
  {
    std::cout << "WhereQueryableData Constructor 2" << std::endl;
  }

  virtual ~WhereQueryableData() { }

  inline virtual IQueryableIteratorData<TObj> & Next() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: ++this->beginIterator; this->IncrementBeginForwardPastFalseConditions(); break;
      case IteratorType::EndForward: ++this->endIterator; this->IncrementEndForwardPastFalseConditions(); break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; this->IncrementBeginReversePastFalseConditions(); break;
      case IteratorType::EndReverse: default: ++this->rendIterator; this->IncrementEndReversePastFalseConditions(); break;
    }

    return *this;
  }

  inline virtual IQueryableIteratorData<TObj> & Prev() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: --this->beginIterator; this->DecrementBeginForwardPastFalseConditions(); break;
      case IteratorType::EndForward: --this->endIterator; this->DecrementEndForwardPastFalseConditions(); break;
      case IteratorType::BeginReverse: --this->rbeginIterator; this->DecrementBeginReversePastFalseConditions(); break;
      case IteratorType::EndReverse: default: --this->rendIterator; this->DecrementEndReversePastFalseConditions(); break;
    }

    return *this;
  }

  inline virtual IQueryableIteratorData<TObj> & Add(int addend) override
  {
    std::cout << "[Where+]" << std::endl;
    // this is the worse possible way to implement this and should be overriden for random access iterators
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

    return *this;
  }

  inline virtual IQueryableIteratorData<TObj> & Subtract(int subtrahend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    bool isFirst = false;

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

    return *this;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> begin() override
  {
    std::cout << "where begin" << std::endl;
    this->beginIterator = this->items.begin();
    this->type = IteratorType::BeginForward;

    this->IncrementBeginForwardPastFalseConditions();
    QueryableIterator<TObj> retVal(this, 0);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> end() override
  {
    std::cout << "where end" << std::endl;
    this->endIterator = this->items.end();
    this->type = IteratorType::EndForward;

    this->DecrementEndForwardPastFalseConditions();
    QueryableIterator<TObj> retVal(this, this->size);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->type = IteratorType::BeginReverse;
    QueryableIterator<TObj> retVal(this, 0);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rend() override
  {
    this->rendIterator = this->items.rend();
    this->type = IteratorType::EndReverse;
    QueryableIterator<TObj> retVal(this, this->size);
    return retVal;
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
