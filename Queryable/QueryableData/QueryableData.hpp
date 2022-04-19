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
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class QueryableData : public IQueryableData<TObj>
{
public:
  using TForwardIterator = typename TIterable<TObj, TArgs...>::iterator;
  using TReverseIterator = typename TIterable<TObj, TArgs...>::reverse_iterator;
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:

  // TODO --> consider making this a pointer so data doesn't have to be copied
  TObj value;
  size_t size = 0;

  // this is a mess, but I can't find a better working solution...
  //  - when sorting, copies of the iterators are made and used for comparison
  //  - these iterators contain a copy of this data and therefore a copy of the underlying items
  //  - these iterators also change the underlying items, so I need them to actually change
  //    the same underlying structure
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
    //this->index = 0;
  }

public:

  // TODO --> allow TArgs to be passed in as a parameter?
  QueryableData()
  {
    // std::cout << "\nQueryableData Constructor 1" << std::endl;
    this->DefaultInitialize();
  }
  QueryableData(const TIterable<TObj, TArgs...> & items)
  {
    // std::cout << "\nQueryableData Constructor 2" << std::endl;
    this->items = std::make_shared<TIterable<TObj, TArgs...>>(items);
    this->DefaultInitialize();

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items->size();
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
    //   that is a bit harder to maintain
    this->size = items->size();
  }
  QueryableData(const QueryableData<TObj, TIterable, TArgs...> & data)
  {
    // std::cout << "QueryableData Copy Constructor 2" << std::endl;
    this->items = data.items;

    this->beginIterator = data.beginIterator;
    this->endIterator = data.endIterator;
    this->rbeginIterator = data.rbeginIterator;
    this->rendIterator = data.rendIterator;

    this->value = data.value;
    this->size = data.size;
  }






























  // IMPORTANT
  // this needs to be abstract and implemented by each individual class so the overrides are properly executed
  // virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
  // {
  //   std::cout << "\nwithin CLONE" << std::endl;
  //   std::shared_ptr<IQueryableData<TObj>> clone = std::make_shared<QueryableData<TObj, TIterable, TArgs...>>(*this);
  //   return clone;
  // }

  QueryableData(std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && data)
  {
    // std::cout << "\nQueryableData Constructor 6" << std::endl;
    // std::cout << "incoming data is null: " << (data.get() ? "no" : "yes") << std::endl;
    // std::cout << "incoming data size: " << data->Count() << std::endl;
    // THIS WOULD BE MUCH BETTER IF WE CAN MOVE IT INSTEAD OF COPY
    this->items = std::move(data->items);
    // std::cout << "after setting items" << std::endl;

    this->DefaultInitialize();
    this->size = data->Count();
    // std::cout << "leaving constructor 6" << std::endl;
  }
  // QueryableData(std::shared_ptr<IQueryableData<TObj>> && data)
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

  virtual IQueryableData<TObj> & Next(IteratorType type, uint64_t & iterated) override
  {
    // std::cout << "[NEXT] underlying begin value before: " << *this->beginIterator << std::endl;
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

  virtual IQueryableData<TObj> & Prev(IteratorType type, uint64_t & iterated) override
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

// TODO --> override this for all children
  virtual TObj & Get(IteratorType type) override
  {
    switch (type)
    {
        case IteratorType::BeginForward: { this->value = *this->beginIterator; return this->value; }
        case IteratorType::EndForward: { this->value = *this->endIterator; return this->value; }
        case IteratorType::BeginReverse: { this->value = *this->rbeginIterator; return this->value; }
        case IteratorType::EndReverse: default: { this->value = *this->rendIterator; return this->value; }
    }
  }

  virtual const TObj & ConstGet(IteratorType type) override
  {
    switch (type)
    {
      case IteratorType::BeginForward: this->value = *this->beginIterator; return this->value;
      case IteratorType::EndForward: this->value = *this->endIterator; return this->value;
      case IteratorType::BeginReverse: this->value = *this->rbeginIterator; return this->value;
      case IteratorType::EndReverse: default: this->value = *this->rendIterator; return this->value;
    }
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

  // template<
  //   typename TOutput = SortOutput<TObj, TIterable, TArgs...>,
  //   typename TLessThan = std::less<TObj>>
  // TOutput Sort(const Sorter<TObj, TIterable, TOutput, TLessThan, TArgs...> & sorter, TLessThan lessThan = {})
  // {
  //   std::cout << "inner inner sort" << std::endl;
  //   return sorter.Sort(this->items, lessThan);
  // }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> begin() override
  {
    // std::cout << "begin" << std::endl;
    this->beginIterator = this->items->begin();
    QueryableIterator<TObj> retVal(this->Clone(), 0, IteratorType::BeginForward);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> end() override
  {
    // std::cout << "end" << std::endl;
    this->endIterator = this->items->end();
    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndForward);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rbegin() override
  {
    this->rbeginIterator = this->items->rbegin();
    QueryableIterator<TObj> retVal(this->Clone(), 0, IteratorType::BeginReverse);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TObj> rend() override
  {
    this->rendIterator = this->items->rend();
    QueryableIterator<TObj> retVal(this->Clone(), this->size, IteratorType::EndReverse);
    return retVal;
  }
};

#endif