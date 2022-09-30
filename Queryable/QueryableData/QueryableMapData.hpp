#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEMAPDATA_H

#include <iostream>
#include <memory>
#include <map>

#include "QueryableData.hpp"

template<
  typename TKey,
  typename T,
  typename TCompare = std::less<TKey>,
  typename TAllocator = std::allocator<std::pair<const TKey, T>>>
class QueryableMapData : public QueryableData<std::pair<const TKey, T>, std::map, TCompare, TAllocator>
{
  // This whole class is overriding all parent implementations because of the weird typing infrastructure
  //   1. We want to iterate over the collection as std::pair<TKey, TValue>
  //   2. We want to suppy both a key and a value to the add method
  //   3. The inheritance assumes the first templated type is the thing within the collection
  //   4. Alternate option would be to template as <TKey, std::map, TValue, TCompare, TAllocator>
  //      4.1 The inheritance would pick this up correctly for std::map
  //      4.2 The inherited extra methods would expect TKey to be the only value within the collection
  //   5. Alternate option would be to further template into something like <TValue, TIterable, TIterating, ...TArgs>
  //      5.1 The TIterating would be a specialized type that would indicate the type returned by the iterator
  //      5.2 It would probably suffice for it to also indicate the type to be supplied when adding to the collection
  //      5.3 This would be a new required parameter in front of the variable template arguments, so it would change every child template inheritance
  //      5.4 I think this would be the best impl, but I want to see if I can get it into a stable state without changing everything first

  typedef typename std::vector<std::pair<const TKey, T>>::iterator TVectorIterator;
protected:
  std::pair<const TKey, T> mapValue;
  std::shared_ptr<std::map<TKey, T, TCompare, TAllocator>> mapItems;
  
  using TForwardIterator = typename std::map<TKey, T, TCompare, TAllocator>::iterator;
  using TReverseIterator = typename std::map<TKey, T, TCompare, TAllocator>::reverse_iterator;
  TForwardIterator mapBeginIterator;
  TForwardIterator mapEndIterator;
  TReverseIterator mapRBeginIterator;
  TReverseIterator mapREndIterator;

public:
  QueryableMapData(TCompare comparator = {}, TAllocator allocator = {})
    : QueryableData<std::pair<const TKey, T>, std::map, TCompare, TAllocator>()
    {
      this->mapItems = std::make_shared<std::map<TKey, T, TCompare, TAllocator>>(comparator, allocator);
      this->DefaultInitialize();
    }

  QueryableMapData(const std::map<TKey, T, TCompare, TAllocator> & items)
  {
    this->mapItems = std::make_shared<std::map<TKey, T, TCompare, TAllocator>>(items);
    this->DefaultInitialize();
    this->size = mapItems->size();
  }

  QueryableMapData(std::map<TKey, T, TCompare, TAllocator> && items)
  {
    this->mapItems = std::make_shared<std::map<TKey, T, TCompare, TAllocator>>(items);
    this->DefaultInitialize();
    this->size = mapItems->size();
  }

  QueryableMapData(const QueryableMapData<TKey, T, TCompare, TAllocator> & data)
  {
    this->size = data.size;
    this->mapItems = data.mapItems;
    this->mapBeginIterator = data.mapBeginIterator;
    this->mapRBeginIterator = data.mapRBeginIterator;
    this->mapEndIterator = data.mapEndIterator;
    this->mapREndIterator = data.mapREndIterator;
  }

  QueryableMapData(
    TVectorIterator first,
    TVectorIterator last,
    TCompare comparator = {})
    : QueryableData<std::pair<const TKey, T>, std::map, TCompare, TAllocator>(first, last, comparator) { }

  virtual ~QueryableMapData() { }

  virtual std::shared_ptr<IQueryableData<std::pair<const TKey, T>>> Clone() override
  {
    return std::make_shared<QueryableMapData<TKey, T, TCompare, TAllocator>>(*this);
  }  

