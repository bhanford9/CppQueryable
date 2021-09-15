#ifndef CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_RANDOMACCESSQUERYABLEDATA_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T, template<typename, typename ...> typename TIterable, typename ...TArgs>
class RandomAccessQueryableData : public QueryableData<T, TIterable, TArgs...>
{
private:
  void InitRandomAccessProperties()
  {
    this->beginning.Add = [&](int addend, int64_t & index) { this->beginIterator += addend; index += addend; };
    this->beginning.Subtract = [&](int subtrahend, int64_t & index) { this->beginIterator -= subtrahend; index -= subtrahend; };

    this->ending.Add = [&](int addend, int64_t & index) { this->endIterator += addend; index += addend; };
    this->ending.Subtract = [&](int subtrahend, int64_t & index) { this->endIterator -= subtrahend; index -= subtrahend; };

    this->rbeginning.Add = [&](int addend, int64_t & index) { this->rbeginIterator += addend; index += addend; };
    this->rbeginning.Subtract = [&](int subtrahend, int64_t & index) { this->rbeginIterator -= subtrahend; index -= subtrahend; };

    this->rending.Add = [&](int addend, int64_t & index) { this->rendIterator += addend; index += addend; };
    this->rending.Subtract = [&](int subtrahend, int64_t & index) { this->rendIterator -= subtrahend; index -= subtrahend; };
  }

public:
  RandomAccessQueryableData() : QueryableData<T, TIterable, TArgs...>()
  {
    this->InitRandomAccessProperties();
  }
  RandomAccessQueryableData(TIterable<T, TArgs...> items)
    : QueryableData<T, TIterable, TArgs...>(items)
  {
    this->InitRandomAccessProperties();
  }
  RandomAccessQueryableData(const RandomAccessQueryableData& data)
    : QueryableData<T, TIterable, TArgs...>(data)
  {
    this->InitRandomAccessProperties();
  }
  RandomAccessQueryableData(RandomAccessQueryableData && data)
    : QueryableData<T, TIterable, TArgs...>(data)
  {
  }

  virtual ~RandomAccessQueryableData() { }

  void Add(T item) override
  {
    this->items.push_back(item);
    this->size++;
  }

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    // todo figure out how to get this to work with this->begin instead o this->items.begin()
    std::sort(this->items.begin(), this->items.end(), compare);
  }
};

#endif
