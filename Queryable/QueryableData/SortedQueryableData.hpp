#ifndef CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SORTEDQUERYABLEDATA_H

#include <iostream>
#include <memory>

#include "QueryableData.hpp"

template<
  typename T,
  template<typename, typename ...> typename TIterable,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>,
  typename ...TArgs>
  // may want to consider making the iterating type const T
class SortedQueryableData : public QueryableData<T, TIterable, T, TCompare, TAllocator, TArgs...>
{
  typedef typename std::vector<T>::iterator TVectorIterator;
public:
  SortedQueryableData(TCompare comparator = {})
    : QueryableData<T, TIterable, T, TCompare, TAllocator, TArgs...>()
  {
    std::cout << "BAD: SortedQueryableData default constructor" << std::endl;
    this->items = TIterable<T, TCompare, TAllocator, TArgs...>(comparator);
  }

  SortedQueryableData(const TIterable<T, TCompare, TAllocator, TArgs...> & items)
    : QueryableData<T, TIterable, T, TCompare, TAllocator, TArgs...>(items)
  {
  }

  SortedQueryableData(TIterable<T, TCompare, TAllocator, TArgs...> && items)
    : QueryableData<T, TIterable, T, TCompare, TAllocator, TArgs...>(std::move(items))
  {
  }

  SortedQueryableData(const SortedQueryableData<T, TIterable, TCompare, TAllocator, TArgs...> & data)
    : QueryableData<T, TIterable, T, TCompare, TAllocator, TArgs...>(data)
  {
  }

  SortedQueryableData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
  {
    // TODO SFINAE require this constructor
    this->items = std::make_shared<TIterable<T, TCompare, TAllocator, TArgs...>>(first, last, comparator);
    this->size = this->items->size();
  }

  virtual ~SortedQueryableData() { }

  virtual T & Get(IteratorType type) override
  {
      // std::cout << "Sorted Get" << std::endl;
      // std::cout << "begin iterator: " << *this->beginIterator << std::endl;
    switch (type)
    {
      // case IteratorType::BeginForward: { return const_cast<T&>(*this->beginIterator); }
      // case IteratorType::EndForward: { return const_cast<T&>(*this->endIterator); }
      // case IteratorType::BeginReverse: { return const_cast<T&>(*this->rbeginIterator); }
      // case IteratorType::EndReverse: default: { return const_cast<T&>(*this->rendIterator); }
      // case IteratorType::BeginForward: { this->value = const_cast<T*>(&(*this->beginIterator)); return *this->value; }
      // case IteratorType::EndForward: { this->value = const_cast<T*>(&(*this->endIterator)); return *this->value; }
      // case IteratorType::BeginReverse: { this->value = const_cast<T*>(&(*this->rbeginIterator)); return *this->value; }
      // case IteratorType::EndReverse: default: { this->value = const_cast<T*>(&(*this->rendIterator)); return *this->value; }
      case IteratorType::BeginForward: { this->value = *this->beginIterator; return this->value; }
      case IteratorType::EndForward: { this->value = *this->endIterator; return this->value; }
      case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
      case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
      // case IteratorType::BeginForward:
      // { 
      //   auto temp = *this->beginIterator;
      //   *this->value = temp;
      //   return *this->value;
      //   // *this->value = *this->beginIterator; return *this->value;
      // }
      // case IteratorType::EndForward:
      // {
      //   auto temp = *this->endIterator;
      //   *this->value = temp;
      //   return *this->value;
      // }
      // case IteratorType::BeginReverse: { *this->value = *this->rbeginIterator; return *this->value; }
      // case IteratorType::EndReverse: default: { *this->value = *this->rendIterator; return *this->value; }
    }

    return this->value;
    // std::cout << "Get: " << *this->value << std::endl;
  }

  virtual const T & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      // case IteratorType::BeginForward: { return *this->beginIterator; }
      // case IteratorType::EndForward: { return *this->endIterator; }
      // case IteratorType::BeginReverse: { return *this->rbeginIterator; }
      // case IteratorType::EndReverse: default: { return *this->rendIterator; }
      // case IteratorType::BeginForward: { this->value = &(*this->beginIterator); return *this->value; }
      // case IteratorType::EndForward: { this->value = &(*this->endIterator); return *this->value; }
      // case IteratorType::BeginReverse: { this->value = &(*this->rbeginIterator); return *this->value; }
      // case IteratorType::EndReverse: default: { this->value = &(*this->rendIterator); return *this->value; }
      case IteratorType::BeginForward: { this->value = *this->beginIterator; return this->value; }
      case IteratorType::EndForward: { this->value = *this->endIterator; return this->value; }
      case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
      case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
    }

    return this->value;
  }
};

#endif
