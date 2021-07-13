#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMULTISETDATA_H

#include <iostream>
#include <memory>
#include <set>

#include "QueryableData.h"
#include "../Iterators/Iterator.h"

template<typename T>
class QueryableMultiSetData : public QueryableData<T, std::multiset>
{
private:
  typedef typename std::multiset<T>::iterator t_forwardIterator;
  typedef typename std::multiset<T>::reverse_iterator t_reverseIterator;

  Iterator<T> beginning;
  Iterator<T> ending;

  Iterator<T> rbeginning;
  Iterator<T> rending;

  mutable t_forwardIterator beginIterator;
  mutable t_forwardIterator endIterator;

  mutable t_reverseIterator rbeginIterator;
  mutable t_reverseIterator rendIterator;

  T value;

  void InitForwardBegin()
  {
    beginning.Get = [&]() { return &this->beginIterator; };
    beginning.Increment = [&]() { this->beginIterator++; };
    beginning.Add = [&](int add) { std::advance(this->beginIterator, add); };
    beginning.Subtract = [&](int subtract) { std::advance(this->beginIterator, -subtract); };
    beginning.Decrement = [&]() { this->beginIterator--; };
    beginning.Equal = [&](const Iterator<T>& value) { return this->beginIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    beginning.Dereference = [&]() -> T& { this->value = *this->beginIterator; return value; };
    beginning.ConstDereference = [&]() -> const T& { return *this->beginIterator; };
  }

  void InitForwardEnd()
  {
    ending.Get = [&]() { return &this->endIterator; };
    ending.Increment = [&]() { this->endIterator++; };
    ending.Decrement = [&]() { this->endIterator--; };
    ending.Equal = [&](const Iterator<T>& value) { return this->endIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Dereference = [&]() -> T& { this->value = *this->endIterator; return value; };
    ending.ConstDereference = [&]() -> const T& { return *this->endIterator; };
  }

  void InitReverseBegin()
  {
    rbeginning.Get = [&]() { return &this->rbeginIterator; };
    rbeginning.Increment = [&]() { this->rbeginIterator++; };
    rbeginning.Decrement = [&]() { this->rbeginIterator--; };
    rbeginning.Equal = [&](const Iterator<T>& value) { return this->rbeginIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rbeginning.Dereference = [&]() -> T& { this->value = *this->rbeginIterator; return value; };
    rbeginning.ConstDereference = [&]() -> const T& { return *this->rbeginIterator; };
  }

  void InitReverseEnd()
  {
    rending.Get = [&]() { return &this->rendIterator; };
    rending.Increment = [&]() { this->rendIterator++; };
    rending.Decrement = [&]() { this->rendIterator--; };
    rending.Equal = [&](const Iterator<T>& value) { return this->rendIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Dereference = [&]() -> T& { this->value = *this->rendIterator; return value; };
    rending.ConstDereference = [&]() -> const T& { return *this->rendIterator; };
  }

public:
  QueryableMultiSetData() : QueryableData<T, std::multiset>() { }
  QueryableMultiSetData(std::multiset<T> items)
    : QueryableData<T, std::multiset>(items)
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }

  void Add(T item) override
  {
    this->items.insert(item);
  }

  int Count() override
  {
    return this->items.size();
  }

  void RemoveLast() override
  {
    if (this->Count() > 0)
    {
      this->items.erase(--this->items.end());
    }
  }

  void RemoveFirst() override
  {

  }

  Iterator<T> begin() override
  {
    this->beginIterator = this->items.begin();
    return this->beginning;
  }

  Iterator<T> end() override
  {
    this->endIterator = this->items.end();
    return this->ending;
  }

  Iterator<T> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    return this->rbeginning;
  }

  Iterator<T> rend() override
  {
    this->rendIterator = this->items.rend();
    return this->rending;
  }
};

#endif
