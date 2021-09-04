#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <set>
#include <vector>

#include "../TypeConstraintUtil.h"
#include "../Utilities/Condition.h"
#include "IQueryableData.h"

template<typename TObj, template<typename, typename ...> typename TIterable, typename ...TArgs>
class QueryableData : virtual public IQueryableData<TObj>
{
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  TIterable<TObj, TArgs...> items;
  Condition<TObj> condition;

  typedef typename TIterable<TObj, TArgs...>::iterator t_forwardIterator;
  typedef typename TIterable<TObj, TArgs...>::reverse_iterator t_reverseIterator;

  Iterator<TObj> beginning;
  Iterator<TObj> ending;

  Iterator<TObj> rbeginning;
  Iterator<TObj> rending;

  t_forwardIterator beginIterator;
  t_forwardIterator endIterator;

  t_reverseIterator rbeginIterator;
  t_reverseIterator rendIterator;

  // TODO --> consider making this a pointer so data doesn't have to be copied
  TObj value;

  uint64_t size = 0;

  void IncrementPastCondition(t_forwardIterator & iterator, uint64_t & index)
  {
    while (!(iterator == this->items.end()) && !this->condition(*iterator))
    {
      iterator++;
      index++;
    }
  }

  void DecrementPastCondition(t_forwardIterator & iterator, uint64_t & index)
  {
    while (!(iterator == this->items.begin()) && !this->condition(*iterator))
    {
      iterator--;
      index++;
    }
  }

  void RIncrementPastCondition(t_reverseIterator & iterator, uint64_t & index)
  {
    while (!(iterator == this->items.rend()) && !this->condition(*iterator))
    {
      iterator++;
      index++;
    }
  }

  void RDecrementPastCondition(t_reverseIterator & iterator, uint64_t & index)
  {
    while (!(iterator == this->items.rbegin()) && !this->condition(*iterator))
    {
      iterator--;
      index++;
    }
  }

  virtual void InitForwardBegin()
  {
    this->beginning.Get = [&]() { return &this->beginIterator; };
    this->beginning.Increment = [&](uint64_t & index) { this->IncrementPastCondition(++this->beginIterator, index); };
    this->beginning.Decrement = [&](uint64_t & index) { this->DecrementPastCondition(--this->beginIterator, index); };
    this->beginning.Dereference = [&]() -> TObj& { this->value = *this->beginIterator; return this->value; };
    this->beginning.ConstDereference = [&]() -> const TObj& { return *this->beginIterator; };
    this->beginning.Assign = [&](const Iterator<TObj> & value) { this->beginIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
  }

  virtual void InitForwardEnd()
  {
    this->ending.Get = [&]() { return &this->endIterator; };
    this->ending.Increment = [&](uint64_t & index) { this->IncrementPastCondition(++this->endIterator, index); };
    this->ending.Decrement = [&](uint64_t & index) { this->DecrementPastCondition(--this->endIterator, index); };
    this->ending.Dereference = [&]() -> TObj& { this->value = *this->endIterator; return this->value; };
    this->ending.ConstDereference = [&]() -> const TObj& { return *this->endIterator; };
    this->ending.Assign = [&](const Iterator<TObj> & value) { this->endIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
  }

  virtual void InitReverseBegin()
  {
    this->rbeginning.Get = [&]() { return &this->rbeginIterator; };
    this->rbeginning.Increment = [&](uint64_t & index) { this->RIncrementPastCondition(++this->rbeginIterator, index); };
    this->rbeginning.Decrement = [&](uint64_t & index) { this->RDecrementPastCondition(--this->rbeginIterator, index); };
    this->rbeginning.Dereference = [&]() -> TObj& { this->value = *this->rbeginIterator; return this->value; };
    this->rbeginning.ConstDereference = [&]() -> const TObj& { return *this->rbeginIterator; };
    this->rbeginning.Assign = [&](const Iterator<TObj> & value) { this->rbeginIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
  }

  virtual void InitReverseEnd()
  {
    this->rending.Get = [&]() { return &this->rendIterator; };
    this->rending.Increment = [&](uint64_t & index) { this->RIncrementPastCondition(++this->rendIterator, index); };
    this->rending.Decrement = [&](uint64_t & index) { this->RDecrementPastCondition(--this->rendIterator, index); };
    this->rending.Dereference = [&]() -> TObj& { this->value = *this->rendIterator; return this->value; };
    this->rending.ConstDereference = [&]() -> const TObj& { return *this->rendIterator; };
    this->rending.Assign = [&](const Iterator<TObj> & value) { this->rendIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
  }

public:
  QueryableData(Condition<TObj> condition = Condition<TObj>())
  {
    this->condition = condition;
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  explicit QueryableData(
    TIterable<TObj, TArgs...> items,
    Condition<TObj> condition = Condition<TObj>())
    : QueryableData<TObj, TIterable, TArgs...>(condition)
  {
    this->items = items;

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the children classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(const QueryableData& data)
  {
    this->items = data.items;

    this->beginning = data.beginning;
    this->ending = data.ending;

    this->rbeginning = data.rbeginning;
    this->rending = data.rending;

    this->beginIterator = data.beginIterator;
    this->endIterator = data.endIterator;

    this->rbeginIterator = data.rbeginIterator;
    this->rendIterator = data.rendIterator;

    this->value = data.value;
  }
  virtual ~QueryableData() { }

  virtual TIterable<TObj, TArgs...> GetItems()
  {
    return this->items;
  }

  void AddCondition(std::function<bool(const TObj &)> condition) override
  {
    this->condition += condition;
  }

  bool PassesCondition(const TObj & obj) const override
  {
    return this->condition(obj);
  }

  void Clear() override
  {
    this->items.clear();
    this->size = 0;
  }

  std::vector<TObj> ToVector() override
  {
    std::vector<TObj> objs;

    for (TObj item : this->items)
    {
      objs.push_back(item);
    }

    return objs;
  }

  Iterator<TObj> begin() override
  {
    this->beginIterator = this->items.begin();
    this->beginning.SetIndex(0);
    this->IncrementPastCondition(this->beginIterator, this->beginning.GetIndex());

    return this->beginning;
  }

  Iterator<TObj> end() override
  {
    this->endIterator = this->items.end();
    this->ending.SetIndex(this->size);
    return this->ending;
  }

  Iterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->RIncrementPastCondition(this->rbeginIterator, this->rbeginning.GetIndex());

    return this->rbeginning;
  }

  Iterator<TObj> rend() override
  {
    this->rendIterator = this->items.rend();
    this->rending.SetIndex(this->size);
    return this->rending;
  }
};

#endif
