#ifndef CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H

#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T, template<typename, typename ...> typename TIterable, typename ...TArgs>
class SortedQueryableData : public QueryableData<T, TIterable, std::function<bool(T, T)>, TArgs...>
{
protected:
  std::function<bool(T, T)> comparator;// = [](T a, T b) { return a < b; };

  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  SortedQueryableData(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : QueryableData<T, TIterable, std::function<bool(T, T)>>()
  {
    this->comparator = compare;
    this->items = TIterable<T, std::function<bool(T, T)>>(compare);
  }

  SortedQueryableData(
    TIterable<T, std::function<bool(T, T)>> items,
    std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : QueryableData<T, TIterable, std::function<bool(T, T)>>(items)
  {
    this->comparator = compare;
  }

  SortedQueryableData(const SortedQueryableData<T, TIterable, TArgs...> & data)
    : QueryableData<T, TIterable, std::function<bool(T, T)>>(data)
  {
    this->comparator = data.comparator;
  }

  SortedQueryableData(
    TVectorIterator first,
    TVectorIterator last,
    std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
  {
    // TODO SFINAE require this constructor
    this->comparator = compare;
    this->items = TIterable<T, std::function<bool(T, T)>>(first, last, this->comparator);
    this->size = this->items.size();
  }

  virtual ~SortedQueryableData() { }

  void Sort(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) override
  {
    this->Update(this->begin(), this->end(), compare);
  }

  virtual void Update(Iterator<T> first, Iterator<T> last, std::function<bool(T, T)> compare) override
  {
    // TODO SFINAE require this constructor
    this->comparator = compare;
    this->items = TIterable<T, std::function<bool(T, T)>>(first, last, compare);
    this->size = this->items.size();
  }

  virtual void Update(TVectorIterator first, TVectorIterator last) override
  {
    // TODO SFINAE require this constructor
    this->items = TIterable<T, std::function<bool(T, T)>>(first, last, this->comparator);
    this->size = this->items.size();
  }
};

#endif
