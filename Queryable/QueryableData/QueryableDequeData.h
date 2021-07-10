#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDEQUEDATA_H

#include <deque>
#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T>
class QueryableDequeData : public QueryableData<T, std::deque>
{
private:
  typedef typename std::deque<T>::iterator t_forwardIterator;
  typedef typename std::deque<T>::reverse_iterator t_reverseIterator;

  Iterator<T> beginning;
  Iterator<T> ending;

  Iterator<T> rbeggining;
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
    rbeggining.Get = [&]() { return &this->rbeginIterator; };
    rbeggining.Increment = [&]() { this->rbeginIterator++; };
    rbeggining.Decrement = [&]() { this->rbeginIterator--; };
    rbeggining.Equal = [&](const Iterator<T>& value) { return this->rbeginIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rbeggining.Dereference = [&]() -> T& { this->value = *this->rbeginIterator; return value; };
    rbeggining.ConstDereference = [&]() -> const T& { return *this->rbeginIterator; };
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
  QueryableDequeData() : QueryableData<T, std::deque>() { }
  QueryableDequeData(std::deque<T> items)
    : QueryableData<T, std::deque>(items)
  {
    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }

  void Add(T item) override
  {
    this->items.push_back(item);
  }

  int Count() override
  {
    return this->items.size();
  }

  void RemoveLast() override
  {
    this->items.pop_back();
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
    return this->rbeggining;
  }

  Iterator<T> rend() override
  {
    this->rendIterator = this->items.rend();
    return this->rending;
  }
};

#endif
