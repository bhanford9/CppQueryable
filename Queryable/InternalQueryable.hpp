#ifndef CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_INTERNALQUERYABLE_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "QueryablesForwardDeclarations.hpp"
#include "QueryableData/IQueryableData.hpp"
#include "QueryableData/QueryableDequeData.hpp"
#include "QueryableData/QueryableListData.hpp"
#include "QueryableData/QueryableMapData.hpp"
#include "QueryableData/QueryableMultiSetData.hpp"
#include "QueryableData/QueryableSetData.hpp"
#include "QueryableData/QueryableVectorData.hpp"
#include "QueryableData/SelectQueryableData/SelectQueryableData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableDequeData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableListData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableMultiSetData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableSetData.hpp"
#include "QueryableData/WhereQueryableData/WhereQueryableVectorData.hpp"
#include "InternalQueryables/DequeInternalQueryable.hpp"
#include "InternalQueryables/ListInternalQueryable.hpp"
#include "InternalQueryables/MapInternalQueryable.hpp"
#include "InternalQueryables/MultiSetInternalQueryable.hpp"
#include "InternalQueryables/SetInternalQueryable.hpp"
#include "InternalQueryables/VectorInternalQueryable.hpp"
#include "QueryableType.hpp"
#include "Sorters/DequeSorter.hpp"
#include "Sorters/ListSorter.hpp"
#include "Sorters/VectorSorter.hpp"
#include "TypeConstraintUtil.hpp"
#include "Utilities/Casting.hpp"
#include "Utilities/Condition.hpp"
#include "Utilities/Grouping.hpp"
#include "Utilities/IWhileCondition.hpp"
#include "Utilities/PersistentContainer.hpp"
#include "Utilities/WhileCondition.hpp"

#include "../CppQueryableTest/Queryable/Performance/Time/Utilities/Duration.hpp"
#include "../CppQueryableTest/Queryable/Performance/Time/Utilities/TimingTypes.hpp"

// Originally wanted this class to be the highest layer where the user interaction would be.
// Now I am seeing that the iterator layer, data layer, and algorithm layer each need some
// of their own specializations between container types. Therefore, going to need an additional
// container wrapper that acts as a single point where users interact
//
// This might be for the best anyway because time/space customizations can be made for each
// container type to help keep things as close to the std lib as possible

// With the rearchitecture to support Maps, I think TArgs is going to be vital at this layer
// I am hoping it will be able to hold more than just the TCompare and TAllocator now
// For Vector, TArgs will hold:
//   TIterating: TStoring
//   TAllocator: TAllocator
// For Set, TArgs will hold:
//   TIterating: TStoring
//   TCompare: TCompare
//   TAllocator: TAllocator
// For Map, TArgs will hold:
//   TIterating: std::pair<TKey, TValue>
//   TValue: TValue
//   TCompare: TKeyCompare
//   TAllocator: TPairAllocator
//
// Maps are a twisted mess in comparison, but it should end up working nicely 
//
// Looks like this wont work because the thing we are iterating over is not TStoring, it is TIterating
//   When we have a functor passed in, it needs to take the type of TIterating, not TStoring
// This is going to cause the templated TIterating to propogate all the way up which is going to be ugly
// The aliases can clean it up, but the return types of the methods will still be of the type 
//   IBaseQueryable<TStoring, TIterable, TIterating, TArgs...>
template<
  typename TStoring,
  template<typename, typename ...> typename TIterable,
  typename TIterating,
  typename ...TArgs>
class InternalQueryable
{
protected:
  // TODO --> consider making this unique and having all of the
  //   QueryableData's implement their own clones
  std::shared_ptr<QueryableData<TStoring, TIterable, TIterating, TArgs...>> items;
  PersistentContainer persistentContainer;
  QueryableType type;

public:

  InternalQueryable(QueryableType type = QueryableType::Vector)
  {
    this->type = type;
  }

  InternalQueryable(const InternalQueryable<TStoring, TIterable, TIterating, TArgs...> & queryable)
    : InternalQueryable(queryable.type)
  {
    this->persistentContainer = queryable.persistentContainer;
    this->type = queryable.type;
    this->items = queryable.items;
  }