  void DefaultInitialize()
  {
    this->mapBeginIterator = this->mapItems->begin();
    this->mapEndIterator = this->mapItems->end();
    this->mapRBeginIterator = this->mapItems->rbegin();
    this->mapREndIterator = this->mapItems->rend();
    this->size = 0;
  }

  void Add(std::pair<const TKey, T> item) override
  {
    (*this->mapItems)[item.first] = item.second;

    // because its a map, the item may not have actually been added. Insert
    // returns true/false whether the item was added, but the size method is
    // also a constant time action, so its cleaner to use it
    this->size = this->mapItems->size();
  }

  virtual std::pair<const TKey, T> & Get(IteratorType type) override
  {
      // std::cout << "Map Get" << std::endl;
    switch (type)
    {
    //   case IteratorType::BeginForward: { this->mapValue = *this->mapBeginIterator; return this->mapValue; }
    //   case IteratorType::EndForward: { this->mapValue = *this->mapEndIterator; return this->mapValue; }
    //   case IteratorType::BeginReverse: { this->mapValue = *this->mapRBeginIterator; return this->mapValue; }
    //   case IteratorType::EndReverse: default: { this->mapValue = *this->mapREndIterator; return this->mapValue; }
      case IteratorType::BeginForward: { return *this->mapBeginIterator; }
      case IteratorType::EndForward: { return *this->mapEndIterator; }
      case IteratorType::BeginReverse: { return *this->mapRBeginIterator; }
      case IteratorType::EndReverse: default: { return *this->mapREndIterator; }
    }

    return this->mapValue;
    // std::cout << "Map Get: " << this->mapValue << std::endl;
  }

  virtual const std::pair<const TKey, T> & ConstGet(IteratorType type) override
  {
    switch (type)
    {
    //   case IteratorType::BeginForward: { this->mapValue = *this->mapBeginIterator; return this->mapValue; }
    //   case IteratorType::EndForward: { this->mapValue = *this->mapEndIterator; return this->mapValue; }
    //   case IteratorType::BeginReverse: { this->mapValue = *this->mapRBeginIterator; return this->mapValue; }
    //   case IteratorType::EndReverse: default: { this->mapValue = *this->mapREndIterator; return this->mapValue; }
      case IteratorType::BeginForward: { return *this->mapBeginIterator; }
      case IteratorType::EndForward: { return *this->mapEndIterator; }
      case IteratorType::BeginReverse: { return *this->mapRBeginIterator; }
      case IteratorType::EndReverse: default: { return *this->mapREndIterator; }
    }

    return this->mapValue;
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: return this->mapBeginIterator != this->mapEndIterator;
      case IteratorType::BeginReverse: return this->mapRBeginIterator != this->mapREndIterator;
      case IteratorType::EndForward:
      case IteratorType::EndReverse:
      default:
        return true;
    }

    return false;
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::EndForward: return this->mapBeginIterator != this->mapEndIterator;
      case IteratorType::EndReverse: return this->mapRBeginIterator != this->mapREndIterator;
      case IteratorType::BeginForward:
      case IteratorType::BeginReverse:
      default:
        return true;
    }

    return false;
  }

