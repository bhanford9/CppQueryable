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
#include "IQueryableData.h"

template<typename TObj, template<typename, typename ...> typename TIterable, typename ...TArgs>
class QueryableData : virtual public IQueryableData<TObj>
{
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  TIterable<TObj, TArgs...> items;

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

  virtual void InitForwardBegin()
  {
    beginning.Get = [&]() { return &this->beginIterator; };
    beginning.Increment = [&]() { this->beginIterator++; };
    beginning.Decrement = [&]() { this->beginIterator--; };
    beginning.Equal = [&](const Iterator<TObj>& value) { return this->beginIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    beginning.Dereference = [&]() -> TObj& { this->value = *this->beginIterator; return this->value; };
    beginning.ConstDereference = [&]() -> const TObj& { return *this->beginIterator; };
    beginning.Add = [&](int add) { std::advance(this->beginIterator, add); };
    beginning.Subtract = [&](int subtract) { std::advance(this->beginIterator, -subtract); };
    // beginning.LessThan = [&](const Iterator<TObj>& value) -> bool { return this->beginIterator < *static_cast<t_forwardIterator*>(value.Get()); };
    beginning.Assign = [&](const Iterator<TObj> & value) { this->beginIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
    // beginning.IterSubtract = [&](const Iterator<TObj>& subtract) -> int { return this->beginIterator - *static_cast<t_forwardIterator*>(subtract.Get()); };
  }

  virtual void InitForwardEnd()
  {
    ending.Get = [&]() { return &this->endIterator; };
    ending.Increment = [&]() { this->endIterator++; };
    ending.Decrement = [&]() { this->endIterator--; };
    ending.Equal = [&](const Iterator<TObj>& value) { return this->endIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Dereference = [&]() -> TObj& { this->value = *this->endIterator; return this->value; };
    ending.ConstDereference = [&]() -> const TObj& { return *this->endIterator; };
    ending.Add = [&](int add) { std::advance(this->endIterator, add); };
    ending.Subtract = [&](int subtract) { std::advance(this->endIterator, -subtract); };
    // ending.LessThan = [&](const Iterator<TObj>& value) -> bool { return this->endIterator < *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Assign = [&](const Iterator<TObj> & value) { this->endIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
    // ending.IterSubtract = [&](const Iterator<TObj>& subtract) -> int { return this->endIterator - *static_cast<t_forwardIterator*>(subtract.Get()); };
  }

  virtual void InitReverseBegin()
  {
    rbeginning.Get = [&]() { return &this->rbeginIterator; };
    rbeginning.Increment = [&]() { this->rbeginIterator++; };
    rbeginning.Decrement = [&]() { this->rbeginIterator--; };
    rbeginning.Equal = [&](const Iterator<TObj>& value) { return this->rbeginIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rbeginning.Dereference = [&]() -> TObj& { this->value = *this->rbeginIterator; return this->value; };
    rbeginning.ConstDereference = [&]() -> const TObj& { return *this->rbeginIterator; };
    rbeginning.Add = [&](int add) { std::advance(this->rbeginIterator, add); };
    rbeginning.Subtract = [&](int subtract) { std::advance(this->rbeginIterator, -subtract); };
    // rbeginning.LessThan = [&](const Iterator<TObj>& value) -> bool { return this->rbeginIterator < *static_cast<t_reverseIterator*>(value.Get()); };
    rbeginning.Assign = [&](const Iterator<TObj> & value) { this->rbeginIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
    // rbeginning.IterSubtract = [&](const Iterator<TObj>& subtract) -> int { return this->rbeginIterator - *static_cast<t_reverseIterator*>(subtract.Get()); };
  }

  virtual void InitReverseEnd()
  {
    rending.Get = [&]() { return &this->rendIterator; };
    rending.Increment = [&]() { this->rendIterator++; };
    rending.Decrement = [&]() { this->rendIterator--; };
    rending.Equal = [&](const Iterator<TObj>& value) { return this->rendIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Dereference = [&]() -> TObj& { this->value = *this->rendIterator; return this->value; };
    rending.ConstDereference = [&]() -> const TObj& { return *this->rendIterator; };
    rending.Add = [&](int add) { std::advance(this->rendIterator, add); };
    rending.Subtract = [&](int subtract) { std::advance(this->rendIterator, -subtract); };
    // rending.LessThan = [&](const Iterator<TObj>& value) -> bool { return this->rendIterator < *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Assign = [&](const Iterator<TObj> & value) { this->rendIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
    // rending.IterSubtract = [&](const Iterator<TObj>& subtract) -> int { return this->rendIterator - *static_cast<t_reverseIterator*>(subtract.Get()); };
  }

public:
  QueryableData()
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  explicit QueryableData(TIterable<TObj, TArgs...> items)
    : QueryableData<TObj, TIterable, TArgs...>()
  {
    this->Initialize(items);
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

  void Initialize(TIterable<TObj, TArgs...> items)
  {
    this->items = items;
  }

  virtual TIterable<TObj, TArgs...> GetItems()
  {
    return this->items;
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
    return this->rbeginning;
  }

  Iterator<TObj> rend() override
  {
    this->rendIterator = this->items.rend();
    return this->rending;
  }
};

#endif