  InternalQueryable(
    std::shared_ptr<QueryableData<TStoring, TIterable, TIterating, TArgs...>> && queryableData,
    QueryableType type)
  {
    this->items = std::move(queryableData);
    this->type = type;
  }

  // For std::map, we need TStoring to be a std::pair when we iterate, by it needs to come into here as std::map<TKey, TValue
  // This will likely mean that these need to stop being possible and instead make them static methods for each underlying type
  // The same will need to be done for QueryableData
  InternalQueryable(const QueryableIterator<TIterating> & first, const QueryableIterator<TIterating> & last, TArgs... args);

  inline QueryableType GetType()
  {
    return this->type;
  }

  inline InternalQueryable<TStoring, TIterable, TIterating, TArgs...> & GetRealized()
  {
    // TODO --> I think I can switch to returning this as QueryableData so casting is not necessary
    std::shared_ptr<IQueryableData<TIterating>> realized = this->items->GetRealizedQueryableData();
    this->items = FutureStd::reinterpret_pointer_cast<QueryableData<TStoring, TIterable, TIterating, TArgs...>>(
      this->items->GetRealizedQueryableData());
    return *this;
  }

  inline void Clear()
  {
    this->items.get()->Clear();
  }

  // TODO --> this may need to be protected for internal use only
  inline void Add(TIterating obj)
  {
    this->items.get()->Add(obj);
  }

  template<typename TAllocator>
  TAllocator GetAllocator()
  {
    return this->items->template GetAllocator<TAllocator>();
  }

  template<typename TLessThan>
  TLessThan GetValueCompare()
  {
    return this->items->GetValueCompare();
  }

  inline QueryableIterator<TIterating> begin()
  {
    // std::cout << "\nInternalQueryable::begin" << std::endl;
    return this->items->begin();
  }

  inline QueryableIterator<TIterating> end()
  {
    return this->items->end();
  }

  inline QueryableIterator<TIterating> rbegin()
  {
    return this->items->rbegin();
  }

  inline QueryableIterator<TIterating> rend()
  {
    return this->items->rend();
  }

  inline std::pair<QueryableIterator<TIterating>, QueryableIterator<TIterating>> ForwardIterators()
  {
    return {this->begin(), this->end()};
  }

  inline std::pair<QueryableIterator<TIterating>, QueryableIterator<TIterating>> ReverseIterators()
  {
    return {this->rbegin(), this->ernd()};
  }