// pass a boolean by reference and return true/false whether force to end has been set
  virtual IQueryableData<std::pair<const TKey, T>> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
  {
    // std::cout << "[NEXT] underlying begin value before" << std::endl;

    if (this->forceToEnd)
    {
      iterated = this->size;
      isForcingToEnd = true;
      return *this;
    }

    switch (type)
    {
      case IteratorType::BeginForward: ++this->mapBeginIterator; break;
      case IteratorType::EndForward: ++this->mapEndIterator; break;
      case IteratorType::BeginReverse: ++this->mapRBeginIterator; break;
      case IteratorType::EndReverse: ++this->mapREndIterator; break;
    }
    // std::cout << "[NEXT] underlying begin value after: " << *this->mapBeginIterator << std::endl;

    iterated = 1;
    return *this;
  }

  virtual IQueryableData<std::pair<const TKey, T>> & Prev(IteratorType type, size_t & iterated) override
  {
    // std::cout << "[PREV] underlying begin value before: " << std::endl;

    switch (type)
    {
      case IteratorType::BeginForward: --this->mapBeginIterator; break;
      case IteratorType::EndForward: --this->mapEndIterator; break;
      case IteratorType::BeginReverse: --this->mapRBeginIterator; break;
      case IteratorType::EndReverse: --this->mapREndIterator; break;
    }
      // std::cout << "[PREV] underlying begin value after: " << std::endl;
    iterated = 1;
    return *this;
  }

  virtual IQueryableData<std::pair<const TKey, T>> & Add(int addend, IteratorType type) override
  {
    // std::cout << "\nBAD" << std::endl;
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (type)
    {
      case IteratorType::BeginForward: while (addend--) ++this->mapBeginIterator; break;
      case IteratorType::EndForward: while (addend--) ++this->mapEndIterator; break;
      case IteratorType::BeginReverse: while (addend--) ++this->mapRBeginIterator; break;
      case IteratorType::EndReverse: while (addend--) ++this->mapREndIterator; break;
    }

    return *this;
  }

  virtual IQueryableData<std::pair<const TKey, T>> & Subtract(int subtrahend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (type)
    {
      case IteratorType::BeginForward: while (subtrahend--) --this->mapBeginIterator; break;
      case IteratorType::EndForward: while (subtrahend--) --this->mapEndIterator; break;
      case IteratorType::BeginReverse: while (subtrahend--) --this->mapRBeginIterator; break;
      case IteratorType::EndReverse: while (subtrahend--) --this->mapREndIterator; break;
    }

    return *this;
  }

  virtual void Clear() override
  {
    this->mapItems->clear();
    this->size = 0;
  }

  virtual QueryableIterator<std::pair<const TKey, T>> begin() override
  {
    // std::cout << "Map Queryable begin" << std::endl;
    this->mapBeginIterator = this->mapItems->begin();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<std::pair<const TKey, T>> retVal(this->Clone(), 0, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<std::pair<const TKey, T>> end() override
  {
    // std::cout << "Map Queryable end" << std::endl;
    this->mapEndIterator = this->mapItems->end();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<std::pair<const TKey, T>> retVal(this->Clone(), this->size, IteratorType::EndForward);

    return retVal;
  }

  virtual QueryableIterator<std::pair<const TKey, T>> rbegin() override
  {
    this->mapRBeginIterator = this->mapItems->rbegin();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<std::pair<const TKey, T>> retVal(this->Clone(), 0, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<std::pair<const TKey, T>> rend() override
  {
    this->mapREndIterator = this->mapItems->rend();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<std::pair<const TKey, T>> retVal(this->Clone(), this->size, IteratorType::EndReverse);
    return retVal;
  }

  virtual void ForceEnd(IteratorType type) override
  {
    // TODO --> I think WhereQueryable might need two different sizes
    //   1. theoretical size when skipping elements
    //   2. true size

    // std::cout << "force to end by size: " << this->size << std::endl;
    this->forceToEnd = true;

    switch(type)
    {
      case IteratorType::BeginForward:
        this->mapBeginIterator = this->mapItems->end();
        break;
      case IteratorType::EndForward:
        this->mapEndIterator = this->mapItems->end();
        break;
      case IteratorType::BeginReverse:
        this->mapREndIterator = this->mapItems->rend();
        break;
      case IteratorType::EndReverse:
        this->mapREndIterator = this->mapItems->rend();
        break;
    }
  }

  virtual void ForceBegin(IteratorType type) override
  {
    this->forceToBegin = true;

    switch(type)
    {
      case IteratorType::BeginForward:
        this->mapBeginIterator = this->mapItems->begin();
        break;
      case IteratorType::EndForward:
        this->mapEndIterator = this->mapItems->begin();
        break;
      case IteratorType::BeginReverse:
        this->mapREndIterator = this->mapItems->rbegin();
        break;
      case IteratorType::EndReverse:
        this->mapREndIterator = this->mapItems->rbegin();
        break;
    }
  }
};

#endif
