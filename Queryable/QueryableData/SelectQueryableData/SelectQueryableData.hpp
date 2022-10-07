#ifndef CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SELECTQUERYABLEDATA_H

#include <iostream>
#include <deque>
#include <vector>

#include "../QueryableData.hpp"

// template<
//   typename TOriginal,
//   typename TCurrent,
//   template<typename, typename ...> typename TIterable,
//   typename ...TArgs>

template<
  typename TSource,
  typename TDestination,
  template<typename, typename ...> typename TIterable,
  typename TSourceIterating,
  typename TDestinationAllocator = std::allocator<TDestination>,
  typename ...TArgs> // source defined last so it can be passed in as TArgs...
class SelectQueryableData : public QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>
{
private:
  std::function<TDestination(TSourceIterating)> selector;
  std::shared_ptr<QueryableData<TSource, TIterable, TSourceIterating, TArgs...>> original;

public:
  SelectQueryableData(
    std::shared_ptr<QueryableData<TSource, TIterable, TSourceIterating, TArgs...>> && data,
    std::function<TDestination(TSourceIterating)> selector)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    this->selector = selector;
    this->original = std::move(data);
    this->size = original->Count();
  }

  SelectQueryableData(
    const std::shared_ptr<QueryableData<TSource, TIterable, TSourceIterating, TArgs...>> & data,
    std::function<TDestination(TSourceIterating)> selector)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    this->selector = selector;
    this->original = data;
    this->size = original->Count();
  }

  SelectQueryableData(const SelectQueryableData<TSource, TDestination, TIterable, TSourceIterating, TDestinationAllocator, TArgs...> & data)
    : QueryableData<TDestination, std::vector, TDestination, TDestinationAllocator>()
  {
    this->selector = data.selector;
    this->original = data.original;
    this->size = original->Count();
  }

  virtual ~SelectQueryableData() { }

  virtual std::shared_ptr<IQueryableData<TDestination>> Clone() override
  {
    return std::make_shared<SelectQueryableData<TSource, TDestination, TIterable, TSourceIterating, TDestinationAllocator, TArgs...>>(*this);
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
    this->items->push_back(item);
    this->size++;
  }

  virtual std::shared_ptr<IQueryableData<TDestination>> GetRealizedQueryableData() override
  {
    // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
    std::vector<TDestination, TDestinationAllocator> data(this->items->get_allocator());

    for (TDestination value : *this)
    {
      data.push_back(value);
    }

    return std::make_shared<QueryableVectorData<TDestination, TDestinationAllocator>>(std::move(data));
  }
  
  virtual QueryableIterator<TDestination> begin() override
  {
    // std::cout << "Deque Select Data begin" << std::endl;
    QueryableIterator<TSourceIterating> child = this->original->begin();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TDestination> end() override
  {
    // std::cout << "Deque Select Data end" << std::endl;
    QueryableIterator<TSourceIterating> child = this->original->end();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::EndForward);
    return retVal;
  }

  virtual QueryableIterator<TDestination> rbegin() override
  {
    QueryableIterator<TSourceIterating> child = this->original->rbegin();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TDestination> rend() override
  {
    QueryableIterator<TSourceIterating> child = this->original->rend();
    QueryableIterator<TDestination> retVal(this->Clone(), child.index, IteratorType::EndReverse);
    return retVal;
  }
};

#endif