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

  TObj value;

  void IncrementPastCondition(t_forwardIterator & iterator)
  {
    while (!(iterator == this->items.end()) && !this->condition(*iterator))
    {
      iterator++;
    }
  }

  void DecrementPastCondition(t_forwardIterator & iterator)
  {
    while (!(iterator == this->items.begin()) && !this->condition(*iterator))
    {
      iterator--;
    }
  }

  void RIncrementPastCondition(t_reverseIterator & iterator)
  {
    while (!(iterator == this->items.rend()) && !this->condition(*iterator))
    {
      iterator++;
    }
  }

  void RDecrementPastCondition(t_reverseIterator & iterator)
  {
    while (!(iterator == this->items.rbegin()) && !this->condition(*iterator))
    {
      iterator--;
    }
  }

  virtual void InitForwardBegin()
  {
    beginning.Get = [&]() { return &this->beginIterator; };
    beginning.Increment = [&]() { this->IncrementPastCondition(++this->beginIterator); };
    beginning.Decrement = [&]() { this->DecrementPastCondition(--this->beginIterator); };
    beginning.Equal = [&](const Iterator<TObj>& value) { return this->beginIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    beginning.Dereference = [&]() -> TObj& { this->value = *this->beginIterator; return this->value; };
    beginning.ConstDereference = [&]() -> const TObj& { return *this->beginIterator; };
    beginning.Assign = [&](const Iterator<TObj> & value) { this->beginIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
  }

  virtual void InitForwardEnd()
  {
    ending.Get = [&]() { return &this->endIterator; };
    ending.Increment = [&]() { this->IncrementPastCondition(++this->endIterator); };
    ending.Decrement = [&]() { this->DecrementPastCondition(--this->endIterator); };
    ending.Equal = [&](const Iterator<TObj>& value) { return this->endIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Dereference = [&]() -> TObj& { this->value = *this->endIterator; return this->value; };
    ending.ConstDereference = [&]() -> const TObj& { return *this->endIterator; };
    ending.Assign = [&](const Iterator<TObj> & value) { this->endIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
  }

  virtual void InitReverseBegin()
  {
    rbeginning.Get = [&]() { return &this->rbeginIterator; };
    rbeginning.Increment = [&]() { this->RIncrementPastCondition(++this->rbeginIterator); };
    rbeginning.Decrement = [&]() { this->RDecrementPastCondition(--this->rbeginIterator); };
    rbeginning.Equal = [&](const Iterator<TObj>& value) { return this->rbeginIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rbeginning.Dereference = [&]() -> TObj& { this->value = *this->rbeginIterator; return this->value; };
    rbeginning.ConstDereference = [&]() -> const TObj& { return *this->rbeginIterator; };
    rbeginning.Assign = [&](const Iterator<TObj> & value) { this->rbeginIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
  }

  virtual void InitReverseEnd()
  {
    rending.Get = [&]() { return &this->rendIterator; };
    rending.Increment = [&]() { this->RIncrementPastCondition(++this->rendIterator); };
    rending.Decrement = [&]() { this->RDecrementPastCondition(--this->rendIterator); };
    rending.Equal = [&](const Iterator<TObj>& value) { return this->rendIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Dereference = [&]() -> TObj& { this->value = *this->rendIterator; return this->value; };
    rending.ConstDereference = [&]() -> const TObj& { return *this->rendIterator; };
    rending.Assign = [&](const Iterator<TObj> & value) { this->rendIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
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
    this->IncrementPastCondition(this->beginIterator);

    return this->beginning;
  }

  Iterator<TObj> end() override
  {
    this->endIterator = this->items.end();
    return this->ending;
  }

  Iterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->RIncrementPastCondition(this->rbeginIterator);

    return this->rbeginning;
  }

  Iterator<TObj> rend() override
  {
    this->rendIterator = this->items.rend();
    return this->rending;
  }
};

#endif
