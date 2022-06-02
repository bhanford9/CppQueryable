#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLE_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "QueryablesForwardDeclarations.hpp"
#include "QueryableData/GroupQueryableData/GroupQueryableDequeData.hpp"
#include "QueryableData/GroupQueryableData/GroupQueryableListData.hpp"
#include "QueryableData/GroupQueryableData/GroupQueryableMultiSetData.hpp"
#include "QueryableData/GroupQueryableData/GroupQueryableSetData.hpp"
#include "QueryableData/GroupQueryableData/GroupQueryableVectorData.hpp"
#include "QueryableData/IQueryableData.hpp"
#include "QueryableData/QueryableDequeData.hpp"
#include "QueryableData/QueryableListData.hpp"
#include "QueryableData/QueryableMultiSetData.hpp"
#include "QueryableData/QueryableSetData.hpp"
#include "QueryableData/QueryableVectorData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableDequeData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableListData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableMultiSetData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableSetData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableVectorData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableDequeData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableListData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableMultiSetData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableSetData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
#include "InternalQueryables/SetInternalQueryable.hpp"
#include "QueryableType.hpp"
#include "SelectBuilders/SelectBuilder.hpp"
#include "Sorters/DequeSorter.hpp"
#include "Sorters/ListSorter.hpp"
#include "Sorters/MultiSetSorter.hpp"
#include "Sorters/SetSorter.hpp"
#include "Sorters/VectorSorter.hpp"
#include "TypeConstraintUtil.hpp"
#include "Utilities/Condition.hpp"
#include "Utilities/Group.hpp"
#include "Utilities/PersistentContainer.hpp"

#include "../CppQueryableTest/Queryable/Performance/Time/Utilities/Duration.hpp"
#include "../CppQueryableTest/Queryable/Performance/Time/Utilities/TimingTypes.hpp"

// Originally wanted this class to be the highest layer where the user interaction would be.
// Now I am seeing that the iterator layer, data layer, and algorithm layer each need some
// of their own specializations between container types. Therefore, going to need an additional
// container wrapper that acts as a single point where users interact
//
// This might be for the best anyway because time/space customizations can be made for each
// container type to help keep things as close to the std lib as possible

template<
  typename TObj,
  template<typename, typename ...> typename TIterable,
  typename ...TArgs>
class InternalQueryable
{
protected:
  // TODO --> consider making this unique and having all of the
  //   QueryableData's implement their own clones
  std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> items;
  PersistentContainer persistentContainer;
  QueryableType type;

public:

  // BEGIN CONSTRUCTORS
  InternalQueryable(QueryableType type = QueryableType::Vector)
  {
    this->type = type;
  }

  InternalQueryable(const InternalQueryable<TObj, TIterable, TArgs...>& queryable)
    : InternalQueryable(queryable.type)
  {
    this->persistentContainer = queryable.persistentContainer;
    this->type = queryable.type;
    this->items = queryable.items;
  }

  InternalQueryable(
    std::shared_ptr<QueryableData<TObj, TIterable, TArgs...>> && queryableData,
    QueryableType type)
  {
    this->items = std::move(queryableData);
    this->type = type;
  }

  InternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TArgs... args);
  InternalQueryable(const TIterable<TObj, TArgs...> & iterable);
  InternalQueryable(TIterable<TObj, TArgs...> && iterable); // TODO --> implement for each subclass
  // END CONSTRUCTORS

  inline QueryableType GetType()
  {
    return this->type;
  }

  inline void Clear()
  {
    this->items.get()->Clear();
  }

  inline void Add(TObj obj)
  {
    this->items.get()->Add(obj);
  }

  inline QueryableIterator<TObj> begin()
  {
    std::cout << "\nInternalQueryable::begin" << std::endl;
    return this->items->begin();
  }

  inline QueryableIterator<TObj> end()
  {
    return this->items->end();
  }

  inline QueryableIterator<TObj> rbegin()
  {
    return this->items->rbegin();
  }

  inline QueryableIterator<TObj> rend()
  {
    return this->items->rend();
  }

  inline std::pair<QueryableIterator<TObj>, QueryableIterator<TObj>> ForwardIterators()
  {
    return {this->begin(), this->end()};
  }

  inline std::pair<QueryableIterator<TObj>, QueryableIterator<TObj>> ReverseIterators()
  {
    return {this->rbegin(), this->ernd()};
  }

  template<
    template<typename, typename, typename ...> typename TInternalQueryable,
    template<typename, typename ...> typename TNewIterable,
    typename ...TNewArgs>
  inline InternalQueryable<TObj, TNewIterable, TNewArgs...> CopyAs(TNewArgs... args)
  {
    // TODO --> it would be nice to ensure that TInternalQueryable inherits InternalQueryable
    //   on the other hand, this should not be accessible to any users
    return TInternalQueryable<TObj, TNewIterable<TObj, TNewArgs...>, TNewArgs...>(
      this->items->begin(),
      this->items->end(),
      args...);
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::deque<TObj, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    std::deque<TObj, TAllocator> newItems(allocator);

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::list<TObj, TAllocator> ToList(TAllocator allocator = {}) const
  {
    std::list<TObj, TAllocator> newItems(allocator);

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  inline std::multiset<TObj, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::multiset<TObj, TLessThan, TAllocator> newItems(lessThan, allocator);

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  inline std::set<TObj, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::set<TObj, TLessThan, TAllocator> newItems(lessThan, allocator);

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TAllocator = std::allocator<TObj>>
  inline std::vector<TObj, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    // probably be better to use the constructor that takes the iterators as parameters
    std::vector<TObj, TAllocator> newItems(allocator);

    std::cout << "\n\n\nGoing into for loop" << std::endl;

    for (TObj item : *this->items.get())
    {
        std::cout << "vector adding: " << item << std::endl;
      newItems.push_back(item);
    }

    return newItems;
  }

  // TODO --> determine best way to return
  template<typename TAllocator = std::allocator<TObj>>
  DequeInternalQueryable<TObj, TAllocator> ToQueryableDeque(TAllocator allocator = {}) const
  {
    std::deque<TObj, TAllocator> copy = this->ToDeque(allocator);
    DequeInternalQueryable<TObj, TAllocator> retValue(copy);
    return retValue;
  }

  template<typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::list, TAllocator> ToQueryableList(TAllocator allocator = {}) const
  {
    std::list<TObj, TAllocator> copy = this->ToList(allocator);
    ListInternalQueryable<TObj, TAllocator> retValue(copy);
    return retValue;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::multiset, TLessThan, TAllocator> ToQueryableMultiSet(
    TLessThan lessThan = {},
    TAllocator allocator = {}) const
  {
    MultiSetInternalQueryable<TObj, TLessThan, TAllocator> retValue(this->ToMultiSet(lessThan, allocator));
    return retValue;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::set, TLessThan, TAllocator> ToQueryableSet(
    TLessThan lessThan = {},
    TAllocator allocator = {}) const
  {
    SetInternalQueryable<TObj, TLessThan, TAllocator> retValue(this->ToSet(lessThan, allocator));
    return retValue;
  }

  template<typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::vector, TAllocator> ToQueryableVector(TAllocator allocator = {}) const
  {
    VectorInternalQueryable<TObj, TAllocator> retValue(this->ToVector(allocator));
    return retValue;
  }

  inline bool IsEmpty()
  {
    return this->items.get()->begin() == this->items.get()->end();
  }

  inline TObj & At(int index) const
  {
    if (index < 0)
    {
      throw std::runtime_error("Index must be greater than zero");
    }

    int i = 0;
    for (TObj & obj : *this->items.get())
    {
      if (index == i++)
      {
        return obj;
      }
    }

    throw std::runtime_error("Specified index was outside the bounds of the container");
  }

  inline size_t Count()
  {
    return this->items.get()->Count();
  }

  inline size_t CountIf(std::function<bool(TObj)> condition) const
  {
    size_t count = 0;

    for (TObj item : *this->items.get())
    {
      if (condition(item))
      {
        count++;
      }
    }

    return count;
  }

  void ForEach(std::function<void(TObj)> action) const
  {
    for (TObj item : *this->items.get())
    {
      action(item);
    }
  }

  // void ForEachRef(std::function<void(TObj&)> action)
  // {
  //   for (TObj & item : *this->items.get())
  //   {
  //     action(item);
  //   }
  // }

  // TODO --> no return necessary
  virtual InternalQueryable<TObj, TIterable, TArgs...> * Where(std::function<bool(const TObj &)> condition) = 0;

  // InternalQueryable<TObj, TIterable, TArgs...> WhereCopy(std::function<bool(TObj)> condition, QueryableType returnType = QueryableType::Default)
  // {
  //   InternalQueryable<TObj, TIterable, TArgs...> returnValue(returnType);
  //
  //   for (TObj item : *this->items.get())
  //   {
  //     if (condition(item))
  //     {
  //       returnValue.Add(item);
  //     }
  //   }
  //
  //   return returnValue;
  // }

  inline TObj First(std::function<bool(TObj)> condition)
  {
    for (TObj item : *this->items.get())
    {
      if (condition(item))
      {
        return item;
      }
    }

    throw std::runtime_error("No item fitting the condition was found.");
  }

  inline TObj First()
  {
    if (!this->IsEmpty())
    {
      return *this->items.get()->begin();
    }

    throw std::runtime_error("Cannot get first item of empty collection.");
  }

  inline TObj Last(std::function<bool(TObj)> condition)
  {
    for (auto it = this->items.get()->rbegin(); it != this->items.get()->rend(); ++it)
    {
      if (condition(*it))
      {
        return *it;
      }
    }

    throw std::runtime_error("No item fitting the condition was found.");
  }

  inline TObj Last()
  {
    if (!this->IsEmpty())
    {
      return *this->items.get()->rbegin();
    }

    throw std::runtime_error("Cannot get last item of empty collection.");
  }

  // Need to get Take and Skip methods into deferred actions similar to the
  // way that Where and Select work
  // InternalQueryable<TObj> Take(int count)
  // {
  //   int i = 0;
  //   std::vector<TObj> copy = this->ToVector();
  //   this->Clear();
  //
  //   for (TObj item : copy)
  //   {
  //     this->items.get()->Add(item);
  //     if (i == count)
  //     {
  //       break;
  //     }
  //   }
  // }
  //
  // InternalQueryable<TObj> * TakeWhile(std::function<bool(TObj)> doTake)
  // {
  //   // consider optimization of doing this without duplicate vector
  //   // may be better/worse depending on container size
  //   std::vector<TObj> copy = this->ToVector();
  //   this->Clear();
  //
  //   for (TObj item : copy)
  //   {
  //     if (doTake(item))
  //     {
  //       this->items.get()->Add(item);
  //     }
  //     else
  //     {
  //       break;
  //     }
  //   }
  //
  //   return this;
  // }
  //
  // InternalQueryable<TObj>* Skip(int count)
  // {
  //   if (count < 0)
  //   {
  //     return this->Take(this->Count() + count);
  //   }
  //
  //   int localSize = this->Count();
  //   if (count > localSize)
  //   {
  //     count = localSize;
  //   }
  //
  //   QueryableVectorData<TObj> copy = this->items.get()->ToVector();
  //   this->Clear();
  //
  //   int i = 0;
  //   for (auto it = copy.begin(); it != copy.end(); ++it)
  //   {
  //     if (this->items.get()->PassesCondition(*it) && count <= i++)
  //     {
  //       this->items.get()->Add(*it);
  //     }
  //   }
  //
  //   return this;
  // }
  //
  // InternalQueryable<TObj>* SkipWhile(std::function<bool(TObj)> doSkip)
  // {
  //   // the skip and take methods need to be thought through
  //   // to come up with better space/time complexities
  //   int toDelete = 0;
  //
  //   for (TObj item : *this->items.get())
  //   {
  //     if (!doSkip(item))
  //     {
  //       break;
  //     }
  //
  //     toDelete++;
  //   }
  //
  //   InternalQueryable<TObj>* retval = this->Skip(toDelete);
  //   return retval;
  // }

  // TODO these can be done with iterators instead
  // inline bool Equal(const TIterable<TObj, TArgs...> & collection) const
  // {
  //   return this->Equal(collection, collection.size());
  // }
  //
  // inline bool Equal(
  //   const TIterable<TObj, TArgs...> & collection,
  //   const std::function<bool(TObj, TObj)> & areEqual) const
  // {
  //   return this->Equal(collection, collection.size(), areEqual);
  // }
  //
  // // forward_list does not contain size() method and don't want to require it
  // // it would be faster to do a pre-check for containers that do have constant size methods
  // inline bool Equal(const TIterable<TObj, TArgs...> & collection, size_t collectionSize) const
  // {
  //   static_assert(is_equatable<TObj>::value, "Type must be equatable");
  //
  //   bool selfEmpty = this->items->end() == this->items->begin();
  //   bool otherEmpty = collection.end() == collection.begin();
  //
  //   if ((selfEmpty && !otherEmpty) || (!selfEmpty && otherEmpty))
  //   {
  //     return false;
  //   }
  //
  //   auto localIterator = this->items->begin();
  //   for (TObj item : collection)
  //   {
  //     if (localIterator == this->items->end() || !(*localIterator == item))
  //     {
  //       return false;
  //     }
  //
  //     ++localIterator;
  //   }
  //
  //   if (localIterator != this->items->end())
  //   {
  //     return false;
  //   }
  //
  //   return true;
  // }
  //
  // inline bool Equal(
  //   const TIterable<TObj, TArgs...> & collection,
  //   size_t collectionSize,
  //   const std::function<bool(TObj, TObj)> & areEqual) const
  // {
  //   bool selfEmpty = this->items->end() == this->items->begin();
  //   bool otherEmpty = collection.end() == collection.begin();
  //
  //   if ((selfEmpty && !otherEmpty) || (!selfEmpty && otherEmpty))
  //   {
  //     return false;
  //   }
  //
  //   auto localIterator = this->items->begin();
  //   for (TObj item : collection)
  //   {
  //     if (localIterator == this->items->end() || !areEqual(*localIterator, item))
  //     {
  //       return false;
  //     }
  //
  //     ++localIterator;
  //   }
  //
  //   if (localIterator != this->items->end())
  //   {
  //     return false;
  //   }
  //
  //   return true;
  // }

  // with preserveFilter true, you can do the following:
  //   collection.Where(x => x.IsValid).Concat(otherItems, true);
  //
  // and the Where condition will be executed on the incoming items to prevent
  // unwanted items from being added without needing to immediately apply the
  // where condition to the rest of the inital collection
  // template<template<typename...> typename TContainer>
  // InternalQueryable<TObj, TContainer>* Concat(TContainer<TObj> collection, bool preserveFilter = false)
  // {
  //   for (TObj obj : collection)
  //   {
  //     if (!preserveFilter || this->items.get()->PassesCondition(obj))
  //     {
  //       this->items.get()->Add(obj);
  //     }
  //   }
  //
  //   return this;
  // }

  inline double Sum(std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    double sum = 0;

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
    }

    return sum;
  }
  inline size_t Sum(std::function<size_t(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    size_t sum = 0;

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
    }

    return sum;
  }

  inline double Average(std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    double sum = 0;
    size_t count = 0;

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
      count++;
    }

    return count > 0 ? sum / count : 0;
  }

  inline double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    double sum  = 0;
    size_t count = 0;

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
      count++;
    }

    return divisor(sum, count);
  }

  template<typename T>
  inline TObj MaxItem(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T maxValue = T();
    TObj maxItem = TObj();

    for (TObj item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (isFirst)
      {
        isFirst = false;
        maxValue = newValue;
        maxItem = item;
      }
      else if (maxValue < newValue)
      {
        maxValue = newValue;
        maxItem = item;
      }
    }

    return maxItem;
  }

  template<typename T>
  inline T Max(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MaxItem(retrieveValue));
  }

  inline TObj Max() const
  {
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    TObj maxItem = TObj();

    for (TObj item : *this->items.get())
    {
      if (isFirst)
      {
        isFirst = false;
        maxItem = item;
      }
      else if (maxItem < item)
      {
        maxItem = item;
      }
    }

    return maxItem;
  }

  template<typename T>
  inline T Max(std::function<T(TObj)> retrieveValue, T startSeed) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T max = startSeed;

    for (TObj item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (max < newValue)
      {
        max = newValue;
      }
    }

    return max;
  }

  inline TObj Max(TObj startSeed) const
  {
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");

    TObj max = startSeed;

    for (TObj item : *this->items.get())
    {
      if (max < item)
      {
        max = item;
      }
    }

    return max;
  }

  template<typename T>
  inline TObj MinItem(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T minValue = T();
    TObj minItem = TObj();

    for (TObj item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (isFirst)
      {
        isFirst = false;
        minValue = newValue;
        minItem = item;
      }
      else if (newValue < minValue)
      {
        minValue = newValue;
        minItem = item;
      }
    }

    return minItem;
  }

  template<typename T>
  inline T Min(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MinItem(retrieveValue));
  }

  inline TObj Min() const
  {
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    TObj minItem = TObj();

    for (TObj item : *this->items.get())
    {
      if (isFirst)
      {
        isFirst = false;
        minItem = item;
      }
      else if (item < minItem)
      {
        minItem = item;
      }
    }

    return minItem;
  }

  template<typename T>
  inline T Min(std::function<T(TObj)> retrieveValue, T startSeed) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T min = startSeed;

    for (TObj item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (newValue < min)
      {
        min = newValue;
      }
    }

    return min;
  }

  inline TObj Min(TObj startSeed) const
  {
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");

    TObj min = startSeed;

    for (TObj item : *this->items.get())
    {
      if (item < min)
      {
        min = item;
      }
    }

    return min;
  }

  template<typename T>
  inline T Range(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    static_assert(is_subtractable<T>::value, "Type must overload subtraction operator");

    bool isFirst = true;
    T max;
    T min;

    for (TObj item : *this->items.get())
    {
      T value = retrieveValue(item);

      if (isFirst)
      {
        isFirst = false;
        max = value;
        min = value;
      }

      if (value < min)
      {
        min = value;
      }

      if (max < value)
      {
        max = value;
      }
    }

    return max - min;
  }

  inline double Range(std::function<double(TObj)> retrieveValue = [](TObj value) { return value; }) const
  {
    bool isFirst = true;
    double max = 0.0;
    double min = 0.0;

    for (TObj item : *this->items.get())
    {
      double value = retrieveValue(item);

      if (isFirst)
      {
        isFirst = false;
        max = value;
        min = value;
      }

      if (value < min)
      {
        min = value;
      }

      if (max < value)
      {
        max = value;
      }
    }

    return max - min;
  }

  // TODO : templates are supposed to be faster than std::function. will require static asserts though
  inline bool Any(std::function<bool(TObj)> condition) const
  {
    for (auto item = this->items->begin(); item != this->items->end(); ++item)
    {
      if (condition(*item))
      {
        return true;
      }
    }

    return false;
  }

  // TODO : templates are supposed to be faster than std::function. will require static asserts though
  inline bool All(std::function<bool(TObj)> condition) const
  {
    for (TObj item : *this->items.get())
    {
      if (!condition(item))
      {
        return false;
      }
    }

    return true;
  }

  template<typename T, typename ...TNewArgs>
  void Select(
    std::function<T(TObj)> retrieveValue,
    SelectBuilder<TObj, T, TIterable, TNewArgs...> * selectBuilder,
    TNewArgs... iterableParameters)
  {
    selectBuilder->Build(this->items, retrieveValue, iterableParameters...);
  }

  inline bool Contains(const TObj & item) const
  {
    static_assert(is_equatable<TObj>::value, "Item must be equatable");

    for (const TObj & localItem : *this->items.get())
    {
      if (localItem == item)
      {
        return true;
      }
    }

    return false;
  }

  // Things to note
  //   1. [multi]sets must use a copy of storage
  //   1.1. this is due to the sorting algorithm being type dependent within the container
  //   2. this should not be used for [multi]sets if the comparator is the same it was built with
  //   3. all other types use their built in optimized sorting algorithms
  //   4. would be faster if std::function could be replaced by type parameter, but then inheritance wouldn't work
  template<
    typename TSortOutput,
    typename TLessThan = std::less<TObj>>
  TSortOutput Sort(
    Sorter<TObj, TSortOutput, TLessThan> * sorter,
    TLessThan lessThan = {})
  {
    return sorter->Sort(this->items->begin(), this->items->end(), lessThan);
  }

  // TODO --> using a template instead of std::function is probably faster
  // These are dangerous methods due to not having an Allocator specified at the
  // class level and needing one in the lower layers. I'm not sure how to fix it yet
  // template<
  //   typename TSortOutput,
  //   typename T = TObj,
  //   typename TLessThan = std::less<T>>
  // TSortOutput OrderBy(
  //   Sorter<TObj, TIterable, TSortOutput, TArgs...> & sorter,
  //   std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
  //   TLessThan lessThan = {})
  // {
  //   return this->Sort(
  //     sorter,
  //     [&](TObj a, TObj b) { return lessThan(retrieveValue(a), retrieveValue(b)); });
  // }
  //
  // template<
  //   typename TSortOutput,
  //   typename T = TObj,
  //   typename TLessThan = std::less<T>>
  // TSortOutput OrderByDescending(
  //   Sorter<TObj, TIterable, TSortOutput, TArgs...> & sorter,
  //   std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
  //   TLessThan lessThan = {})
  // {
  //   return this->Sort(
  //       sorter,
  //       [&](TObj a, TObj b) { return !lessThan(retrieveValue(a), retrieveValue(b)); });
  // }

  // template<typename TLessThan, typename TAllocator>
  // SortedInternalQueryable<TObj, TIterable, std::function<bool(TObj, TObj)>, TAllocator> & ReSort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; })
  // {
  //   std::shared_ptr<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>>, TLessThan, TAllocator>> sorter;
  //
  //   switch (this->type)
  //   {
  //     case QueryableType::MultiSet:
  //     {
  //       MultiSetSorter<TObj, TLessThan, TAllocator> multiSetSorter;
  //       sorter = std::make_shared<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>>, TLessThan, TAllocator>>(multiSetSorter);
  //     }
  //     case QueryableType::Set:
  //     {
  //       SetSorter<TObj, TLessThan, TAllocator> setSorter;
  //       sorter = std::make_shared<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>>, TLessThan, TAllocator>>(setSorter);
  //     }
  //     default:
  //       throw std::runtime_error("ReOrderBy, ReOrderByDescending and ReSort are only meant for containers that are ordered by default. For all other containers use OrderBy, OrderByDescending or Sort");
  //       break;
  //   }
  //
  //   // I think this is the only thing keeping us from using IQueryableData everywhere instead of QueryableData, and its not even working....
  //   SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>> setOutput = this->items->Sort(*sorter);
  //   // This return does not work due to the SortedQueryable being abstract.
  //   // I could have the SortedQueryable implement all abstract methods and pass the execution to child virtual methods,
  //   // but I don't like needing the Re-Sort method anyway, so might try to find another way to handle this instead.
  //   return { setOutput.Get() };
  // }
  //
  // template<
  //   typename T = TObj,
  //   typename TLessThan = std::less<T>,
  //   typename TAllocator = std::allocator<TObj>>
  // SortedInternalQueryable<TObj, TIterable, TLessThan, TAllocator> & ReOrderBy(
  //   std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
  //   TLessThan lessThan = {})
  // {
  //   return { this->ReSort<TLessThan, TAllocator>([&](TObj a, TObj b) { return lessThan(retrieveValue(a), retrieveValue(b)); }) };
  // }
  //
  // template<
  //   typename T = TObj,
  //   typename TLessThan = std::less<T>,
  //   typename TAllocator = std::allocator<TObj>>
  // SortedInternalQueryable<TObj, TIterable, TLessThan, TAllocator> & ReOrderByDescending(
  //   std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
  //   TLessThan lessThan = {})
  // {
  //   return { this->ReSort<TLessThan, TAllocator>([&](TObj a, TObj b) { return !lessThan(retrieveValue(a), retrieveValue(b)); }) };
  // }

  // TODO --> make this virtual? like Where()
  template<
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<TObj>,
    typename TAllocator = std::allocator<TObj>,
    typename ...TExceptionArgs>
  void Except(
    const TExceptions<TObj, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    static_assert(can_iterate<TExceptions<TObj, TExceptionArgs...>>::value, "Class must be able to be iterated over");

    // O(nlogn) minimize and sort the exceptions coming in
    std::set<TObj, TLessThan, TAllocator> sortedExceptions(
      exceptions.begin(),
      exceptions.end(),
      lessThan,
      allocator);

    // O(m) make a copy of current items
    TIterable<TObj, TArgs...> copy(this->items->begin(), this->items->end());

    // O(m) clear current items (may be better to re-instantiate instead?)
    this->items->Clear();

    auto last = sortedExceptions.end();
    // O(mlogn) add back any that don't exist within exceptions
    for (TObj item : copy)
    {
      if (sortedExceptions.find(item) == last)
      {
        this->items->Add(item);
      }
    }

    // Total: O(nlogn + m + m + mlogn) ~= O(nlogn + 2m + mlogn) ~= O((n + m)logn + 2m) ~= O(max(n, m)logn)
    // There are some instances where O(nm) would be faster
    //
    // Another option is to sort both and only iterate over both once
    // O(nlogn + mlogm + max(n, m))
    //
    // Probably some scenarios where removing is better than creation a full new copy too





    // TODO --> if  nXm < max(nlog(n), mlog(m)) then sorting is not worth it
    // TODO --> don't call toVector if the type is already a random access iterator
    // std::vector<TObj> localSorted = this->Sort(comparator).ToVector();
    // std::vector<TObj> inputSorted = collection->ToVector();
    // std::sort(inputSorted.begin(), inputSorted.end(), comparator);
    //
    // int localCount = localSorted.size();
    // int inputCount = inputSorted.size();
    //
    // if (localCount <= 0 || inputCount <= 0)
    // {
    //   return *this;
    // }
    //
    // std::vector<TObj> result;
    // int localIndex = 0;
    // int inputIndex = 0;
    //
    // std::function<bool(TObj, TObj)> equal = [&](TObj a, TObj b)
    // {
    //   return !comparator(a, b) && !comparator(b, a);
    // };
    //
    // while (localIndex < localCount && inputIndex < inputCount)
    // {
    //   TObj localItem = localSorted[localIndex];
    //   TObj inputItem = inputSorted[inputIndex];
    //
    //   if (equal(localItem, inputItem))
    //   {
    //     TObj equalValue = localItem;
    //
    //     while (++localIndex < localCount && equal(equalValue, localSorted[localIndex]));
    //     while (++inputIndex < inputCount && equal(equalValue, inputSorted[inputIndex]));
    //   }
    //   else if (comparator(localItem, inputItem))
    //   {
    //     result.push_back(localItem);
    //     localIndex++;
    //   }
    //   else
    //   {
    //     inputIndex++;
    //   }
    // }
    //
    // // gather leftovers
    // for (; localIndex < localCount; localIndex++)
    // {
    //   if (!equal(localSorted[localIndex], inputSorted[inputCount - 1]))
    //   {
    //     result.push_back(localSorted[localIndex]);
    //   }
    // }
    //
    // // this is a linear update. Constant update or updating within the previous
    // // looping would be ideal
    // // this->items.get()->Update(result.begin(), result.end());
    //
    // return *this;
  }

  // TODO: changing std::function to a templated member is supposed to be faster
  // TODO: not sure I like this implementation:
  //   - No guarantee that we can create a T (i.e., default constructor)
  template<typename T = TObj>
  inline T Aggregate(const std::function<T(T, TObj)> & accumulate, T * seed = NULL)
  {
    T aggregatedValue;

    if (seed != NULL)
    {
      aggregatedValue = *seed;
    }

    for (TObj item : *this->items.get())
    {
      aggregatedValue = accumulate(aggregatedValue, item);
    }

    return aggregatedValue;
  }

  // TODO: changing std::function to a templated member is supposed to be faster
  template<typename TFinalized, typename T = TObj>
  inline TFinalized Aggregate(
    const std::function<T(T, TObj)> & accumulate,
    const std::function<TFinalized(T)> & finalizer,
    T * seed = NULL)
  {
    return finalizer(this->Aggregate<T>(accumulate, seed));
  }

  // template<
  //   typename TJoinObj,
  //   typename TJoinOn,
  //   typename TResult>
  // InternalQueryable<TResult> & Join(
  //   InternalQueryable<TJoinObj> & collection,
  //   std::function<TJoinOn(TObj)> getLocalJoinOn,
  //   std::function<TJoinOn(TJoinObj)> getInputJoinOn,
  //   std::function<TResult(TObj, TJoinObj)> createFrom,
  //   std::function<bool(TResult, TResult)> outCompare,
  //   QueryableType returnType = QueryableType::Default)
  // {
  //   static_assert(is_less_comparable<TJoinOn>::value, "Type must be 'less than' comparable");
  //   typedef InternalQueryable<TResult> TReturn;
  //
  //   QueryableType type = returnType == QueryableType::Default ? this->type : returnType;
  //   std::shared_ptr<TReturn> data = std::make_shared<TReturn>(type, outCompare);
  //   this->persistentContainer.Set(data);
  //   std::shared_ptr<TReturn> result = this->persistentContainer.GetAs<TReturn>();
  //
  //   // Sort each collection on passed in key getters                             ( + time complexity: nlog(n) )
  //   //   this allows us to only need to fully iterate over each collection once  ( + time complexity: n )
  //   //   and chunks of non-joinable data can be easily bypassed                  ( + non-generalizable benefit )
  //   // Change inner collection to vector to gaurantee constant time indexing     ( - requires extra space )
  //   //   may want to only do this if collection type does not have constant time indexing
  //   this->OrderBy(getLocalJoinOn);
  //   std::vector<TJoinObj> inputSorted = collection.OrderBy(getInputJoinOn).ToVector();
  //   int inputSize = inputSorted.size();
  //
  //   if (inputSize > 0)
  //   {
  //     int inputIndex = 0;
  //
  //     for (TObj localItem : *this->items.get())
  //     {
  //       TJoinOn localValue;
  //       TJoinOn inputValue;
  //
  //       do
  //       {
  //         TJoinObj inputItem = inputSorted[inputIndex];
  //
  //         localValue = getLocalJoinOn(localItem);
  //         inputValue = getInputJoinOn(inputItem);
  //
  //         if (localValue == inputValue)
  //         {
  //           int sameValueIndex = inputIndex;
  //           while (sameValueIndex < inputSize)
  //           {
  //             TJoinOn nextValue = getInputJoinOn(inputSorted[sameValueIndex]);
  //
  //             // if they're not equal then move on
  //             if ((nextValue < inputValue) || (inputValue < nextValue))
  //             {
  //               break;
  //             }
  //
  //             result.get()->Add(createFrom(localItem, inputSorted[sameValueIndex++]));
  //           }
  //         }
  //
  //         if (inputValue <= localValue)
  //         {
  //           inputIndex++;
  //         }
  //
  //       } while (inputValue < localValue && inputIndex < inputSize);
  //     }
  //   }
  //
  //   return *result.get();
  // }

  // template<typename TOut>
  // InternalQueryable<TOut>* Cast()
  // {
  //   // TODO --> make this a deferred action
  //   typedef InternalQueryable<TOut> TReturn;
  //   std::shared_ptr<TReturn> data = std::make_shared<TReturn>(this->type);
  //   this->persistentContainer.Set(data);
  //   std::shared_ptr<TReturn> result = this->persistentContainer.GetAs<TReturn>();
  //
  //   for (TObj item : *this->items.get())
  //   {
  //     result.get()->Add(static_cast<TOut>(item));
  //   }
  //
  //   return result.get();
  // }


