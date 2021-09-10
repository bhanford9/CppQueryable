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
  typedef typename TIterable<TObj, TArgs...>::iterator TForwardIterator;
  typedef typename TIterable<TObj, TArgs...>::reverse_iterator TReverseIterator;

  TIterable<TObj, TArgs...> items;

  Iterator<TObj> beginning;
  Iterator<TObj> ending;
  Iterator<TObj> rbeginning;
  Iterator<TObj> rending;

  TForwardIterator beginIterator;
  TForwardIterator endIterator;
  TReverseIterator rbeginIterator;
  TReverseIterator rendIterator;

  // TODO --> consider making this a pointer so data doesn't have to be copied
  TObj value;
  uint64_t size = 0;

  void InitForwardBegin()
  {
    this->beginning.Get = [&]() { return &this->beginIterator; };
    this->beginning.Increment = [&](uint64_t & index) { ++this->beginIterator; };
    this->beginning.Decrement = [&](uint64_t & index) { --this->beginIterator; };
    this->beginning.Dereference = [&]() -> TObj& { this->value = *this->beginIterator; return this->value; };
    this->beginning.ConstDereference = [&]() -> const TObj& { return *this->beginIterator; };
    this->beginning.Assign = [&](const Iterator<TObj> & value) { this->beginIterator = TForwardIterator(*static_cast<TForwardIterator*>(value.Get())); };
  }

  void InitForwardEnd()
  {
    this->ending.Get = [&]() { return &this->endIterator; };
    this->ending.Increment = [&](uint64_t & index) { ++this->endIterator; };
    this->ending.Decrement = [&](uint64_t & index) { --this->endIterator;};
    this->ending.Dereference = [&]() -> TObj& { this->value = *this->endIterator; return this->value; };
    this->ending.ConstDereference = [&]() -> const TObj& { return *this->endIterator; };
    this->ending.Assign = [&](const Iterator<TObj> & value) { this->endIterator = TForwardIterator(*static_cast<TForwardIterator*>(value.Get())); };
  }

  void InitReverseBegin()
  {
    this->rbeginning.Get = [&]() { return &this->rbeginIterator; };
    this->rbeginning.Increment = [&](uint64_t & index) { ++this->rbeginIterator; };
    this->rbeginning.Decrement = [&](uint64_t & index) { --this->rbeginIterator; };
    this->rbeginning.Dereference = [&]() -> TObj& { this->value = *this->rbeginIterator; return this->value; };
    this->rbeginning.ConstDereference = [&]() -> const TObj& { return *this->rbeginIterator; };
    this->rbeginning.Assign = [&](const Iterator<TObj> & value) { this->rbeginIterator = TReverseIterator(*static_cast<TReverseIterator*>(value.Get())); };
  }

  void InitReverseEnd()
  {
    this->rending.Get = [&]() { return &this->rendIterator; };
    this->rending.Increment = [&](uint64_t & index) { ++this->rendIterator; };
    this->rending.Decrement = [&](uint64_t & index) { --this->rendIterator; };
    this->rending.Dereference = [&]() -> TObj& { this->value = *this->rendIterator; return this->value; };
    this->rending.ConstDereference = [&]() -> const TObj& { return *this->rendIterator; };
    this->rending.Assign = [&](const Iterator<TObj> & value) { this->rendIterator = TReverseIterator(*static_cast<TReverseIterator*>(value.Get())); };
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
    this->items = items;

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(const QueryableData<TObj, TIterable> & data)
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
    this->size = data.size;
  }
  virtual ~QueryableData() { }

  // void AddCondition(std::function<bool(const TObj &)> condition) override
  // {
  //   this->condition += condition;
  // }
  //
  // bool PassesCondition(const TObj & obj) const override
  // {
  //   return this->condition(obj);
  // }

  virtual int Count() override
  {
    return this->size;
  }

  int StorageSize() override
  {
    return this->size;
  }

  virtual void Clear() override
  {
    this->items.clear();
    this->size = 0;
  }

  virtual std::vector<TObj> ToVector() override
  {
    std::vector<TObj> objs;

    for (TObj item : this->items)
    {
      objs.push_back(item);
    }

    return objs;
  }

  virtual Iterator<TObj> begin() override
  {
    this->beginIterator = this->items.begin();
    this->beginning.SetIndex(0);
    return this->beginning;
  }

  virtual Iterator<TObj> end() override
  {
    this->endIterator = this->items.end();
    this->ending.SetIndex(this->size);
    return this->ending;
  }

  virtual Iterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->rbeginning.SetIndex(0);
    return this->rbeginning;
  }

  virtual Iterator<TObj> rend() override
  {
    this->rendIterator = this->items.rend();
    this->rending.SetIndex(this->size);
    return this->rending;
  }
};

#endif
