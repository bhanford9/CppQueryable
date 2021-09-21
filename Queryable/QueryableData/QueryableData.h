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

#include "../../DataStructures/Person.h"

template<typename TObj, template<typename, typename ...> typename TIterable, typename ...TArgs>
class QueryableData : virtual public IQueryableData<TObj>
{
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  typedef typename std::vector<TObj>::iterator TVectorIterator;
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
  int64_t size = 0;

  void InitForwardBegin()
  {
    this->beginning.Get = [&]() { return &this->beginIterator; };
    this->beginning.Increment = [&](int64_t & index) { if (index <= this->size) ++this->beginIterator; };
    this->beginning.Decrement = [&](int64_t & index) { if (index > 0) --this->beginIterator; };
    this->beginning.Dereference = [&]() -> TObj& { this->value = *this->beginIterator; return this->value; };
    this->beginning.ConstDereference = [&]() -> const TObj& { return *this->beginIterator; };
    this->beginning.Assign = [&](const Iterator<TObj> & value) { this->beginIterator = TForwardIterator(*static_cast<TForwardIterator*>(value.Get())); };

    // this is the worst way to do this and should be avoided
    // add and subtract needed to support the random access iterators
    this->beginning.Add = [&](int addend, int64_t & index) { while (addend-- > 0) ++this->beginning; };
    this->beginning.Subtract = [&](int subtrahend, int64_t & index) { while (subtrahend-- > 0) --this->beginning; };
  }

  void InitForwardEnd()
  {
    this->ending.Get = [&]() { return &this->endIterator; };
    this->ending.Increment = [&](int64_t & index) { if (index <= this->size) ++this->endIterator; };
    this->ending.Decrement = [&](int64_t & index) { if (index > 0) --this->endIterator;};
    this->ending.Dereference = [&]() -> TObj& { this->value = *this->endIterator; return this->value; };
    this->ending.ConstDereference = [&]() -> const TObj& { return *this->endIterator; };
    this->ending.Assign = [&](const Iterator<TObj> & value) { this->endIterator = TForwardIterator(*static_cast<TForwardIterator*>(value.Get())); };

    // this is the worst way to do this and should be avoided
    // add needed to support the random access iterators
    this->ending.Add = [&](int addend, int64_t & index) { while (addend-- > 0) ++this->ending; };
    this->ending.Subtract = [&](int subtrahend, int64_t & index) { while (subtrahend-- > 0) --this->ending; };
  }

  void InitReverseBegin()
  {
    this->rbeginning.Get = [&]() { return &this->rbeginIterator; };
    this->rbeginning.Increment = [&](int64_t & index) { if (index <= this->size) ++this->rbeginIterator; };
    this->rbeginning.Decrement = [&](int64_t & index) { if (index > 0) --this->rbeginIterator; };
    this->rbeginning.Dereference = [&]() -> TObj& { this->value = *this->rbeginIterator; return this->value; };
    this->rbeginning.ConstDereference = [&]() -> const TObj& { return *this->rbeginIterator; };
    this->rbeginning.Assign = [&](const Iterator<TObj> & value) { this->rbeginIterator = TReverseIterator(*static_cast<TReverseIterator*>(value.Get())); };

    // this is the worst way to do this and should be avoided
    // add needed to support the random access iterators
    this->rbeginning.Add = [&](int addend, int64_t & index) { while (addend-- > 0) ++this->rbeginning; };
    this->rbeginning.Subtract = [&](int subtrahend, int64_t & index) { while (subtrahend-- > 0) --this->rbeginning; };
  }

  void InitReverseEnd()
  {
    this->rending.Get = [&]() { return &this->rendIterator; };
    this->rending.Increment = [&](int64_t & index) { if (index <= this->size) ++this->rendIterator; };
    this->rending.Decrement = [&](int64_t & index) { if (index > 0) --this->rendIterator; };
    this->rending.Dereference = [&]() -> TObj& { this->value = *this->rendIterator; return this->value; };
    this->rending.ConstDereference = [&]() -> const TObj& { return *this->rendIterator; };
    this->rending.Assign = [&](const Iterator<TObj> & value) { this->rendIterator = TReverseIterator(*static_cast<TReverseIterator*>(value.Get())); };

    // this is the worst way to do this and should be avoided
    // add needed to support the random access iterators
    this->rending.Add = [&](int addend, int64_t & index) { while (addend-- > 0) ++this->rending; };
    this->rending.Subtract = [&](int subtrahend, int64_t & index) { while (subtrahend-- > 0) --this->rending; };
  }

public:

  QueryableData()
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();

    beginIterator = this->items.begin();
    endIterator = this->items.end();
    rbeginIterator = this->items.rbegin();
    rendIterator = this->items.rend();

    this->size = 0;
  }
  QueryableData(TIterable<TObj, TArgs...> items)
    : QueryableData<TObj, TIterable, TArgs...>()
  {
    this->items = items;

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(TIterable<TObj, TArgs...> && items)
    : QueryableData<TObj, TIterable, TArgs...>()
  {
    this->items = std::move(items);

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(TVectorIterator first, TVectorIterator last)
  {
    // TODO SFINAE require this constructor
    this->items = TIterable<TObj, TArgs...>(first, last);
    this->size = this->items.size();
  }
  QueryableData(const QueryableData<TObj, TIterable> & data)
    : QueryableData<TObj, TIterable>()
  {
    this->items = data.items;
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

  virtual void Update(
    Iterator<TObj> first,
    Iterator<TObj> last,
    std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) override
  {
    // TODO SFINAE require this constructor
    this->items = TIterable<TObj, TArgs...>(first, last);
    this->size = this->items.size();
  }

  virtual void Update(TVectorIterator first, TVectorIterator last) override
  {
    // TODO SFINAE require this constructor
    this->items = TIterable<TObj, TArgs...>(first, last);
    this->size = this->items.size();
  }

  virtual Iterator<TObj> begin() override
  {
    this->beginIterator = this->items.begin();
    this->beginning.Index = 0;
    return this->beginning;
  }

  virtual Iterator<TObj> end() override
  {
    this->endIterator = this->items.end();
    this->ending.Index = this->size;
    return this->ending;
  }

  virtual Iterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->rbeginning.Index = 0;
    return this->rbeginning;
  }

  virtual Iterator<TObj> rend() override
  {
    this->rendIterator = this->items.rend();
    this->rending.Index = this->size;
    return this->rending;
  }
};

#endif
