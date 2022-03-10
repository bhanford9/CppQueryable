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

#include "../Iterators/Iterator.hpp"
#include "../Iterators/IteratorType.hpp"
#include "../Iterators/QueryableIterator.hpp"
#include "../Iterators/QueryableDataIterator.hpp"
#include "../TypeConstraintUtil.hpp"
#include "../Utilities/Condition.hpp"
#include "IQueryableData.hpp"

#include "../../DataStructures/Person.hpp"

template<
  typename TObj,
  typename TOut,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class QueryableData : public IQueryableData<TObj, TOut>
{
public:
  using TForwardIterator = typename TIterable<TObj, TArgs...>::iterator;
  using TReverseIterator = typename TIterable<TObj, TArgs...>::reverse_iterator;
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  // typedef typename std::vector<TObj, TArgs...>::iterator TVectorIterator;

  // TODO --> consider making this a pointer so data doesn't have to be copied
  TOut value;
  int64_t size = 0;

  TIterable<TObj, TArgs...> items;

  TForwardIterator beginIterator;
  TForwardIterator endIterator;
  TReverseIterator rbeginIterator;
  TReverseIterator rendIterator;


  void DefaultInitialize()
  {
    this->beginIterator = this->items.begin();
    this->endIterator = this->items.end();
    this->rbeginIterator = this->items.rbegin();
    this->rendIterator = this->items.rend();
    this->size = 0;
    //this->index = 0;
  }

  inline virtual TOut & ToOutput(TObj & original) const
  {
    return original;
  }

  inline virtual const TOut & ToOutputConst(const TObj & original) const
  {
    return original;
  }

public:


  virtual void * GetData()
  {
    return &this->items;
  }
  // for each of these inline virtual overriden methods, there is usually something dangerous and/or unorthodox going on
  // compared to what you would expect to see within a normal iterator. All of these methods are intended to be
  // hidden from external users and only _respectfully_ used by the Queryable library. Because of this,
  // the methods are implemented in such a way that they expect the user of the method to be using it in a very specific
  // way that will prevent it from executing the dangerous and/or unorthodox path.

  // inline virtual bool operator<(const QueryableIterator<TOut>& other) const override
  // {
  //   switch (this->type)
  //   {
  //     case IteratorType::BeginForward: return this->beginIterator < other.beginIterator;
  //     case IteratorType::EndForward: return this->endIterator < other.endIterator;
  //     case IteratorType::BeginReverse: return this->rbeginIterator < other.rbeginIterator;
  //     case IteratorType::EndReverse: default: return this->rendIterator < other.rendIterator;
  //   }
  // }

  inline virtual IQueryableIteratorData<TOut> & Next(IteratorType type, uint64_t & iterated) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: ++this->beginIterator; break;
      case IteratorType::EndForward: ++this->endIterator; break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; break;
      case IteratorType::EndReverse: ++this->rendIterator; break;
    }

    iterated = 1;
    return *this;
  }

  inline virtual IQueryableIteratorData<TOut> & Prev(IteratorType type, uint64_t & iterated) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: --this->beginIterator; break;
      case IteratorType::EndForward: --this->endIterator; break;
      case IteratorType::BeginReverse: --this->rbeginIterator; break;
      case IteratorType::EndReverse: --this->rendIterator; break;
    }

    iterated = 1;
    return *this;
  }

  inline virtual TOut & Get(IteratorType type) override
  {
    switch (type)
    {
        case IteratorType::BeginForward: { TObj value1 = *this->beginIterator; this->value = this->ToOutput(value1); return this->value; }
        case IteratorType::EndForward: { TObj value2 = *this->endIterator; this->value = this->ToOutput(value2); return this->value; }
        case IteratorType::BeginReverse: { TObj value3 = *this->rbeginIterator; this->value = this->ToOutput(value3); return this->value; }
        case IteratorType::EndReverse: default: { TObj value4 = *this->rendIterator; this->value = this->ToOutput(value4); return this->value; }
    }
  }

  inline virtual const TOut & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: this->value = this->ToOutputConst(*this->beginIterator); return this->value;
      case IteratorType::EndForward: this->value = this->ToOutputConst(*this->endIterator); return this->value;
      case IteratorType::BeginReverse: this->value = this->ToOutputConst(*this->rbeginIterator); return this->value;
      case IteratorType::EndReverse: default: this->value = this->ToOutputConst(*this->rendIterator); return this->value;
    }
  }

  inline virtual IQueryableIteratorData<TOut> & Add(int addend, IteratorType type) override
  {
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

  inline virtual IQueryableIteratorData<TOut> & Subtract(int subtrahend, IteratorType type) override
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

  QueryableData()
  {
    // std::cout << "\nQueryableData Constructor 1" << std::endl;
    this->DefaultInitialize();
  }
  QueryableData(const TIterable<TObj, TArgs...> & items)
  {
    // std::cout << "\nQueryableData Constructor 2" << std::endl;
    this->items = items;
    this->DefaultInitialize();

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(TIterable<TObj, TArgs...> && items)
  {
    // std::cout << "\nQueryableData Constructor 3" << std::endl;
    this->items = std::move(items);

    this->DefaultInitialize();
    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->value = items.value;
    this->size = this->items.size();
  }
  // QueryableData(TVectorIterator first, TVectorIterator last)
  // {
  //   std::cout << "\nQueryableData Constructor 4" << std::endl;
  //   // TODO SFINAE require this constructor
  //   this->items = TIterable<TObj, TAllocator, TArgs...>(first, last);
  //
  //   this->DefaultInitialize();
  //   this->size = this->items.size();
  // }
  QueryableData(const QueryableData<TObj, TOut, TIterable, TArgs...> & data)
  {
    // std::cout << "\nQueryableData Constructor 5" << std::endl;
    this->items = data.items;

    this->DefaultInitialize();

    this->value = data.value;
    this->size = data.size;
  }
  QueryableData(std::shared_ptr<QueryableData<TObj, TOut, TIterable, TArgs...>> && data)
  {
    // std::cout << "\nQueryableData Constructor 6" << std::endl;
    // std::cout << "incoming data is null: " << (data.get() ? "no" : "yes") << std::endl;
    // std::cout << "incoming data size: " << data->Count() << std::endl;
    // THIS WOULD BE MUCH BETTER IF WE CAN MOVE IT INSTEAD OF COPY
    this->items = std::move(data->items);// *static_cast<TIterable<TObj, TArgs...>*>(data->GetData());
    // std::cout << "after setting items" << std::endl;

    this->DefaultInitialize();
    this->size = data->Count();
    // std::cout << "leaving constructor 6" << std::endl;
  }
  // QueryableData(std::shared_ptr<IQueryableData<TObj, TOut>> && data)
  // {
  //   // std::cout << "\nQueryableData Constructor 6" << std::endl;
  //   // std::cout << "incoming data is null: " << (data.get() ? "no" : "yes") << std::endl;
  //   // std::cout << "incoming data size: " << data->Count() << std::endl;
  //   // THIS WOULD BE MUCH BETTER IF WE CAN MOVE IT INSTEAD OF COPY
  //   this->items = *static_cast<TIterable<TObj, TArgs...>*>(data->GetData());
  //   // std::cout << "after setting items" << std::endl;
  //
  //   this->DefaultInitialize();
  //   this->size = data->Count();
  //   // std::cout << "leaving constructor 6" << std::endl;
  // }
  virtual ~QueryableData() { }

  // void AddCondition(std::function<bool(const TObj &)> condition) override
  // {
  //   this->condition += condition;
  // }
  //
  // bool PassesCondition(const TObj & obj) const override
  // {
  //   return this->condition(obj);
  // }

  virtual void Add(TObj obj) override
  {
    // leave empty
  }

  virtual int Count() override
  {
    return this->size;
  }

  int StorageSize() override
  {
    return this->size;
  }

  virtual void Clear() override
  {
    this->items.clear();
    this->size = 0;
  }

  template<
    typename TOutput = SortOutput<TObj, TIterable, TArgs...>,
    typename TLessThan = std::less<TObj>>
  TOutput Sort(const Sorter<TObj, TIterable, TOutput, TArgs...> & sorter, TLessThan lessThan = {})
  {
    return sorter.Sort(this->items, lessThan);
  }

  // virtual void Update(
  //   QueryableIterator<TOut> first,
  //   QueryableIterator<TOut> last,
  //   std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) override
  // {
  //   // TODO SFINAE require this constructor
  //   this->items = TIterable<TObj, TArgs...>(first, last);
  //   this->size = this->items.size();
  // }
  //
  // virtual void Update(TVectorIterator first, TVectorIterator last) override
  // {
  //   // TODO SFINAE require this constructor
  //   this->items = TIterable<TObj, TArgs...>(first, last);
  //   this->size = this->items.size();
  // }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TOut> begin() override
  {
    this->beginIterator = this->items.begin();
    QueryableIterator<TOut> retVal(this, 0, IteratorType::BeginForward);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TOut> end() override
  {
    this->endIterator = this->items.end();
    QueryableIterator<TOut> retVal(this, this->size, IteratorType::EndForward);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TOut> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    QueryableIterator<TOut> retVal(this, 0, IteratorType::BeginReverse);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TOut> rend() override
  {
    this->rendIterator = this->items.rend();
    QueryableIterator<TOut> retVal(this, this->size, IteratorType::EndReverse);
    return retVal;
  }
};

#endif