  template<typename TAllocator = std::allocator<TIterating>>
  inline std::deque<TIterating, TAllocator> ToDeque(TAllocator allocator = {}) const
  {
    std::deque<TIterating, TAllocator> newItems(allocator);

    for (TIterating item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TAllocator = std::allocator<TIterating>>
  inline std::list<TIterating, TAllocator> ToList(TAllocator allocator = {}) const
  {
    std::list<TIterating, TAllocator> newItems(allocator);

    for (TIterating item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<
    typename TKey,
    typename TValue = TStoring,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  inline std::map<TKey, TValue, TLessThan, TAllocator> ToMap(
    std::function<TKey(TIterating)> getKey,
    std::function<TValue(TIterating)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    std::map<TKey, TValue, TLessThan, TAllocator> newItems(keyCompare, pairAllocator);

    for (TIterating item : *this->items.get())
    {
      newItems[getKey(item)] = getValue(item);
    }
    
    return newItems;
  }

  template<typename TLessThan = std::less<TIterating>, typename TAllocator = std::allocator<TIterating>>
  inline std::multiset<TIterating, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::multiset<TIterating, TLessThan, TAllocator> newItems(lessThan, allocator);

    for (TIterating item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TLessThan = std::less<TIterating>, typename TAllocator = std::allocator<TIterating>>
  inline std::set<TIterating, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}, TAllocator allocator = {}) const
  {
    std::set<TIterating, TLessThan, TAllocator> newItems(lessThan, allocator);

    for (TIterating item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TAllocator = std::allocator<TIterating>>
  inline std::vector<TIterating, TAllocator> ToVector(TAllocator allocator = {}) const
  {
    // probably be better to use the constructor that takes the iterators as parameters
    std::vector<TIterating, TAllocator> newItems(allocator);

    for (TIterating item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  // TODO --> determine best way to return
  template<typename TAllocator = std::allocator<TStoring>>
  DequeInternalQueryable<TStoring, TAllocator> ToQueryableDeque(TAllocator allocator = {}) const
  {
    std::deque<TStoring, TAllocator> copy = this->ToDeque(allocator);
    DequeInternalQueryable<TStoring, TAllocator> retValue(copy);
    return retValue;
  }

  template<typename TAllocator = std::allocator<TStoring>>
  ListInternalQueryable<TStoring, TAllocator> ToQueryableList(TAllocator allocator = {}) const
  {
    std::list<TStoring, TAllocator> copy = this->ToList(allocator);
    ListInternalQueryable<TStoring, TAllocator> retValue(copy);
    return retValue;
  }

  template<
    typename TKey,
    typename TValue = TStoring,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  inline MapInternalQueryable<TKey, TValue, TLessThan, TAllocator> ToQueryableMap(
    std::function<TKey(TStoring)> getKey,
    std::function<TValue(TStoring)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    MapInternalQueryable<TKey, TValue, TLessThan, TAllocator> retValue(this->ToMap(getKey, getValue, keyCompare, pairAllocator));
    return retValue;
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  MultiSetInternalQueryable<TStoring, TLessThan, TAllocator> ToQueryableMultiSet(
    TLessThan lessThan = {},
    TAllocator allocator = {}) const
  {
    MultiSetInternalQueryable<TStoring, TLessThan, TAllocator> retValue(this->ToMultiSet(lessThan, allocator));
    return retValue;
  }

  template<typename TLessThan = std::less<TStoring>, typename TAllocator = std::allocator<TStoring>>
  SetInternalQueryable<TStoring, TLessThan, TAllocator> ToQueryableSet(
    TLessThan lessThan = {},
    TAllocator allocator = {}) const
  {
    SetInternalQueryable<TStoring, TLessThan, TAllocator> retValue(this->ToSet(lessThan, allocator));
    return retValue;
  }

  template<typename TAllocator = std::allocator<TStoring>>
  VectorInternalQueryable<TStoring, TAllocator> ToQueryableVector(TAllocator allocator = {}) const
  {
    VectorInternalQueryable<TStoring, TAllocator> retValue(this->ToVector(allocator));
    return retValue;
  }

  inline bool IsEmpty()
  {
    return this->items.get()->begin() == this->items.get()->end();
  }

  inline TIterating & At(int index) const
  {
    if (index < 0)
    {
      throw std::runtime_error("Index must be greater than zero");
    }

    int i = 0;
    for (TIterating & obj : *this->items.get())
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

  inline size_t CountIf(std::function<bool(TIterating)> condition) const
  {
    size_t count = 0;

    for (TIterating item : *this->items.get())
    {
      if (condition(item))
      {
        count++;
      }
    }

    return count;
  }

  void ForEach(std::function<void(const TIterating &)> action) const
  {
    for (const auto & item : *this->items.get())
    {
      action(item);
    }
  }

  virtual void Where(std::function<bool(const TIterating &)> condition) = 0;

  inline TIterating First(std::function<bool(TIterating)> condition)
  {
    for (TIterating item : *this->items.get())
    {
      if (condition(item))
      {
        return item;
      }
    }

    throw std::runtime_error("No item fitting the condition was found.");
  }

  inline TIterating First()
  {
    if (!this->IsEmpty())
    {
      return *this->items.get()->begin();
    }

    throw std::runtime_error("Cannot get first item of empty collection.");
  }

  inline TIterating Last(std::function<bool(TIterating)> condition)
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

  inline TIterating Last()
  {
    if (!this->IsEmpty())
    {
      return *this->items.get()->rbegin();
    }

    throw std::runtime_error("Cannot get last item of empty collection.");
  }

  inline void Skip(int count)
  {
    std::shared_ptr<IWhileCondition<TIterating>> whileCondition =
      std::make_shared<WhileCondition<TIterating, int>>(
        count,
        [](const TIterating & value, int & current) { return current-- > 0; },
        [count](int current) mutable { return count; });
    
    this->InternalSkipWhile(std::move(whileCondition));
  }

  inline void SkipWhile(std::function<bool(TIterating)> && doSkip)
  {
    std::shared_ptr<IWhileCondition<TIterating>> whileCondition =
      std::make_shared<WhileCondition<TIterating, int>>(std::move(doSkip));    
    this->InternalSkipWhile(std::move(whileCondition));
  }

  inline void Take(int count)
  {
    std::shared_ptr<IWhileCondition<TIterating>> whileCondition =
      std::make_shared<WhileCondition<TIterating, int>>(
        count,
        [](const TIterating & value, int & current) { return current-- > 0; },
        [count](int current) mutable { return count; });
    
    this->InternalTakeWhile(std::move(whileCondition));
  }

  inline void TakeWhile(std::function<bool(TIterating)> && doTake)
  {
    std::shared_ptr<IWhileCondition<TIterating>> whileCondition =
      std::make_shared<WhileCondition<TIterating, int>>(std::move(doTake));    
    this->InternalTakeWhile(std::move(whileCondition));
  }

  // make private?
  inline virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TIterating>> && condition) = 0;
  inline virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TIterating>> && condition) = 0;
  
  // TODO these can be done with iterators instead
  // inline bool Equal(const TIterable<TStoring, TArgs...> & collection) const
  // {
  //   return this->Equal(collection, collection.size());
  // }
  //
  // inline bool Equal(
  //   const TIterable<TStoring, TArgs...> & collection,
  //   const std::function<bool(TStoring, TStoring)> & areEqual) const
  // {
  //   return this->Equal(collection, collection.size(), areEqual);
  // }
  //
  // // forward_list does not contain size() method and don't want to require it
  // // it would be faster to do a pre-check for containers that do have constant size methods
  // inline bool Equal(const TIterable<TStoring, TArgs...> & collection, size_t collectionSize) const
  // {
  //   static_assert(is_equatable<TStoring>::value, "Type must be equatable");
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
  //   for (TStoring item : collection)
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
  //   const TIterable<TStoring, TArgs...> & collection,
  //   size_t collectionSize,
  //   const std::function<bool(TStoring, TStoring)> & areEqual) const
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
  //   for (TStoring item : collection)
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
  // InternalQueryable<TStoring, TContainer>* Concat(TContainer<TStoring> collection, bool preserveFilter = false)
  // {
  //   for (TStoring obj : collection)
  //   {
  //     if (!preserveFilter || this->items.get()->PassesCondition(obj))
  //     {
  //       this->items.get()->Add(obj);
  //     }
  //   }
  //
  //   return this;
  // }

  inline double Sum(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    double sum = 0;

    for (TIterating item : *this->items.get())
    {
      sum += retrieveValue(item);
    }

    return sum;
  }
  inline size_t Sum(std::function<size_t(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    size_t sum = 0;

    for (TIterating item : *this->items.get())
    {
      sum += retrieveValue(item);
    }

    return sum;
  }

  inline double Average(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    double sum = 0;
    size_t count = 0;

    for (TIterating item : *this->items.get())
    {
      sum += retrieveValue(item);
      count++;
    }

    return count > 0 ? sum / count : 0;
  }

  inline double Average(
    std::function<double(double, size_t)> divisor,
    std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    double sum  = 0;
    size_t count = 0;

    for (TIterating item : *this->items.get())
    {
      sum += retrieveValue(item);
      count++;
    }

    return divisor(sum, count);
  }

  template<typename T>
  inline TIterating MaxItem(std::function<T(TIterating)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T maxValue;
    TIterating maxItem;

    for (TIterating item : *this->items.get())
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
  inline T Max(std::function<T(TIterating)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MaxItem(retrieveValue));
  }

  inline TStoring Max() const
  {
    static_assert(is_less_comparable<TIterating>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    TIterating maxItem;

    for (TIterating item : *this->items.get())
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
  inline T Max(std::function<T(TIterating)> retrieveValue, T startSeed) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T max = startSeed;

    for (TIterating item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (max < newValue)
      {
        max = newValue;
      }
    }

    return max;
  }

  inline TIterating Max(TIterating startSeed) const
  {
    static_assert(is_less_comparable<TIterating>::value, "Type must be 'less than' comparable");

    TIterating max = startSeed;

    for (TIterating item : *this->items.get())
    {
      if (max < item)
      {
        max = item;
      }
    }

    return max;
  }

  template<typename T>
  inline TIterating MinItem(std::function<T(TIterating)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T minValue = T();
    TIterating minItem;

    for (TIterating item : *this->items.get())
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
  inline T Min(std::function<T(TIterating)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MinItem(retrieveValue));
  }

  inline TIterating Min() const
  {
    static_assert(is_less_comparable<TIterating>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    TIterating minItem;

    for (TIterating item : *this->items.get())
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
  inline T Min(std::function<T(TIterating)> retrieveValue, T startSeed) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T min = startSeed;

    for (TIterating item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (newValue < min)
      {
        min = newValue;
      }
    }

    return min;
  }

  inline TIterating Min(TIterating startSeed) const
  {
    static_assert(is_less_comparable<TIterating>::value, "Type must be 'less than' comparable");

    TIterating min = startSeed;

    for (TIterating item : *this->items.get())
    {
      if (item < min)
      {
        min = item;
      }
    }

    return min;
  }

  template<typename T>
  inline T Range(std::function<T(TIterating)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    static_assert(is_subtractable<T>::value, "Type must overload subtraction operator");

    bool isFirst = true;
    T max;
    T min;

    for (TIterating item : *this->items.get())
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

  inline double Range(std::function<double(TIterating)> retrieveValue = [](TIterating value) { return value; }) const
  {
    bool isFirst = true;
    double max = 0.0;
    double min = 0.0;

    for (TIterating item : *this->items.get())
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
  inline bool Any(std::function<bool(TIterating)> condition) const
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
  inline bool All(std::function<bool(TIterating)> condition) const
  {
    for (TIterating item : *this->items.get())
    {
      if (!condition(item))
      {
        return false;
      }
    }

    return true;
  }

  template<typename TDestination, typename TAllocatorDestination = std::allocator<TDestination>>
  std::shared_ptr<InternalQueryable<TDestination, std::vector, TDestination, TAllocatorDestination>> Select(
    std::function<TDestination(TIterating)> & selector)
  {
    std::shared_ptr<SelectQueryableData<TStoring, TDestination, TIterable, TIterating, TAllocatorDestination, TArgs...>> selectData =
      std::make_shared<SelectQueryableData<TStoring, TDestination, TIterable, TIterating, TAllocatorDestination, TArgs...>>(
        this->items,
        selector);

    std::shared_ptr<VectorInternalQueryable<TDestination, TAllocatorDestination>> mapQueryable =
      std::make_shared<VectorInternalQueryable<TDestination, TAllocatorDestination>>(
        std::move(selectData),
        QueryableType::Vector);

    return
      FutureStd::reinterpret_pointer_cast<InternalQueryable<TDestination, std::vector, TDestination, TAllocatorDestination>>(
        mapQueryable);
  }

  inline bool Contains(const TIterating & item) const
  {
    static_assert(is_equatable<TIterating>::value, "Item must be equatable");

    for (const TIterating & localItem : *this->items.get())
    {
      if (localItem == item)
      {
        return true;
      }
    }

    return false;
  }

  template<typename TLessThan = std::less<TStoring>>
  void Sort(TLessThan lessThan = {})
  {
    // sorting is fragile wrt to container type in cpp. Need to have a simple QueryableData container to be able to sort properly
    this->items = FutureStd::reinterpret_pointer_cast<QueryableData<TStoring, TIterable, TIterating, TArgs...>>(
      this->items->GetRealizedQueryableData());

    switch (this->GetType())
    {
      case QueryableType::Deque:
        this->items->Sort(
          FutureStd::reinterpret_pointer_cast<ISorter<TStoring, TIterable, TArgs...>>(
            std::make_shared<DequeSorter<TStoring, TLessThan, TArgs...>>(lessThan)));
        break;
      case QueryableType::List:
        this->items->Sort(
          FutureStd::reinterpret_pointer_cast<ISorter<TStoring, TIterable, TArgs...>>(
            std::make_shared<ListSorter<TStoring, TLessThan, TArgs...>>(lessThan)));
        break;
      case QueryableType::Vector:
        this->items->Sort(
          FutureStd::reinterpret_pointer_cast<ISorter<TStoring, TIterable, TArgs...>>(
            std::make_shared<VectorSorter<TStoring, TLessThan, TArgs...>>(lessThan)));
        break;
      case QueryableType::MultiSet:
      case QueryableType::Set:
      default:
        break;
    }
  }

  // TODO --> recently found out that the allocator and value compare are able to be retrieved
  //   from the std lib containers... Don't need to have them passed in
  template<
    template<typename, typename ...> typename TExceptions,
    typename TLessThan = std::less<TIterating>,
    typename TAllocator = std::allocator<TIterating>,
    typename ...TExceptionArgs>
  void Except(
    const TExceptions<TIterating, TExceptionArgs...> & exceptions,
    TLessThan lessThan = {},
    TAllocator allocator = {})
  {
    static_assert(can_iterate<TExceptions<TIterating, TExceptionArgs...>>::value, "Class must be able to be iterated over");

    // O(nlogn) minimize and sort the exceptions coming in
    std::set<TIterating, TLessThan, TAllocator> sortedExceptions(
      exceptions.begin(),
      exceptions.end(),
      lessThan,
      allocator);

    // TODO --> This should not be necessary and I am pretty sure there is a bug somewhere causing the need for it
    this->items = FutureStd::reinterpret_pointer_cast<QueryableData<TStoring, TIterable, TIterating, TArgs...>>(
      this->items->GetRealizedQueryableData());

    // O(m) make a copy of current items
    TIterable<TStoring, TArgs...> copy(this->items->begin(), this->items->end());

    // O(m) clear current items (may be better to re-instantiate instead?)
    this->items->Clear();

    auto last = sortedExceptions.end();
    // O(mlogn) add back any that don't exist within exceptions
    for (const TIterating & item : copy)
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
    // std::vector<TStoring> localSorted = this->Sort(comparator).ToVector();
    // std::vector<TStoring> inputSorted = collection->ToVector();
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
    // std::vector<TStoring> result;
    // int localIndex = 0;
    // int inputIndex = 0;
    //
    // std::function<bool(TStoring, TStoring)> equal = [&](TStoring a, TStoring b)
    // {
    //   return !comparator(a, b) && !comparator(b, a);
    // };
    //
    // while (localIndex < localCount && inputIndex < inputCount)
    // {
    //   TStoring localItem = localSorted[localIndex];
    //   TStoring inputItem = inputSorted[inputIndex];
    //
    //   if (equal(localItem, inputItem))
    //   {
    //     TStoring equalValue = localItem;
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
  template<typename T = TIterating>
  inline T Aggregate(const std::function<T(T, TIterating)> & accumulate, T * seed = NULL)
  {
    T aggregatedValue;

    if (seed != NULL)
    {
      aggregatedValue = *seed;
    }

    for (TIterating item : *this->items.get())
    {
      aggregatedValue = accumulate(aggregatedValue, item);
    }

    return aggregatedValue;
  }

  // TODO: changing std::function to a templated member is supposed to be faster
  template<typename TFinalized, typename T = TIterating>
  inline TFinalized Aggregate(
    const std::function<T(T, TIterating)> & accumulate,
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
  //   std::function<TJoinOn(TStoring)> getLocalJoinOn,
  //   std::function<TJoinOn(TJoinObj)> getInputJoinOn,
  //   std::function<TResult(TStoring, TJoinObj)> createFrom,
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
  //     for (TStoring localItem : *this->items.get())
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
  //   for (TStoring item : *this->items.get())
  //   {
  //     result.get()->Add(static_cast<TOut>(item));
  //   }
  //
  //   return result.get();
  // }
};

#endif
