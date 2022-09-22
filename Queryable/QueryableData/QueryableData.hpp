#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "IQueryableData.hpp"
#include "../Iterators/IteratorType.hpp"
#include "../Iterators/QueryableIterator.hpp"
#include "../TypeConstraintUtil.hpp"
#include "../Utilities/Condition.hpp"
#include "../Sorters/ISorter.hpp"

#include "../../DataStructures/Person.hpp"

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class QueryableData : public IQueryableData<TObj>
{
public:
  using TForwardIterator = typename TIterable<TObj, TArgs...>::iterator;
  using TReverseIterator = typename TIterable<TObj, TArgs...>::reverse_iterator;
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  TObj value;
  size_t size = 0;
  bool forceToEnd = false;
  bool forceToBegin = false;

  // this is a mess, but a better working solution is escaping me...
  //  - when sorting, copies of the iterators are made and used for comparison
  //  - these iterators contain a copy of this data and therefore a copy of the underlying items
  //  - these iterators also change the underlying items, so I need them to actually change
  //    the same underlying structure
  //
  //  - there is a lot of coupling of the data and the actions on that data in here. might want
  //    to split them apart better
  std::shared_ptr<TIterable<TObj, TArgs...>> items;

  TForwardIterator beginIterator;
  TForwardIterator endIterator;
  TReverseIterator rbeginIterator;
  TReverseIterator rendIterator;

  void DefaultInitialize()
  {
    this->beginIterator = this->items->begin();
    this->endIterator = this->items->end();
    this->rbeginIterator = this->items->rbegin();
    this->rendIterator = this->items->rend();
    this->size = 0;
  }

public:

  QueryableData()
  {
    // std::cout << "QueryableData Constructor 1" << std::endl;
    this->items = std::make_shared<TIterable<TObj, TArgs...>>();
    this->DefaultInitialize();
  }
  QueryableData(const TIterable<TObj, TArgs...> & items)
  {
    this->items = std::make_shared<TIterable<TObj, TArgs...>>(items);
    this->DefaultInitialize();

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    //
    //   another option could be to let the child constructors set the size, but
    //   that is a bit harder to maintain. Would need to always call the method
    //   to have the child calculate the size after constructions... may be the cleanest
    //   since the user never sees this class anyway
    this->size = this->items->size();
    // std::cout << "QueryableData Constructor 2: " << this->size << std::endl;
  }
  QueryableData(TIterable<TObj, TArgs...> && items)
  {
    // std::cout << "\nQueryableData Constructor 3" << std::endl;
    this->items = std::make_shared<TIterable<TObj, TArgs...>>(items);

    this->DefaultInitialize();

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    //
    //   another option could be to let the child constructors set the size, but
    //   that is a bit harder to maintain. Would need to always call the method
    //   to have the child calculate the size after constructions... may be the cleanest
    //   since the user never sees this class anyway
    this->size = items.size();
    // std::cout << "QueryableData Constructor 3: " << this->size << std::endl;
  }
  QueryableData(const QueryableData<TObj, TIterable, TArgs...> & data)
  {
    // std::cout << "QueryableData Copy Constructor 2: " << data.size << std::endl;
    this->items = data.items;

    this->beginIterator = data.beginIterator;
    this->endIterator = data.endIterator;
    this->rbeginIterator = data.rbeginIterator;
    this->rendIterator = data.rendIterator;

    // this->value = data.value;
    this->size = data.size;

    this->forceToEnd = data.forceToEnd;
    this->forceToBegin = data.forceToBegin;
  }

  QueryableData(std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data)
  {
      throw;
    this->items = std::move(data->items);
    this->DefaultInitialize();
    this->size = data->Count();

    this->forceToEnd = data->forceToEnd;
    this->forceToBegin = data->forceToBegin;
  }

  QueryableData(QueryableIterator<TObj> first, QueryableIterator<TObj> last, TArgs... args) :
    items(std::make_shared<TIterable<TObj, TArgs...>>(first, last, args...))
  {
      throw;
  }

  inline QueryableData<TObj, TIterable, TArgs...> & operator=(IQueryableData<TObj> && other)
  {
    std::cout << "this shouldn't be necessary" << std::endl;
    this->Clear();
    
    for (const TObj & item : other)
    {
      this->Add(item);
    }

    return *this;
  }

  virtual ~QueryableData() { }

  template<typename TAllocator>
  TAllocator GetAllocator()
  {
    return this->items->get_allocator();
  }

  template<typename TLessThan>
  TLessThan GetValueCompare()
  {
    return this->items->value_comp();
  }

  virtual bool CanIncrement(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: return this->beginIterator != this->endIterator;
      case IteratorType::BeginReverse: return this->rbeginIterator != this->rendIterator;
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
      case IteratorType::EndForward: return this->beginIterator != this->endIterator;
      case IteratorType::EndReverse: return this->rbeginIterator != this->rendIterator;
      case IteratorType::BeginForward:
      case IteratorType::BeginReverse:
      default:
        return true;
    }

    return false;
  }

