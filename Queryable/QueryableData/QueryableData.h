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

#include "../Iterators/Iterator.h"
#include "../Iterators/IteratorType.h"
#include "../Iterators/QueryableIterator.h"
#include "../Iterators/QueryableDataIterator.h"
#include "../TypeConstraintUtil.h"
#include "../Utilities/Condition.h"
#include "IQueryableData.h"

#include "../../DataStructures/Person.h"

template<typename TObj, typename TIterator, template<typename, typename ...> typename TIterable, typename ...TArgs>
class QueryableData : public IQueryableData<TObj, TIterator>
{
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  typedef typename std::vector<TObj>::iterator TVectorIterator;
  using TForwardIterator = typename TIterable<TObj, TArgs...>::iterator;
  using TReverseIterator = typename TIterable<TObj, TArgs...>::reverse_iterator;

  // TODO --> consider making this a pointer so data doesn't have to be copied
  TObj value;
  int64_t size = 0;
  IteratorType type;

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

  // std::shared_ptr<QueryableData<TObj, TIterator, TIterable, TArgs...>> GetSharedPointerToSelf()
  // {
  //   return std::make_shared<QueryableData<TObj, TIterator, TIterable, TArgs...>>(*this);
  // }

  QueryableData<TObj, TIterator, TIterable, TArgs...> * GetSharedPointerToSelf()
  {
    return this;
  }

  inline virtual TIterator & ToOutput(TObj & original) const
  {
    return original;
  }


  inline virtual const TIterator & ToOutputConst(const TObj & original) const
  {
    return original;
  }

  inline virtual void Add(TIterable<TObj, TArgs...> & items, TObj item) const
  {
    std::cout << "bad add" << std::endl;
    // throw
  }

public:


  // for each of these inline virtual overriden methods, there is usually something dangerous and/or unorthodox going on
  // compared to what you would expect to see within a normal iterator. All of these methods are intended to be
  // hidden from external users and only _respectfully_ used by the Queryable library. Because of this,
  // the methods are implemented in such a way that they expect the user of the method to be using it in a very specific
  // way that will prevent it from executing the dangerous and/or unorthodox path.

  // inline virtual bool operator<(const QueryableIterator<TIterator>& other) const override
  // {
  //   switch (this->type)
  //   {
  //     case IteratorType::BeginForward: return this->beginIterator < other.beginIterator;
  //     case IteratorType::EndForward: return this->endIterator < other.endIterator;
  //     case IteratorType::BeginReverse: return this->rbeginIterator < other.rbeginIterator;
  //     case IteratorType::EndReverse: default: return this->rendIterator < other.rendIterator;
  //   }
  // }

