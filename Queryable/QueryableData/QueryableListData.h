#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLELISTDATA_H

#include <iostream>
#include <list>

#include "QueryableData.h"
#include "../Iterators/Iterator.h"

template<typename T>
class QueryableListData : public QueryableData<T, std::list>
{
private:
  typedef typename std::list<T>::iterator t_forwardIterator;
  typedef typename std::list<T>::reverse_iterator t_reverseIterator;

  Iterator<T> beggining;
  Iterator<T> ending;

  Iterator<T> rbeggining;
  Iterator<T> rending;

  t_forwardIterator beginIterator;
  t_forwardIterator endIterator;

  t_reverseIterator rbeginIterator;
  t_reverseIterator rendIterator;

  void InitForwardBegin()
  {
    beggining.Get = [&]() { return &this->beginIterator; };
    beggining.Increment = [&]() { this->beginIterator++; };
    beggining.Decrement = [&]() { this->beginIterator--; };
    beggining.Equal = [&](const Iterator<T>& value) { return this->beginIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    beggining.Dereference = [&]() -> T& { return *this->beginIterator; };
    beggining.ConstDereference = [&]() -> const T& { return *this->beginIterator; };
  }

  void InitForwardEnd()
  {
    ending.Get = [&]() { return &this->endIterator; };
    ending.Increment = [&]() { this->endIterator++; };
    ending.Decrement = [&]() { this->endIterator--; };
    ending.Equal = [&](const Iterator<T>& value) { return this->endIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Dereference = [&]() -> T& { return *this->endIterator; };
    ending.ConstDereference = [&]() -> const T& { return *this->endIterator; };
  }

  void InitReverseBegin()
  {
    rbeggining.Get = [&]() { return &this->rbeginIterator; };
    rbeggining.Increment = [&]() { this->rbeginIterator++; };
    rbeggining.Decrement = [&]() { this->rbeginIterator--; };
    rbeggining.Equal = [&](const Iterator<T>& value) { return this->rbeginIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rbeggining.Dereference = [&]() -> T& { return *this->rbeginIterator; };
    rbeggining.ConstDereference = [&]() -> const T& { return *this->rbeginIterator; };
  }

  void InitReverseEnd()
  {
    rending.Get = [&]() { return &this->rendIterator; };
    rending.Increment = [&]() { this->rendIterator++; };
    rending.Decrement = [&]() { this->rendIterator--; };
    rending.Equal = [&](const Iterator<T>& value) { return this->rendIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Dereference = [&]() -> T& { return *this->rendIterator; };
    rending.ConstDereference = [&]() -> const T& { return *this->rendIterator; };
  }

public:
  QueryableListData() : QueryableData<T, std::list>() { }
  QueryableListData(std::list<T> items)
    : QueryableData<T, std::list>(items)
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
    return this->beggining;
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