//   template<typename TKey, typename TData = TObj>
//   InternalQueryable<Group<TKey, TObj>> GroupBy(
//     std::function<TKey(TObj)> getKey,
//     QueryableType storageType = QueryableType::Default,
//     std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
//     std::function<bool(TData, TData)> dataCompare = [](TData a, TData b) { return a < b; })
//   {
//     QueryableType type = storageType == QueryableType::Default ? this->type : storageType;
//     InternalQueryable<Group<TKey, TObj>> queryableGroups(type);
//
//     for (TObj item : *this->items.get())
//     {
//       TKey key = getKey(item);
//
//       if (!queryableGroups.Any([&](Group<TKey, TObj> group) { return group.HasKey(key); }))
//       {
//         switch (type)
//         {
//           case QueryableType::Deque:
//             queryableGroups.Add(GroupQueryableDequeData<TKey, TData>(key, type, keyCompare));
//             break;
//           case QueryableType::List:
//             queryableGroups.Add(GroupQueryableListData<TKey, TData>(key, type, keyCompare));
//             break;
//           case QueryableType::MultiSet:
//             queryableGroups.Add(GroupQueryableMultiSetData<TKey, TData>(key, type, keyCompare, dataCompare));
//             break;
//           case QueryableType::Set:
//             queryableGroups.Add(GroupQueryableSetData<TKey, TData>(key, type, keyCompare, dataCompare));
//             break;
//           case QueryableType::Vector:
//           default:
//             queryableGroups.Add(GroupQueryableVectorData<TKey, TData>(key, type, keyCompare));
//             break;
//         }
//       }
//
//       queryableGroups
//         .First([&](Group<TKey, TObj> group) { return group.HasKey(key); })
//         .Add(item);
//     }
//
//     queryableGroups.Sort([](Group<TKey, TObj> a, Group<TKey, TObj> b) { return a < b; });
//
//     return queryableGroups;
//   }
};

#endif
