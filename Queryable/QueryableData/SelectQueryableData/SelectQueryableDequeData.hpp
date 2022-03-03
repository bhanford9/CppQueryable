#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDEQUEDATA_H

#include <iostream>
#include <deque>

#include "SelectQueryableData.hpp"

template<
  typename TOriginal,
  typename TCurrent,
  typename TCompare = std::less<TCurrent>,
  typename TAllocator = std::less<TOriginal>>
class SelectQueryableDequeData : public SelectQueryableData<TOriginal, TCurrent, std::deque, TCompare, TAllocator>
{
public:
  SelectQueryableDequeData(
    std::shared_ptr<IQueryableData<TOriginal, TOriginal>> data,
    std::function<TCurrent(TOriginal)> selector)
    : SelectQueryableData<TOriginal, TCurrent, std::deque, TCompare, TAllocator>(std::move(data), selector)
  {
    this->InitRandomAccessProperties();
  }

  virtual ~SelectQueryableDequeData() { }

  inline virtual QueryableIterator<TCurrent> & operator+(int addend) override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TCurrent> & operator+=(int addend) override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TCurrent> & operator-(int subtrahend) override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TCurrent> & operator-=(int subtrahend) override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return this->AsReferenceIterator();
  }


  void Add(TCurrent item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items.push_back(item);
    this->size++;
  }
};

#endif
