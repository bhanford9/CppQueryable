#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEMAPDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEMAPDATA_H

#include <iostream>
#include <map>
#include <vector>

#include "../QueryableData.hpp"

// After you call select on a map, you are not conceptually dealing with a map structure anymore
//   so I have decided to just have it inherit a vector structure instead
// This has caused me to wonder if all of the Select classes could be implemented this way
//   it may be better to do so simply for consistency between types
//   it would also take away the need for different select classes
//   need to think through if there is significant benefit of persisting stdlib container type

template<
  typename TSourceKey,
  typename TDestination,
  typename TDestinationAllocator,
  typename TSourceValue, // source defined last so it can be passed in as TArgs...
  typename TSourceKeyLessThan,// = std::less<TSourceKey>,
  typename TSourceAllocator>// = std::allocator<std::pair<const TSourceKey, TSourceValue>>>
class SelectQueryableMapData :
  public QueryableData<
    TDestination,
    std::vector,
    TDestination,
    TDestinationAllocator>
{
private:
  std::function<TDestination(std::pair<const TSourceKey, TSourceValue>)> selector;
  std::shared_ptr<
    QueryableData<
      TSourceKey,
      std::map,
      std::pair<const TSourceKey, TSourceValue>,
      TSourceValue,
      TSourceKeyLessThan,
      TSourceAllocator>>
    original;

// TODO --> I think an allocator and lessthan comparer need to be able to be passed in as destination parameters

public:
  SelectQueryableMapData(
    std::shared_ptr<
      QueryableData<
        TSourceKey,
        std::map,
        std::pair<const TSourceKey, TSourceValue>,
        TSourceValue,
        TSourceKeyLessThan,
        TSourceAllocator>> && data,
    std::function<TDestination(std::pair<const TSourceKey, TSourceValue>)> selector)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    // std::cout << "select queryable map data move constructor" << std::endl;
    selector = selector;
    original = std::move(data);
    this->size = original->Count();
  }

  SelectQueryableMapData(
    const std::shared_ptr<
      QueryableData<
        TSourceKey,
        std::map,
        std::pair<const TSourceKey, TSourceValue>,
        TSourceValue,
        TSourceKeyLessThan,
        TSourceAllocator>> & data,
    std::function<TDestination(std::pair<const TSourceKey, TSourceValue>)> selector)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    // std::cout << "select queryable map data copy constructor 1" << std::endl;
    this->selector = selector;
    this->original = data;
    this->size = original->Count();
  }

  SelectQueryableMapData(
    const
      SelectQueryableMapData<
        TSourceKey,
        TDestination,
        TDestinationAllocator,
        TSourceValue,
        TSourceKeyLessThan,
        TSourceAllocator> &
      data)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    // std::cout << "select queryable map data copy constructor 2" << std::endl;
    this->selector = data.selector;
    this->original = data.original;
    this->size = original->Count();
  }

  virtual ~SelectQueryableMapData() { }

  virtual std::shared_ptr<IQueryableData<TDestination>> Clone() override
  {
    return std::make_shared<
      SelectQueryableMapData<
        TSourceKey,
        TDestination,
        TDestinationAllocator,
        TSourceValue,
        TSourceKeyLessThan,
        TSourceAllocator>>(*this);
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    return this->original->CanIncrement(type);
  }

  virtual bool CanDecrement(IteratorType type) override
  {
    return this->original->CanDecrement(type);
  }

  virtual TDestination & Get(IteratorType type) override
  {
    // std::cout << "map select get" << std::endl;
    this->value = this->selector(this->original->Get(type));
    return this->value;
  }

  virtual const TDestination & ConstGet(IteratorType type) override
  {
    // std::cout << "map select const get" << std::endl;
    this->value = this->selector(this->original->Get(type));
    return this->value;
  }
  
  virtual IQueryableData<TDestination> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
  {
    // std::cout << "Select Can Increment: " << this->original->CanIncrement(type) << std::endl;
    // std::cout << "Select Data Next before value: " << this->original->Get(type) << std::endl;
    this->original->Next(type, iterated, isForcingToEnd);
    return *this;
  }

  virtual IQueryableData<TDestination> & Prev(IteratorType type, size_t & iterated) override
  {
    // std::cout << "Select Data Prev" << std::endl;
    this->original->Prev(type, iterated);
    return *this;
  }

  virtual IQueryableData<TDestination> & Add(int addend, IteratorType type) override
  {
    // std::cout << "Select Data Add" << std::endl;
    this->original->Add(addend, type);
    return *this;
  }

  virtual IQueryableData<TDestination> & Subtract(int subtrahend, IteratorType type) override
  {
    // std::cout << "Select Data Subtract" << std::endl;
    this->original->Add(subtrahend, type);
    return *this;
  }

  void Add(TDestination item) override
  {
    // this wont easily or quickly work... might want to nix it
    this->items->push_back(item);
    this->size++;
  }

  virtual std::shared_ptr<IQueryableData<TDestination>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::vector<TDestination, TDestinationAllocator> data(this->items->get_allocator());

    for (TDestination & value : *this)
    {
      data.push_back(value);
    }

    return std::make_shared<QueryableVectorData<TDestination, TDestinationAllocator>>(std::move(data));
  }
  
  virtual QueryableIterator<TDestination> begin() override
  {
    // std::cout << "Map Select Data begin" << std::endl;
    QueryableIterator<std::pair<const TSourceKey, TSourceValue>> child = this->original->begin();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TDestination> end() override
  {
    // std::cout << "Map Select Data end" << std::endl;
    QueryableIterator<std::pair<const TSourceKey, TSourceValue>> child = this->original->end();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::EndForward);
    return retVal;
  }

  virtual QueryableIterator<TDestination> rbegin() override
  {
    QueryableIterator<std::pair<const TSourceKey, TSourceValue>> child = this->original->rbegin();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TDestination> rend() override
  {
    QueryableIterator<std::pair<const TSourceKey, TSourceValue>> child = this->original->rend();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::EndReverse);
    return retVal;
  }
};

#endif
