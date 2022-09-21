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
#include "InternalQueryables/DequeInternalQueryable.hpp"
#include "InternalQueryables/ListInternalQueryable.hpp"
#include "InternalQueryables/MapInternalQueryable.hpp"
#include "InternalQueryables/MultiSetInternalQueryable.hpp"
#include "InternalQueryables/SetInternalQueryable.hpp"
#include "InternalQueryables/VectorInternalQueryable.hpp"
#include "QueryableType.hpp"
#include "SelectBuilders/SelectBuilder.hpp"
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

  InternalQueryable(QueryableType type = QueryableType::Vector)
  {
    this->type = type;
  }

  InternalQueryable(const InternalQueryable<TObj, TIterable, TArgs...> & queryable)
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

  // For std::map, we need TObj to be a std::pair when se iterate, by it needs to come into here as std::map<TKey, TValue
  // This will likely mean that these need to stop being possible and instead make them static methods for each underlying type
  // The same will need to be done for QueryableData
  InternalQueryable(const QueryableIterator<TObj> & first, const QueryableIterator<TObj> & last, TArgs... args);

  inline QueryableType GetType()
  {
    return this->type;
  }

  inline InternalQueryable<TObj, TIterable, TArgs...> & GetRealized()
  {
    // TODO --> I think I can switch to returning this as QueryableData so casting is not necessary
    std::shared_ptr<IQueryableData<TObj>> realized = this->items->GetRealizedQueryableData();
    this->items = FutureStd::reinterpret_pointer_cast<QueryableData<TObj, TIterable, TArgs...>>(this->items->GetRealizedQueryableData());
    return *this;
  }

  inline void Clear()
  {
    this->items.get()->Clear();
  }

  // TODO --> this may need to be protected for internal use only
  inline void Add(TObj obj)
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

  inline QueryableIterator<TObj> begin()
  {
    // std::cout << "\nInternalQueryable::begin" << std::endl;
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

  template<
    typename TKey,
    typename TValue = TObj,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  inline std::map<TKey, TValue, TLessThan, TAllocator> ToMap(
    std::function<TKey(TObj)> getKey,
    std::function<TValue(TObj)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    std::map<TKey, TValue, TLessThan, TAllocator> newItems(keyCompare, pairAllocator);

    for (TObj item : *this->items.get())
    {
      newItems[getKey(item)] = getValue(item);
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

    for (TObj item : *this->items.get())
    {
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

  template<
    typename TKey,
    typename TValue = TObj,
    typename TLessThan = std::less<TKey>,
    typename TAllocator = std::allocator<std::pair<const TKey, TValue>>>
  inline InternalQueryable<TKey, std::map, TValue, TLessThan, TAllocator> ToQueryableMap(
    std::function<TKey(TObj)> getKey,
    std::function<TValue(TObj)> getValue,
    TLessThan keyCompare = {},
    TAllocator pairAllocator = {})
  {
    MapInternalQueryable<TKey, TValue, TLessThan, TAllocator> retValue(this->ToMap(getKey, getValue, keyCompare, pairAllocator));
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
    for (const TObj & item : *this->items.get())
    {
      action(item);
    }
  }

  virtual void Where(std::function<bool(const TObj &)> condition) = 0;

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

  inline void Skip(int count)
  {
    std::shared_ptr<IWhileCondition<TObj>> whileCondition =
      std::make_shared<WhileCondition<TObj, int>>(
        count,
        [](const TObj & value, int & current) { return current-- > 0; },
        [count](int current) mutable { return count; });
    
    this->InternalSkipWhile(std::move(whileCondition));
  }

  inline void SkipWhile(std::function<bool(TObj)> && doSkip)
  {
    std::shared_ptr<IWhileCondition<TObj>> whileCondition =
      std::make_shared<WhileCondition<TObj, int>>(std::move(doSkip));    
    this->InternalSkipWhile(std::move(whileCondition));
  }

  inline void Take(int count)
  {
    std::shared_ptr<IWhileCondition<TObj>> whileCondition =
      std::make_shared<WhileCondition<TObj, int>>(
        count,
        [](const TObj & value, int & current) { return current-- > 0; },
        [count](int current) mutable { return count; });
    
    this->InternalTakeWhile(std::move(whileCondition));
  }

  inline void TakeWhile(std::function<bool(TObj)> && doTake)
  {
    std::shared_ptr<IWhileCondition<TObj>> whileCondition =
      std::make_shared<WhileCondition<TObj, int>>(std::move(doTake));    
    this->InternalTakeWhile(std::move(whileCondition));
  }

  // make private?
  inline virtual void InternalSkipWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) = 0;
  inline virtual void InternalTakeWhile(std::shared_ptr<IWhileCondition<TObj>> && condition) = 0;
  
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

  template<typename TLessThan = std::less<TObj>>
  void Sort(TLessThan lessThan = {})
  {
    // sorting is fragile wrt to container type in cpp. Need to have a simple QueryableData container to be able to sort properly
    this->items = FutureStd::reinterpret_pointer_cast<QueryableData<TObj, TIterable, TArgs...>>(this->items->GetRealizedQueryableData());

    switch (this->GetType())
    {
      case QueryableType::Deque:
        this->items->Sort(
          FutureStd::reinterpret_pointer_cast<ISorter<TObj, TIterable, TArgs...>>(
            std::make_shared<DequeSorter<TObj, TLessThan, TArgs...>>(lessThan)));
        break;
      case QueryableType::List:
        this->items->Sort(
          FutureStd::reinterpret_pointer_cast<ISorter<TObj, TIterable, TArgs...>>(
            std::make_shared<ListSorter<TObj, TLessThan, TArgs...>>(lessThan)));
        break;
      case QueryableType::Vector:
        this->items->Sort(
          FutureStd::reinterpret_pointer_cast<ISorter<TObj, TIterable, TArgs...>>(
            std::make_shared<VectorSorter<TObj, TLessThan, TArgs...>>(lessThan)));
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

    // TODO --> This should not be necessary and I am pretty sure there is a bug somewhere causing the need for it
    this->items = FutureStd::reinterpret_pointer_cast<QueryableData<TObj, TIterable, TArgs...>>(this->items->GetRealizedQueryableData());

    // O(m) make a copy of current items
    TIterable<TObj, TArgs...> copy(this->items->begin(), this->items->end());

    // O(m) clear current items (may be better to re-instantiate instead?)
    this->items->Clear();

    auto last = sortedExceptions.end();
    // O(mlogn) add back any that don't exist within exceptions
    for (const TObj & item : copy)
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
};

#endif