  inline virtual IQueryableIteratorData<TIterator> & Next() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: ++this->beginIterator; break;
      case IteratorType::EndForward: ++this->endIterator; break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; break;
      case IteratorType::EndReverse: ++this->rendIterator; break;
    }

    return *this;
  }

  inline virtual IQueryableIteratorData<TIterator> & Prev() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: --this->beginIterator; break;
      case IteratorType::EndForward: --this->endIterator; break;
      case IteratorType::BeginReverse: --this->rbeginIterator; break;
      case IteratorType::EndReverse: --this->rendIterator; break;
    }

    return *this;
  }

  inline virtual TIterator & Get() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: { TObj value1 = *this->beginIterator; return this->ToOutput(value1); }
      case IteratorType::EndForward: { TObj value2 = *this->endIterator; return this->ToOutput(value2); }
      case IteratorType::BeginReverse: { TObj value3 = *this->rbeginIterator; return this->ToOutput(value3); }
      case IteratorType::EndReverse: default: { TObj value4 = *this->rendIterator; return this->ToOutput(value4); }
    }
  }

  inline virtual const TIterator & ConstGet() const override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: return this->ToOutputConst(*this->beginIterator);
      case IteratorType::EndForward: return this->ToOutputConst(*this->endIterator);
      case IteratorType::BeginReverse: return this->ToOutputConst(*this->rbeginIterator);
      case IteratorType::EndReverse: default: return this->ToOutputConst(*this->rendIterator);
    }
  }

  inline virtual IQueryableIteratorData<TIterator> & Add(int addend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (this->type)
    {
      case IteratorType::BeginForward: while (addend--) ++this->beginIterator; break;
      case IteratorType::EndForward: while (addend--) ++this->endIterator; break;
      case IteratorType::BeginReverse: while (addend--) ++this->rbeginIterator; break;
      case IteratorType::EndReverse: while (addend--) ++this->rendIterator; break;
    }

    return *this;
  }

  inline virtual IQueryableIteratorData<TIterator> & Subtract(int subtrahend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (this->type)
    {
      case IteratorType::BeginForward: while (subtrahend--) --this->beginIterator; break;
      case IteratorType::EndForward: while (subtrahend--) --this->endIterator; break;
      case IteratorType::BeginReverse: while (subtrahend--) --this->rbeginIterator; break;
      case IteratorType::EndReverse: while (subtrahend--) --this->rendIterator; break;
    }

    return *this;
  }

  QueryableData()
    // internalReference(this->GetSharedPointerToSelf())
  {
    std::cout << "\nQueryableData Constructor 1" << std::endl;
    this->DefaultInitialize();
  }
  QueryableData(const TIterable<TObj, TArgs...> & items)
  {
    std::cout << "\nQueryableData Constructor 2" << std::endl;
    std::cout << "incoming items count: " << items.size() << std::endl;
    this->items = items;
    //this->index = 0;
    this->DefaultInitialize();

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(TIterable<TObj, TArgs...> && items)
  {
    std::cout << "\nQueryableData Constructor 3" << std::endl;
    this->items = std::move(items);

    this->DefaultInitialize();
    //this->index = 0;
    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->value = items.value;
    this->size = this->items.size();
  }
  QueryableData(TVectorIterator first, TVectorIterator last)
  {
    std::cout << "\nQueryableData Constructor 4" << std::endl;
    // TODO SFINAE require this constructor
    this->items = TIterable<TObj, TArgs...>(first, last);

    this->DefaultInitialize();
    //this->index = 0;
    this->size = this->items.size();
  }
  QueryableData(const QueryableData<TObj, TIterator, TIterable, TArgs...> & data)
  {
    std::cout << "\nQueryableData Constructor 5" << std::endl;
    this->items = data.items;

    this->DefaultInitialize();

    //this->index = data.index;
    this->value = data.value;
    this->size = data.size;
  }
  QueryableData(std::shared_ptr<IQueryableData<TObj, TIterator>> && data)
  {
    QueryableIterator<TIterator> start = data->begin();
    QueryableIterator<TIterator> stop = data->end();
    std::cout << "start index: " << start.index << ", stop index: " << stop.index << std::endl;

    for (TObj & obj : *data.get())
    {
      std::cout << "adding object: " << obj << std::endl;
      this->Add(this->items, obj);
    }

    std::cout << "after foreach loop" << std::endl;

    this->DefaultInitialize();

    //this->index = data->index;
    // this->value = data->value;
    // this->size = data->size;
    // TODO --> not sure how to handle this yet, might need to iterate over incoming data
  }
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
  virtual void Sort(std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) override
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

  virtual std::vector<TObj> ToVector() override
  {
    std::vector<TObj> returnVector;
    for (const TObj & obj : *this)
    {
      returnVector.push_back(obj);
    }
    return returnVector;
  }

  // virtual void Update(
  //   QueryableIterator<TIterator> first,
  //   QueryableIterator<TIterator> last,
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
  virtual QueryableIterator<TIterator> begin() override
  {
    this->beginIterator = this->items.begin();
    this->type = IteratorType::BeginForward;

    QueryableIterator<TIterator> retVal(this, 0);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TIterator> end() override
  {
    this->endIterator = this->items.end();
    this->type = IteratorType::EndForward;

    QueryableIterator<TIterator> retVal(this, this->size);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TIterator> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->type = IteratorType::BeginReverse;

    QueryableIterator<TIterator> retVal(this, 0);
    return retVal;
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TIterator> rend() override
  {
    this->rendIterator = this->items.rend();
    this->type = IteratorType::EndReverse;

    QueryableIterator<TIterator> retVal(this, this->size);
    return retVal;
  }
};

#endif
