#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLESETDATA_H

#include <iostream>
#include <set>
#include <vector>

#include "../QueryableData.hpp"

template<
  typename TSource,
  typename TDestination,
  typename TDestinationAllocator = std::allocator<TDestination>,
  typename TSourceLessThan = std::less<TSource>, // source defined last so it can be passed in as TArgs...
  typename TSourceAllocator = std::allocator<TSource>>
class SelectQueryableSetData : 
  public QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>
{
private:
  std::function<TDestination(TSource)> selector;
  std::shared_ptr<QueryableData<TSource, std::set, TSource, TSourceLessThan, TSourceAllocator>> original;

// TODO --> I think an allocator and lessthan comparer need to be able to be passed in as destination parameters

public:
  SelectQueryableSetData(
    std::shared_ptr<QueryableData<TSource, std::set, TSource, TSourceLessThan, TSourceAllocator>> && data,
    std::function<TDestination(TSource)> selector)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    selector = selector;
    original = std::move(data);
    this->size = original->Count();
  }

  SelectQueryableSetData(
    const std::shared_ptr<QueryableData<TSource, std::set, TSource, TSourceLessThan, TSourceAllocator>> & data,
    std::function<TDestination(TSource)> selector)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    selector = selector;
    original = data;
    this->size = original->Count();
  }

  SelectQueryableSetData(
    const
      SelectQueryableSetData<
        TSource,
        TDestination,
        TDestinationAllocator,
        TSourceLessThan,
        TSourceAllocator> &
      data)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    selector = data.selector;
    original = data.original;
    this->size = original->Count();
  }

  virtual ~SelectQueryableSetData() { }

  virtual std::shared_ptr<IQueryableData<TDestination>> Clone() override
  {
    return std::make_shared<
      SelectQueryableSetData<
        TSource,
        TDestination,
        TDestinationAllocator,
        TSourceLessThan,
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
    this->value = this->selector(this->original->Get(type));
    return this->value;
  }

  virtual const TDestination & ConstGet(IteratorType type) override
  {
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
    this->items->insert(item);
    this->size++;
  }

  virtual std::shared_ptr<IQueryableData<TDestination>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::vector<TDestination, TDestinationAllocator> data(this->items->get_allocator());

    for (const TSource & value : *this)
    {
      data.insert(this->selector(value));
    }

    return std::make_shared<QueryableSetData<TDestination, TDestinationAllocator>>(std::move(data));
  }
  
  virtual QueryableIterator<TDestination> begin() override
  {
    // std::cout << "Set Select Data begin" << std::endl;
    QueryableIterator<TSource> child = this->original->begin();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TDestination> end() override
  {
    // std::cout << "Set Select Data end" << std::endl;
    QueryableIterator<TSource> child = this->original->end();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::EndForward);
    return retVal;
  }

  virtual QueryableIterator<TDestination> rbegin() override
  {
    QueryableIterator<TSource> child = this->original->rbegin();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TDestination> rend() override
  {
    QueryableIterator<TSource> child = this->original->rend();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::EndReverse);
    return retVal;
  }
};

#endif
