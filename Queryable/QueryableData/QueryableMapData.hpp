#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMAPDATA_H

#include <iostream>
#include <memory>
#include <map>

#include "QueryableData.hpp"

template<
  typename TKey,
  typename T,
  typename TCompare = std::less<T>,
  typename TAllocator = std::allocator<T>>
class QueryableMapData : public QueryableData<TKey, std::map, T, TCompare, TAllocator>
{
  typedef typename std::vector<std::pair<TKey, T>>::iterator TVectorIterator;
public:
  QueryableMapData(TCompare comparator = {})
    : QueryableData<TKey, std::map, T, TCompare, TAllocator>()
    {
      std::cout << "queryable map data default constructor" << std::endl;
    }

  QueryableMapData(const std::map<TKey, T, TCompare, TAllocator> & items)
    : QueryableData<TKey, std::map, T, TCompare, TAllocator>(items)
    {
    }

  QueryableMapData(std::map<TKey, T, TCompare, TAllocator> && items)
    : QueryableData<TKey, std::map, T, TCompare, TAllocator>(std::move(items))
    {
    }

  QueryableMapData(const QueryableMapData<T, TCompare, TAllocator> & data)
    : QueryableData<TKey, std::map, T, TCompare, TAllocator>(data) { }

  QueryableMapData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
    : QueryableData<TKey, std::map, T, TCompare, TAllocator>(first, last, comparator) { }

  virtual ~QueryableMapData() { }

  virtual std::shared_ptr<IQueryableData<TKey>> Clone() override
  {
    return std::make_shared<QueryableMapData<TKey, T, TCompare, TAllocator>>(*this);
  }

  void Add(TKey item) override
  {
    // this add method wont work
    // this->items->insert(item);

    // because its a map, the tiem may not have actually been added. Insert
    // returns true/false whether the item was added, but the size method is
    // also a constant time action, so its cleaner to use it
    // this->size = this->items->size();
  }

  virtual TKey & Get(IteratorType type) override
  {
      // std::cout << "Get" << std::endl;
    switch (type)
    {
      case IteratorType::BeginForward: { this->value = this->beginIterator->first; return this->value; }
      case IteratorType::EndForward: { this->value = this->endIterator->first; return this->value; }
      // case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
      // case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
    }

    return this->value;
    // std::cout << "Get: " << this->value << std::endl;
  }

  virtual const TKey & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: { this->value = this->beginIterator->first; return this->value; }
      case IteratorType::EndForward: { this->value = this->endIterator->first; return this->value; }
      // case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
      // case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
    }

    return this->value;
  }
};

#endif
