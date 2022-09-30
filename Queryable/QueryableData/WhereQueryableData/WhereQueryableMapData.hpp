#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMAPDATA_H

#include <iostream>
#include <map>

#include "../../Utilities/Condition.hpp"
#include "../QueryableMapData.hpp"

template<
  typename TKey,
  typename TValue,
  typename TCompare = std::less<TKey>,
  typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
class WhereQueryableMapData : public QueryableMapData<TKey, TValue, TCompare, TAllocator>
{
protected:
  Condition<std::pair<const TKey, TValue>> condition;
  std::shared_ptr<QueryableData<std::pair<const TKey, TValue>, std::map, TCompare, TAllocator>> originalMap;
  bool sizeIsCalculated;

  void IncrementPastFalseConditions(IteratorType type, size_t & iterated, bool & isForcingToEnd)
  {
    while (this->originalMap->CanIncrement(type) && this->condition && !this->condition(this->originalMap->Get(type)))
    {
      size_t internalIterated = 1;
      this->originalMap->Next(type, internalIterated, isForcingToEnd);
      iterated += internalIterated;
    }
  }

  void DecrementPastFalseConditions(IteratorType type, size_t & iterated)
  {
    while (this->originalMap->CanDecrement(type) && this->condition && !this->condition(this->originalMap->Get(type)))
    {
      size_t internalIterated = 1;
      this->originalMap->Prev(type, internalIterated);
      iterated += internalIterated;
    }
  }

public:
  // WhereQueryableMapData(
  //   std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> && data,
  //   std::function<bool(std::pair<const TKey, TValue>)> && condition)
  // {
  //   std::cout << "Where Queryable Map Data constructor 1" << std::endl;
  //   this->originalMap = std::move(data);
  //   this->sizeIsCalculated = false;
  //   this->condition += condition;
  // }
  WhereQueryableMapData(
    std::shared_ptr<QueryableData<std::pair<const TKey, TValue>, std::map, TCompare, TAllocator>> && data,
    std::function<bool(const std::pair<const TKey, TValue> &)> && condition)
  {
    // std::cout << "Where Queryable Map Data constructor 2" << std::endl;
    this->originalMap = std::move(data);
    this->sizeIsCalculated = false;
    this->condition += condition;
  }
  // WhereQueryableMapData(
  //   std::shared_ptr<QueryableMapData<TKey, TValue, TCompare, TAllocator>> && data,
  //   std::function<bool(std::pair<const TKey, TValue>)> && condition)
  // {
  //   std::cout << "Where Queryable Map Data constructor 2" << std::endl;
  //   this->originalMap = std::move(data);
  //   this->sizeIsCalculated = false;
  //   this->condition += condition;
  // }
  WhereQueryableMapData(const WhereQueryableMapData<TKey, TValue, TCompare, TAllocator> & other)
  {
    // std::cout << "Where Queryable Map Data constructor 3" << std::endl;
    this->originalMap = other.originalMap;
    this->sizeIsCalculated = other.sizeIsCalculated;
    this->condition = other.condition;
  }

  virtual ~WhereQueryableMapData() { }
  
  virtual size_t Count() override
  {
    // if (this->sizeIsCalculated)
    // {
    //   return this->size;
    // }

    size_t count = 0;

    // not sure I like needing to get the realized queryable data
    auto realized = this->originalMap->GetRealizedQueryableData();

    for (const auto & item : *realized)
    {
      if (condition(item))
      {
        count++;
      }
    }

    this->size = count;
    // this->sizeIsCalculated = true;

    return count;
  }

  virtual void Add(std::pair<const TKey, TValue> item) override
  {
    if (this->condition(item))
    {
      this->InternalAdd(item);
      this->size++;
    }
  }

  virtual std::pair<const TKey, TValue> & Get(IteratorType type) override
  {
    return this->originalMap->Get(type);
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    return this->originalMap->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->originalMap->CanDecrement(type);
  }

  virtual const std::pair<const TKey, TValue> & ConstGet(IteratorType type) override
  {
    return this->originalMap->ConstGet(type);
  }

  virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> Clone() override
  {
    return std::make_shared<WhereQueryableMapData<TKey, TValue, TCompare, TAllocator>>(*this);
  }

  virtual void InternalAdd(const std::pair<const TKey, TValue> & item)
  {
    this->originalMap->Add(item);
  }
  
  virtual IQueryableData<std::pair<const TKey, TValue>> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
  {
    this->originalMap->Next(type, iterated, isForcingToEnd);
    
    if (!isForcingToEnd)
    {
      this->IncrementPastFalseConditions(type, iterated, isForcingToEnd);
    }
    
    return *this;
  }

  virtual IQueryableData<std::pair<const TKey, TValue>> & Prev(IteratorType type, size_t & iterated) override
  {
    this->originalMap->Prev(type, iterated);
    this->DecrementPastFalseConditions(type, iterated);
    return *this;
  }

  virtual IQueryableData<std::pair<const TKey, TValue>> & Add(int addend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    std::cout << "bad" << std::endl;
    size_t dummy = 0;
    while (this->originalMap->CanIncrement(type) && addend-- > 0)
    {
      bool isForcingToEnd = false;
      this->Next(type, dummy, isForcingToEnd);
    }

    return *this;
  }

  virtual IQueryableData<std::pair<const TKey, TValue>> & Subtract(int subtrahend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    std::cout << "bad" << std::endl;
    size_t dummy = 0;
    while (this->originalMap->CanDecrement(type) && subtrahend-- > 0)
    {
      this->Prev(type, dummy);
    }

    return *this;
  }

  virtual QueryableIterator<std::pair<const TKey, TValue>> begin() override
  {
    QueryableIterator<std::pair<const TKey, TValue>> child = this->originalMap->begin();

    size_t startIndex = child.index;
    bool isForcingToEnd = false;
    this->IncrementPastFalseConditions(IteratorType::BeginForward, startIndex, isForcingToEnd);
    // std::cout << "begin start index: " << startIndex << std::endl;
    QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), startIndex, IteratorType::BeginForward);

    return retVal;
  }

  virtual QueryableIterator<std::pair<const TKey, TValue>> end() override
  {
    QueryableIterator<std::pair<const TKey, TValue>> child = this->originalMap->end();

    size_t startIndex = child.index;
    QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), startIndex, IteratorType::EndForward);

    return retVal;
  }

  virtual QueryableIterator<std::pair<const TKey, TValue>> rbegin() override
  {
    QueryableIterator<std::pair<const TKey, TValue>> child = this->originalMap->rbegin();

    size_t startIndex = child.index;
    bool isForcingToEnd = false;
    this->IncrementPastFalseConditions(IteratorType::BeginReverse, startIndex, isForcingToEnd);
    QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);

    return retVal;
  }

  virtual QueryableIterator<std::pair<const TKey, TValue>> rend() override
  {
    QueryableIterator<std::pair<const TKey, TValue>> child = this->originalMap->end();

    size_t startIndex = child.index;
    QueryableIterator<std::pair<const TKey, TValue>> retVal(this->Clone(), startIndex, IteratorType::EndReverse);

    return retVal;
  }

  virtual std::shared_ptr<IQueryableData<std::pair<const TKey, TValue>>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner

    // no idea why this constructor is failing to take get_allocator()
    std::map<TKey, TValue, TCompare, TAllocator> data(this->mapItems->key_comp(), this->mapItems->get_allocator());

    for (const std::pair<const TKey, TValue> & value : *this)
    {
        data[value.first] = value.second;
    }

    return std::make_shared<QueryableMapData<TKey, TValue, TCompare, TAllocator>>(std::move(data));
  }
};

#endif
