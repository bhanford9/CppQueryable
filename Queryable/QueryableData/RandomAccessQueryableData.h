#ifndef CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T, template<typename, typename ...> typename TIterable, typename ...TArgs>
class RandomAccessQueryableData : public QueryableData<T, T, TIterable, TArgs...>
{
public:
  RandomAccessQueryableData() : QueryableData<T, T, TIterable, TArgs...>()
  {
  }
  RandomAccessQueryableData(TIterable<T, TArgs...> items)
    : QueryableData<T, T, TIterable, TArgs...>(items)
  {
  }
  RandomAccessQueryableData(const RandomAccessQueryableData& data)
    : QueryableData<T, T, TIterable, TArgs...>(data)
  {
  }
  RandomAccessQueryableData(RandomAccessQueryableData && data)
    : QueryableData<T, T, TIterable, TArgs...>(data)
  {
  }

  virtual ~RandomAccessQueryableData() { }

  inline virtual IQueryableIteratorData<T> & Add(int addend, IteratorType type) override
  {
    std::cout << "Random Access + Operator" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator += addend; break;
      case IteratorType::EndForward: this->endIterator += addend; break;
      case IteratorType::BeginReverse: this->rbeginIterator += addend; break;
      case IteratorType::EndReverse: this->rendIterator += addend; break;
    }

    return *this;
  }

  inline virtual IQueryableIteratorData<T> & Subtract(int subtrahend, IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: this->beginIterator -= subtrahend; break;
      case IteratorType::EndForward: this->endIterator -= subtrahend; break;
      case IteratorType::BeginReverse: this->rbeginIterator -= subtrahend; break;
      case IteratorType::EndReverse: this->rendIterator -= subtrahend; break;
    }

    return *this;
  }

  void Add(T item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    std::sort(this->items.begin(), this->items.end(), compare);
  }
};

#endif