// pass a boolean by reference and return true/false whether force to end has been set
  virtual IQueryableData<TObj> & Next(IteratorType type, size_t & iterated, bool & isForcingToEnd) override
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
      case IteratorType::BeginForward: ++this->beginIterator; break;
      case IteratorType::EndForward: ++this->endIterator; break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; break;
      case IteratorType::EndReverse: ++this->rendIterator; break;
    }
    // std::cout << "[NEXT] underlying begin value after: " << *this->beginIterator << std::endl;

    iterated = 1;
    return *this;
  }

  virtual IQueryableData<TObj> & Prev(IteratorType type, size_t & iterated) override
  {
    // std::cout << "[PREV] underlying begin value before: " << std::endl;

    switch (type)
    {
      case IteratorType::BeginForward: --this->beginIterator; break;
      case IteratorType::EndForward: --this->endIterator; break;
      case IteratorType::BeginReverse: --this->rbeginIterator; break;
      case IteratorType::EndReverse: --this->rendIterator; break;
    }
      // std::cout << "[PREV] underlying begin value after: " << std::endl;
    iterated = 1;
    return *this;
  }

  virtual IQueryableData<TObj> & Add(int addend, IteratorType type) override
  {
    // std::cout << "\nBAD" << std::endl;
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (type)
    {
      case IteratorType::BeginForward: while (addend--) ++this->beginIterator; break;
      case IteratorType::EndForward: while (addend--) ++this->endIterator; break;
      case IteratorType::BeginReverse: while (addend--) ++this->rbeginIterator; break;
      case IteratorType::EndReverse: while (addend--) ++this->rendIterator; break;
    }

    return *this;
  }

  virtual IQueryableData<TObj> & Subtract(int subtrahend, IteratorType type) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (type)
    {
      case IteratorType::BeginForward: while (subtrahend--) --this->beginIterator; break;
      case IteratorType::EndForward: while (subtrahend--) --this->endIterator; break;
      case IteratorType::BeginReverse: while (subtrahend--) --this->rbeginIterator; break;
      case IteratorType::EndReverse: while (subtrahend--) --this->rendIterator; break;
    }

    return *this;
  }

  virtual void Add(TObj obj) override = 0;

  virtual size_t Count() override
  {
    return this->size;
  }

  size_t StorageSize() const override
  {
    return this->size;
  }

  virtual void Clear() override
  {
    this->items->clear();
    this->size = 0;
  }

  virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
  {
    return this->Clone();
  }

  virtual void Sort(std::shared_ptr<ISorter<TObj, TIterable, TArgs...>> sorter)
  {
    //   std::cout << "in default sorter" << std::endl;
    sorter->Sort(*this->items);
  }

  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "Standard Queryable begin" << std::endl;
    this->beginIterator = this->items->begin();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<TObj> retVal(this->Clone(), 0, IteratorType::BeginForward);
    return retVal;
  }

  virtual QueryableIterator<TObj> end() override
  {
    // std::cout << "Standard Queryable end" << std::endl;
    this->endIterator = this->items->end();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndForward);

    return retVal;
  }

  virtual QueryableIterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items->rbegin();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<TObj> retVal(this->Clone(), 0, IteratorType::BeginReverse);
    return retVal;
  }

  virtual QueryableIterator<TObj> rend() override
  {
    this->rendIterator = this->items->rend();
    this->forceToBegin = false;
    this->forceToEnd = false;
    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndReverse);
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
        this->beginIterator = this->items->end();
        break;
      case IteratorType::EndForward:
        this->endIterator = this->items->end();
        break;
      case IteratorType::BeginReverse:
        this->rendIterator = this->items->rend();
        break;
      case IteratorType::EndReverse:
        this->rendIterator = this->items->rend();
        break;
    }
  }

  virtual void ForceBegin(IteratorType type) override
  {
    this->forceToBegin = true;

    switch(type)
    {
      case IteratorType::BeginForward:
        this->beginIterator = this->items->begin();
        break;
      case IteratorType::EndForward:
        this->endIterator = this->items->begin();
        break;
      case IteratorType::BeginReverse:
        this->rendIterator = this->items->rbegin();
        break;
      case IteratorType::EndReverse:
        this->rendIterator = this->items->rbegin();
        break;
    }
  }
};

#endif
