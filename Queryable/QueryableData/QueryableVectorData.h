#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEVECTORDATA_H

#include <iostream>
#include <vector>

#include "QueryableData.h"
#include "../Iterators/Iterator.h"

template<typename T>
class QueryableVectorData : public QueryableData<T, std::vector>
{
private:
  typedef typename std::vector<T>::iterator t_forwardIterator;
  typedef typename std::vector<T>::reverse_iterator t_reverseIterator;

  Iterator<T> beginning;
  Iterator<T> ending;

  Iterator<T> rbeginning;
  Iterator<T> rending;

  t_forwardIterator endIterator;

  t_reverseIterator rbeginIterator;
  t_reverseIterator rendIterator;

  void InitForwardBegin()
  {
    beginning.Get = [&]() { return &this->beginIterator; };
    beginning.Increment = [&]() { this->beginIterator++; };
    beginning.Decrement = [&]() { this->beginIterator--; };
    beginning.Equal = [&](const Iterator<T>& value) { return this->beginIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    beginning.Dereference = [&]() -> T& { return *this->beginIterator; };
    beginning.ConstDereference = [&]() -> const T& { return *this->beginIterator; };
    beginning.Add = [&](int add) { std::advance(this->beginIterator, add); };
    beginning.Subtract = [&](int subtract) { std::advance(this->beginIterator, -subtract); };
    beginning.IterSubtract = [&](const Iterator<T>& subtract) -> int { return this->beginIterator - *static_cast<t_forwardIterator*>(subtract.Get()); };
    beginning.LessThan = [&](const Iterator<T>& value) -> bool { std::cout << (this->beginIterator < *static_cast<t_forwardIterator*>(value.Get())) << std::endl; return this->beginIterator < *static_cast<t_forwardIterator*>(value.Get()); };
    beginning.Assign = [&](const Iterator<T> & value) { this->beginIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
  }

  void InitForwardEnd()
  {
    ending.Get = [&]() { return &this->endIterator; };
    ending.Increment = [&]() { this->endIterator++; };
    ending.Decrement = [&]() { this->endIterator--; };
    ending.Equal = [&](const Iterator<T>& value) { return this->endIterator == *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Dereference = [&]() -> T& { return *this->endIterator; };
    ending.ConstDereference = [&]() -> const T& { return *this->endIterator; };
    ending.Add = [&](int add) { std::advance(this->endIterator, add); };
    ending.Subtract = [&](int subtract) { std::advance(this->endIterator, -subtract); };
    ending.IterSubtract = [&](const Iterator<T>& subtract) -> int { return this->endIterator - *static_cast<t_forwardIterator*>(subtract.Get()); };
    ending.LessThan = [&](const Iterator<T>& value) -> bool { std::cout << (this->endIterator < *static_cast<t_forwardIterator*>(value.Get())) << std::endl; return this->endIterator < *static_cast<t_forwardIterator*>(value.Get()); };
    ending.Assign = [&](const Iterator<T> & value) { this->endIterator = t_forwardIterator(*static_cast<t_forwardIterator*>(value.Get())); };
  }

  void InitReverseBegin()
  {
    rbeginning.Get = [&]() { return &this->rbeginIterator; };
    rbeginning.Increment = [&]() { this->rbeginIterator++; };
    rbeginning.Decrement = [&]() { this->rbeginIterator--; };
    rbeginning.Equal = [&](const Iterator<T>& value) { return this->rbeginIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rbeginning.Dereference = [&]() -> T& { return *this->rbeginIterator; };
    rbeginning.ConstDereference = [&]() -> const T& { return *this->rbeginIterator; };
    rbeginning.Add = [&](int add) { std::advance(this->rbeginIterator, add); };
    rbeginning.Subtract = [&](int subtract) { std::advance(this->rbeginIterator, -subtract); };
    rbeginning.IterSubtract = [&](const Iterator<T>& subtract) -> int { return this->rbeginIterator - *static_cast<t_reverseIterator*>(subtract.Get()); };
    rbeginning.LessThan = [&](const Iterator<T>& value) -> bool { std::cout << (this->rbeginIterator < *static_cast<t_reverseIterator*>(value.Get())) << std::endl; return this->rbeginIterator < *static_cast<t_reverseIterator*>(value.Get()); };
    rbeginning.Assign = [&](const Iterator<T> & value) { this->rbeginIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
  }

  void InitReverseEnd()
  {
    rending.Get = [&]() { return &this->rendIterator; };
    rending.Increment = [&]() { this->rendIterator++; };
    rending.Decrement = [&]() { this->rendIterator--; };
    rending.Equal = [&](const Iterator<T>& value) { return this->rendIterator == *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Dereference = [&]() -> T& { return *this->rendIterator; };
    rending.ConstDereference = [&]() -> const T& { return *this->rendIterator; };
    rending.Add = [&](int add) { std::advance(this->rendIterator, add); };
    rending.Subtract = [&](int subtract) { std::advance(this->rendIterator, -subtract); };
    rending.IterSubtract = [&](const Iterator<T>& subtract) -> int { return this->rendIterator - *static_cast<t_reverseIterator*>(subtract.Get()); };
    rending.LessThan = [&](const Iterator<T>& value) -> bool { return this->rendIterator < *static_cast<t_reverseIterator*>(value.Get()); };
    rending.Assign = [&](const Iterator<T> & value) { this->rendIterator = t_reverseIterator(*static_cast<t_reverseIterator*>(value.Get())); };
  }

public:
  t_forwardIterator beginIterator;
  QueryableVectorData() : QueryableData<T, std::vector>() { }
  QueryableVectorData(std::vector<T> items)
    : QueryableData<T, std::vector>(items)
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
    return this->rbeginning;
  }

  Iterator<T> rend() override
  {
    this->rendIterator = this->items.rend();
    return this->rending;
  }
};

#endif
