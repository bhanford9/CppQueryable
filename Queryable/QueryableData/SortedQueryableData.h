#ifndef CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H

#include <iostream>
#include <memory>

#include "QueryableData.h"

template<typename T, template<typename, typename ...> typename TIterable, typename ...TArgs>
class SortedQueryableData : public QueryableData<T, TIterable, std::function<bool(T, T), TArgs...>>
{
protected:
  std::function<bool(T, T)> comparator;

  typedef typename std::vector<T>::iterator TVectorIterator;
  typedef typename TIterable<T, std::function<bool(T, T)>>::iterator t_forwardIterator;
public:
  SortedQueryableData(std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
    : QueryableData<T, TIterable, std::function<bool(T, T)>>()
  {
    this->comparator = compare;
    this->items = TIterable<T, std::function<bool(T, T)>>(compare);

    this->InitForwardBegin();
    this->InitForwardEnd();
    this->InitReverseBegin();
    this->InitReverseEnd();
  }
  SortedQueryableData(TIterable<T, std::function<bool(T, T)>> items)
    : QueryableData<T, TIterable, std::function<bool(T, T)>>(items)
  {
  }
  SortedQueryableData(const SortedQueryableData& data)
    : QueryableData<T, TIterable, std::function<bool(T, T)>>(data)
  {
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
    this->comparator = compare;
    this->items = TIterable<T, std::function<bool(T, T)>>(first, last, compare);
    this->size = this->items.size();
  }

  virtual void Update(TVectorIterator first, TVectorIterator last)
  {
    // TODO SFINAE require this constructor
    this->items = TIterable<T, std::function<bool(T, T)>>(first, last, this->comparator);
    this->size = this->items.size();
  }
};

#endif
