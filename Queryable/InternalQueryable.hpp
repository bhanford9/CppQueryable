#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLE_H

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

  template<template<typename...> typename TContainer, typename ...TContainerArgs>
  bool Equal(const TContainer<TObj, TContainerArgs...> & collection, int collectionSize)
  {
    static_assert(is_equatable<TObj>::value, "Type must be equatable");

    int localCount = this->Count();

    if (localCount != collectionSize)
    {
      return false;
    }

    int i = 0;
    for (TObj item : collection)
    {
      if (!(this->At(i++) == item))
      {
        return false;
      }
    }

    return true;
  }

  template<template<typename...> typename TContainer, typename ...TContainerArgs>
  bool Equal(const TContainer<TObj, TContainerArgs...> & collection, int collectionSize, std::function<bool(TObj, TObj)> areEqual)
  {
    int localCount = this->Count();

    if (localCount != collectionSize)
    {
      return false;
    }

    int i = 0;
    for (TObj item : collection)
    {
      if (!areEqual(this->At(i++), item))
      {
        return false;
      }
    }

    return true;
  }

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

  InternalQueryable(const TIterable<TObj, TArgs...> & iterable);
  // END CONSTRUCTORS

  QueryableType GetType()
  {
    return this->type;
  }

  void Clear()
  {
    this->items.get()->Clear();
  }

  void Add(TObj obj)
  {
    this->items.get()->Add(obj);
  }

  template<typename TAllocator = std::allocator<TObj>>
  std::deque<TObj, TAllocator> ToDeque() const
  {
    std::deque<TObj, TAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TAllocator = std::allocator<TObj>>
  std::list<TObj, TAllocator> ToList() const
  {
    std::list<TObj, TAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  std::multiset<TObj, TLessThan, TAllocator> ToMultiSet(TLessThan lessThan = {}) const
  {
    std::multiset<TObj, TLessThan, TAllocator> newItems(lessThan);

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  std::set<TObj, TLessThan, TAllocator> ToSet(TLessThan lessThan = {}) const
  {
    std::set<TObj, TLessThan, TAllocator> newItems(lessThan);

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TAllocator = std::allocator<TObj>>
  std::vector<TObj, TAllocator> ToVector() const
  {
    std::vector<TObj, TAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  // TODO --> determine best way to return
  template<typename TAllocator = std::allocator<TObj>>
  DequeInternalQueryable<TObj, TAllocator> & ToQueryableDeque()
  {
    std::deque<TObj, TAllocator> copy = this->ToDeque();

    this->items = std::make_shared<QueryableDequeData<TObj, TAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    this->type = QueryableType::Deque;
    return *this;
  }

  template<typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::list, TAllocator> & ToQueryableList()
  {
    std::list<TObj, TAllocator> copy = this->ToList();

    this->items = std::make_shared<QueryableListData<TObj, TAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    this->type = QueryableType::List;
    return *this;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::multiset, TLessThan, TAllocator> & ToQueryableMultiSet()
  {
    std::multiset<TObj, TLessThan, TAllocator> copy = this->ToMultiSet();
    this->items = std::make_shared<QueryableMultiSetData<TObj, TLessThan, TAllocator>>(copy);

    this->type = QueryableType::MultiSet;
    return *this;
  }

  template<typename TLessThan = std::less<TObj>, typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::set, TLessThan, TAllocator> & ToQueryableSet()
  {
    std::set<TObj, std::function<bool(TObj, TObj)>> copy = this->ToSet();
    this->items = std::make_shared<QueryableSetData<TObj, TLessThan, TAllocator>>(copy);

    this->type = QueryableType::Set;
    return *this;
  }

  template<typename TAllocator = std::allocator<TObj>>
  InternalQueryable<TObj, std::vector, TAllocator> & ToQueryableVector()
  {
    std::vector<TObj> copy = this->ToVector();

    this->items = std::make_shared<QueryableVectorData<TObj, TAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    this->type = QueryableType::Vector;
    return *this;
  }

  bool IsEmpty()
  {
    return this->items.get()->begin() == this->items.get()->end();
  }

  TObj & At(int index)
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

  int Count()
  {
    return this->items.get()->Count();
  }

  int CountIf(std::function<bool(TObj)> condition)
  {
    int count = 0;

    for (TObj item : *this->items.get())
    {
      if (condition(item))
      {
        count++;
      }
    }

    return count;
  }

  void ForEach(std::function<void(TObj)> action)
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

  // TODO --> drop this down to child classes
  virtual InternalQueryable<TObj, TIterable, TArgs...> & Where(std::function<bool(const TObj &)> condition) = 0;
  // {
  //   switch (this->type)
  //   {
  //     // Think I need to create move constructors or each of these
  //     case QueryableType::Deque:
  //       this->items = std::move(std::make_shared<WhereQueryableDequeData<TObj, TArgs...>>(std::move(this->items), std::move(condition)));
  //       break;
  //     case QueryableType::List:
  //       this->items = std::move(std::make_shared<WhereQueryableListData<TObj, TArgs...>>(std::move(this->items), std::move(condition)));
  //       break;
  //     case QueryableType::MultiSet:
  //       this->items = std::move(std::make_shared<WhereQueryableMultiSetData<TObj, TArgs...>>(std::move(this->items), std::move(condition)));
  //       break;
  //     case QueryableType::Set:
  //       this->items = std::move(std::make_shared<WhereQueryableSetData<TObj, TArgs...>>(std::move(this->items), std::move(condition)));
  //       break;
  //     case QueryableType::Vector:
  //       // std::cout << "into where, items count: " << this->Count() << std::endl;
  //       this->items = std::move(std::make_shared<WhereQueryableVectorData<TObj, TArgs...>>(std::move(this->items), std::move(condition)));
  //       // std::cout << "out where, items count: " << this->Count() << std::endl;
  //       break;
  //     default: break;
  //   }
  //
  //   return *this;
  // }

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

  TObj First(std::function<bool(TObj)> condition)
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

  TObj First()
  {
    if (!this->IsEmpty())
    {
      return *this->items.get()->begin();
    }

    throw std::runtime_error("Cannot get first item of empty collection.");
  }

  TObj Last(std::function<bool(TObj)> condition)
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

  TObj Last()
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

  // TODO --> these should be handled by child classes
  bool Equal(const std::vector<TObj> & collection)
  {
    return this->Equal<TObj, std::vector>(collection, collection.size());
  }

  bool Equal(const std::vector<TObj> & collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::vector>(collection, collection.size(), areEqual);
  }

  bool Equal(const std::list<TObj> & collection)
  {
    return this->Equal<TObj, std::list>(collection, collection.size());
  }

  bool Equal(const std::list<TObj> & collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::list>(collection, collection.size(), areEqual);
  }

  bool Equal(const std::deque<TObj> & collection)
  {
    return this->Equal<TObj, std::deque>(collection, collection.size());
  }

  bool Equal(const std::deque<TObj> & collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::deque>(collection, collection.size(), areEqual);
  }

  bool Equal(const std::set<TObj> & collection)
  {
    return this->Equal<TObj, std::set>(collection, collection.size());
  }

  bool Equal(const std::set<TObj> & collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::set>(collection, collection.size(), areEqual);
  }

  bool Equal(const std::multiset<TObj> & collection)
  {
    return this->Equal<TObj, std::multiset>(collection, collection.size());
  }

  bool Equal(const std::multiset<TObj> & collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::multiset>(collection, collection.size(), areEqual);
  }

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

  template<typename T>
  T Sum(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_aggregatable<T>::value, "Type must implement the '+=' operator");

    T sum = T();

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
    }

    return sum;
  }

  TObj Sum() const
  {
    static_assert(is_aggregatable<TObj>::value, "Type must implement the '+=' operator");

    TObj sum = TObj();

    for (TObj item : *this->items.get())
    {
      sum += item;
    }

    return sum;
  }

  template<typename T>
  double Average(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(std::is_arithmetic<T>::value, "Type must be numeric");

    double sum = 0;
    ulong count = 0;

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
      count++;
    }

    return count > 0 ? sum / count : 0;
  }

  TObj Average(std::function<TObj(const TObj &, ulong)> divisor) const
  {
    static_assert(is_aggregatable<TObj>::value, "Type must implement the '+=' operator");

    TObj sum = TObj();
    ulong count = 0;

    for (TObj item : *this->items.get())
    {
      sum += item;
      count++;
    }

    return divisor(sum, count);
  }

  double Average() const
  {
    static_assert(std::is_arithmetic<TObj>::value, "Type must be numeric");

    double sum = 0;
    ulong count = 0;

    for (TObj item : *this->items.get())
    {
      sum += item;
      count++;
    }

    return count > 0 ? sum / count : 0;
  }

  template<typename T>
  TObj MaxItem(std::function<T(TObj)> retrieveValue) const
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
  T Max(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MaxItem(retrieveValue));
  }

  TObj Max() const
  {
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    TObj maxItem = TObj();

    TTime start = THighRes::now();

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

    TTime end = THighRes::now();

    Duration duration(start, end);

    std::cout << "Max Iteration Time (millis): " << duration.MillisStr() << std::endl;

    return maxItem;
  }

  template<typename T>
  T Max(std::function<T(TObj)> retrieveValue, T startSeed) const
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

  TObj Max(TObj startSeed) const
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
  TObj MinItem(std::function<T(TObj)> retrieveValue) const
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
  T Min(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MinItem(retrieveValue));
  }

  TObj Min() const
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
  T Min(std::function<T(TObj)> retrieveValue, T startSeed) const
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

  TObj Min(TObj startSeed) const
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
  T Range(std::function<T(TObj)> retrieveValue) const
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    static_assert(is_subtractable<T>::value, "Type must overload subtraction operator");

    bool isFirst = true;
    T max = T();
    T min = T();

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

  TObj Range() const
  {
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");
    static_assert(is_subtractable<TObj>::value, "Type must overload subtraction operator");

    bool isFirst = true;
    TObj max = TObj();
    TObj min = TObj();

    for (TObj item : *this->items.get())
    {
      if (isFirst)
      {
        isFirst = false;
        max = item;
        min = item;
      }

      if (item < min)
      {
        min = item;
      }

      if (max < item)
      {
        max = item;
      }
    }

    return max - min;
  }

  bool Any(std::function<bool(TObj)> condition) const
  {
    for (TObj item : *this->items.get())
    {
      if (condition(item))
      {
        return true;
      }
    }

    return false;
  }

  bool All(std::function<bool(TObj)> condition) const
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

  bool Contains(TObj obj) const
  {
    static_assert(is_equatable<TObj>::value, "Item must be equatable");

    for (TObj item : *this->items.get())
    {
      if (item == obj)
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
  //   4. need to verify that the Queryable move constructor is always used for returning
  virtual InternalQueryable<TObj, TIterable, TArgs...> & Sort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; }) = 0;

  // TODO --> using a template instead of std::function is probably faster
  // These are dangerous methods due to not having an Allocator specified at the
  // class level and needing one in the lower layers. I'm not sure how to fix it yet
  template<
    typename T = TObj,
    typename TLessThan = std::less<T>>
  InternalQueryable<TObj, TIterable, TArgs...> & OrderBy(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {})
  {
    return this->Sort([&](TObj a, TObj b) { return lessThan(retrieveValue(a), retrieveValue(b)); });
  }

  template<
    typename T = TObj,
    typename TLessThan = std::less<T>>
  InternalQueryable<TObj, TIterable, TArgs...> & OrderByDescending(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {})
  {
    InternalQueryable<TObj, TIterable, TArgs...> & retVal =
      this->Sort([&](TObj a, TObj b) { return !lessThan(retrieveValue(a), retrieveValue(b)); });
    return retVal;
  }

  template<typename TLessThan, typename TAllocator>
  SortedInternalQueryable<TObj, TIterable, std::function<bool(TObj, TObj)>, TAllocator> & ReSort(std::function<bool(TObj, TObj)> lessThan = [](TObj a, TObj b) { return a < b; })
  {
    std::shared_ptr<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>>, TLessThan, TAllocator>> sorter;

    switch (this->type)
    {
      case QueryableType::MultiSet:
      {
        MultiSetSorter<TObj, TLessThan, TAllocator> multiSetSorter;
        sorter = std::make_shared<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>>, TLessThan, TAllocator>>(multiSetSorter);
      }
      case QueryableType::Set:
      {
        SetSorter<TObj, TLessThan, TAllocator> setSorter;
        sorter = std::make_shared<Sorter<TObj, TIterable, SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>>, TLessThan, TAllocator>>(setSorter);
      }
      default:
        throw std::runtime_error("ReOrderBy, ReOrderByDescending and ReSort are only meant for containers that are ordered by default. For all other containers use OrderBy, OrderByDescending or Sort");
        break;
    }

    SortOutput<TObj, TIterable, std::function<bool(TObj, TObj)>> setOutput = this->items->Sort(*sorter);
    // This return does not work due to the SortedQueryable being abstract.
    // I could have the SortedQueryable implement all abstract methods and pass the execution to child virtual methods,
    // but I don't like needing the Re-Sort method anyway, so might try to find another way to handle this instead.
    return { setOutput.Get() };
  }

  template<
    typename T = TObj,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<TObj>>
  SortedInternalQueryable<TObj, TIterable, TLessThan, TAllocator> & ReOrderBy(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {})
  {
    return this->ReSort<TLessThan, TAllocator>([&](TObj a, TObj b) { return lessThan(retrieveValue(a), retrieveValue(b)); });
  }

  template<
    typename T = TObj,
    typename TLessThan = std::less<T>,
    typename TAllocator = std::allocator<TObj>>
  SortedInternalQueryable<TObj, TIterable, TLessThan, TAllocator> & ReOrderByDescending(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; },
    TLessThan lessThan = {})
  {
    return this->ReSort<TLessThan, TAllocator>([&](TObj a, TObj b) { return !lessThan(retrieveValue(a), retrieveValue(b)); });
  }

  // TODO --> is returing it ordered based on the given comparator okay?
  //          should having an implementation that doesn't change order be done?
  // InternalQueryable<TObj> & Except(
  //   const InternalQueryable<TObj> & collection,
  //   std::function<bool(TObj, TObj)> comparator = [](TObj a, TObj b) { return a < b; })
  // {
  //   // TODO --> if  nXm < max(nlog(n), mlog(m)) then sorting is not worth it
  //   // TODO --> don't call toVector if the type is already a random access iterator
  //
  //   std::vector<TObj> localSorted = this->Sort(comparator).ToVector();
  //   std::vector<TObj> inputSorted = collection.ToVector();
  //   std::sort(inputSorted.begin(), inputSorted.end(), comparator);
  //
  //   int localCount = localSorted.size();
  //   int inputCount = inputSorted.size();
  //
  //   if (localCount <= 0 || inputCount <= 0)
  //   {
  //     return *this;
  //   }
  //
  //   std::vector<TObj> result;
  //   int localIndex = 0;
  //   int inputIndex = 0;
  //
  //   std::function<bool(TObj, TObj)> equal = [&](TObj a, TObj b)
  //   {
  //     return !comparator(a, b) && !comparator(b, a);
  //   };
  //
  //   while (localIndex < localCount && inputIndex < inputCount)
  //   {
  //     TObj localItem = localSorted[localIndex];
  //     TObj inputItem = inputSorted[inputIndex];
  //
  //     if (equal(localItem, inputItem))
  //     {
  //       TObj equalValue = localItem;
  //
  //       while (++localIndex < localCount && equal(equalValue, localSorted[localIndex]));
  //       while (++inputIndex < inputCount && equal(equalValue, inputSorted[inputIndex]));
  //     }
  //     else if (comparator(localItem, inputItem))
  //     {
  //       result.push_back(localItem);
  //       localIndex++;
  //     }
  //     else
  //     {
  //       inputIndex++;
  //     }
  //   }
  //
  //   // gather leftovers
  //   for (; localIndex < localCount; localIndex++)
  //   {
  //     if (!equal(localSorted[localIndex], inputSorted[inputCount - 1]))
  //     {
  //       result.push_back(localSorted[localIndex]);
  //     }
  //   }
  //
  //   // this is a linear update. Constant update or updating within the previous
  //   // looping would be ideal
  //   this->items.get()->Update(result.begin(), result.end());
  //
  //   return *this;
  // }

  template<typename T = TObj>
  T Aggregate(std::function<T(T, TObj)> accumulate, T * seed = NULL)
  {
    T aggregatedValue = T();

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

  template<typename T = TObj, typename TFinalizer>
  TFinalizer Aggregate(
    std::function<T(T, TObj)> accumulate,
    std::function<TFinalizer(T)> finalizer,
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
