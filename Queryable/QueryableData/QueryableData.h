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
class QueryableData :
  protected QueryableDataIterator<TIterator, TIterable, TArgs...>, // I think I want this protected so it cannot be used directly as an iterator by anyone other than children
  virtual public IQueryableData<TObj, TIterator>
{
  static_assert(can_iterate<TIterable<TObj, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  typedef typename std::vector<TObj>::iterator TVectorIterator;
  // using TForwardIterator = typename TIterable<TObj, TArgs...>::iterator;
  // using TReverseIterator = typename TIterable<TObj, TArgs...>::reverse_iterator;

  // TODO --> consider making this a pointer so data doesn't have to be copied
  TObj value;
  int64_t size = 0;


  void DefaultInitialize()
  {
    this->beginIterator = this->items.begin();
    this->endIterator = this->items.end();
    this->rbeginIterator = this->items.rbegin();
    this->rendIterator = this->items.rend();
    this->size = 0;
    this->index = 0;
  }

  inline QueryableIterator<TIterator> AsCopiedIterator()
  {
    return *static_cast<QueryableIterator<TIterator>*>(this);
  }

  inline QueryableIterator<TIterator> & AsReferenceIterator()
  {
    return *static_cast<QueryableIterator<TIterator>*>(this);
  }

  inline QueryableIterator<TIterator> * AsIterator()
  {
    return static_cast<QueryableIterator<TIterator>*>(this);
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

  inline virtual QueryableIterator<TIterator> & operator++() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: ++this->beginIterator; break;
      case IteratorType::EndForward: ++this->endIterator; break;
      case IteratorType::BeginReverse: ++this->rbeginIterator; break;
      case IteratorType::EndReverse: ++this->rendIterator; break;
    }

    this->index++;

    // not sure if a cast is needed or not
    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TIterator> & operator--() override
  {
    switch (this->type)
    {
      case IteratorType::BeginForward: --this->beginIterator; break;
      case IteratorType::EndForward: --this->endIterator; break;
      case IteratorType::BeginReverse: --this->rbeginIterator; break;
      case IteratorType::EndReverse: --this->rendIterator; break;
    }

    this->index--;

    // not sure if a cast is needed or not
    return this->AsReferenceIterator();
  }

  inline virtual const TIterator & operator*() override
  {
    std::cout << "within real deref 1" << std::endl;
    switch (this->type)
    {
      case IteratorType::BeginForward: return *this->beginIterator;
      case IteratorType::EndForward: return *this->endIterator;
      case IteratorType::BeginReverse: return *this->rbeginIterator;
      case IteratorType::EndReverse: default: return *this->rendIterator;
    }
  }

  inline virtual const TIterator & operator*() const override
  {
    std::cout << "within real deref 2" << std::endl;
    switch (this->type)
    {
      case IteratorType::BeginForward: return *this->beginIterator;
      case IteratorType::EndForward: return *this->endIterator;
      case IteratorType::BeginReverse: return *this->rbeginIterator;
      case IteratorType::EndReverse: default: return *this->rendIterator;
    }
  }

  inline virtual QueryableIterator<TIterator> & operator+(int addend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (this->type)
    {
      case IteratorType::BeginForward: while (addend--) ++this->beginIterator; break;
      case IteratorType::EndForward: while (addend--) ++this->endIterator; break;
      case IteratorType::BeginReverse: while (addend--) ++this->rbeginIterator; break;
      case IteratorType::EndReverse: while (addend--) ++this->rendIterator; break;
    }

    // TODO --> might be dangerous
    this->index += addend;

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TIterator> & operator+=(int addend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (this->type)
    {
      case IteratorType::BeginForward: while (addend--) ++this->beginIterator; break;
      case IteratorType::EndForward: while (addend--) ++this->endIterator; break;
      case IteratorType::BeginReverse: while (addend--) ++this->rbeginIterator; break;
      case IteratorType::EndReverse: while (addend--) ++this->rendIterator; break;
    }

    // TODO --> might be dangerous
    this->index += addend;

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TIterator> & operator-(int subtrahend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (this->type)
    {
      case IteratorType::BeginForward: while (subtrahend--) --this->beginIterator; break;
      case IteratorType::EndForward: while (subtrahend--) --this->endIterator; break;
      case IteratorType::BeginReverse: while (subtrahend--) --this->rbeginIterator; break;
      case IteratorType::EndReverse: while (subtrahend--) --this->rendIterator; break;
    }

    // TODO --> might be dangerous
    this->index -= subtrahend;

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TIterator> & operator-=(int subtrahend) override
  {
    // this is the worse possible way to implement this and should be overriden for random access iterators
    switch (this->type)
    {
      case IteratorType::BeginForward: while (subtrahend--) --this->beginIterator; break;
      case IteratorType::EndForward: while (subtrahend--) --this->endIterator; break;
      case IteratorType::BeginReverse: while (subtrahend--) --this->rbeginIterator; break;
      case IteratorType::EndReverse: while (subtrahend--) --this->rendIterator; break;
    }

    // TODO --> might be dangerous
    this->index -= subtrahend;

    return this->AsReferenceIterator();
  }

  inline virtual QueryableIterator<TIterator> & operator=(const QueryableIterator<TIterator> & value) override
  {
    // TODO --> figure out if we should assign all iterators or just the type-specific iterator
    // switch (this->type)
    // {
    //   case IteratorType::BeginForward: this->beginIterator = value.beginIterator; this->index = 0;break;
    //   case IteratorType::EndForward: this->endIterator = value.endIterator; this->index = this->size; break;
    //   case IteratorType::BeginReverse: this->rbeginIterator = value.rbeginIterator; this->index = 0; break;
    //   case IteratorType::EndReverse: this->rendIterator = value.rendIterator; this->index = this->size; break;
    // }

    // not sure of a good way to do this yet
    this->Clear();
    QueryableIterator<TIterator> cpy = value;
    for (auto val : cpy)
    {
      this->Add(val);
    }

    return this->AsReferenceIterator();
  }

  QueryableData()
  {
    this->DefaultInitialize();
  }
  QueryableData(const TIterable<TObj, TArgs...> & items)
  {
    this->items = items;
    this->index = 0;
    this->DefaultInitialize();

    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->size = this->items.size();
  }
  QueryableData(TIterable<TObj, TArgs...> && items)
  {
    this->items = std::move(items);

    this->DefaultInitialize();
    this->index = 0;
    // TODO --> almost all containers have a size method. Either require that the
    //   items passed in have it or require the size is passed into the constructor
    //   then fix up the child classes having a Count method
    this->value = items.value;
    this->size = this->items.size();
  }
  QueryableData(TVectorIterator first, TVectorIterator last)
  {
    // TODO SFINAE require this constructor
    this->items = TIterable<TObj, TArgs...>(first, last);

    this->DefaultInitialize();
    this->index = 0;
    this->size = this->items.size();
  }
  QueryableData(const QueryableData<TObj, TIterator, TIterable> & data)
  {
    this->items = data.items;

    this->DefaultInitialize();

    this->index = 0;
    this->value = data.value;
    this->size = data.size;
  }
  QueryableData(std::shared_ptr<IQueryableData<TObj, TIterator>> && data)
  {
    this->DefaultInitialize();

    this->index = 0;
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










   // This class has to be the iterator... inheritance won't work because you copy the parent on return which has no data and its own bad implementations














    this->beginIterator = this->items.begin();
    this->index = 0;
    this->type = IteratorType::BeginForward;
    return this->AsCopiedIterator();
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TIterator> end() override
  {
    this->endIterator = this->items.end();
    this->index = this->size;
    this->type = IteratorType::EndForward;
    return this->AsCopiedIterator();
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TIterator> rbegin() override
  {
    this->rbeginIterator = this->items.rbegin();
    this->index = 0;
    this->type = IteratorType::BeginReverse;
    return this->AsCopiedIterator();
  }

  // we return a copy of ourself, so we need to make sure to set our type
  // so that the next time its used, the correct underlying iterator is used
  // may want to consider copy, then set, then move out
  virtual QueryableIterator<TIterator> rend() override
  {
    this->rendIterator = this->items.rend();
    this->index = this->size;
    this->type = IteratorType::EndReverse;
    return this->AsCopiedIterator();
  }
};

#endif
