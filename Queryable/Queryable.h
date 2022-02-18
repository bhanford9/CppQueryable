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

#include "QueryableData/GroupQueryableData/GroupQueryableDequeData.h"
#include "QueryableData/GroupQueryableData/GroupQueryableListData.h"
#include "QueryableData/GroupQueryableData/GroupQueryableMultiSetData.h"
#include "QueryableData/GroupQueryableData/GroupQueryableSetData.h"
#include "QueryableData/GroupQueryableData/GroupQueryableVectorData.h"
#include "QueryableData/IQueryableData.h"
#include "QueryableData/QueryableDequeData.h"
#include "QueryableData/QueryableListData.h"
#include "QueryableData/QueryableMultiSetData.h"
#include "QueryableData/QueryableSetData.h"
#include "QueryableData/QueryableVectorData.h"
#include "QueryableData/SelectQueryableData/SelectQueryableData.h"
#include "QueryableData/SelectQueryableData/SelectQueryableDequeData.h"
#include "QueryableData/SelectQueryableData/SelectQueryableListData.h"
#include "QueryableData/SelectQueryableData/SelectQueryableMultiSetData.h"
#include "QueryableData/SelectQueryableData/SelectQueryableSetData.h"
#include "QueryableData/SelectQueryableData/SelectQueryableVectorData.h"
#include "QueryableData/WhereQueryableData/WhereQueryableData.h"
#include "QueryableData/WhereQueryableData/WhereQueryableDequeData.h"
#include "QueryableData/WhereQueryableData/WhereQueryableListData.h"
#include "QueryableData/WhereQueryableData/WhereQueryableMultiSetData.h"
#include "QueryableData/WhereQueryableData/WhereQueryableSetData.h"
#include "QueryableData/WhereQueryableData/WhereQueryableVectorData.h"
#include "QueryableType.h"
#include "TypeConstraintUtil.h"
#include "Utilities/Condition.h"
#include "Utilities/Group.h"
#include "Utilities/PersistentContainer.h"

#include "../CppQueryableTest/Queryable/Performance/Time/Utilities/Duration.h"
#include "../CppQueryableTest/Queryable/Performance/Time/Utilities/TimingTypes.h"

template<typename TObj>
class Queryable
{
protected:
  // TODO --> consider making this unique and having all of the
  //   QueryableData's implement their own clones
  std::shared_ptr<IQueryableData<TObj, TObj>> items;
  PersistentContainer persistentContainer;
  QueryableType type;

  template<typename T, template<typename...> typename TIterable>
  bool Equal(TIterable<T> collection, int collectionSize)
  {
    static_assert(is_equatable<T>::value, "Type must be equatable");

    int localCount = this->Count();

    if (localCount != collectionSize)
    {
      return false;
    }

    int i = 0;
    for (T item : collection)
    {
      if (!(this->At(i++) == item))
      {
        return false;
      }
    }

    return true;
  }

  template<typename T, template<typename...> typename TIterable>
  bool Equal(TIterable<T> collection, int collectionSize, std::function<bool(T, T)> areEqual)
  {
    int localCount = this->Count();

    if (localCount != collectionSize)
    {
      return false;
    }

    int i = 0;
    for (T item : collection)
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
  Queryable(
    QueryableType type = QueryableType::Vector,
    std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; })
  {
    switch (type)
    {
      case QueryableType::Deque:
        {
          std::cout << "[TRACE:Queryable] init wiht deque" << std::endl;
          std::deque<TObj> localDeque;
          this->items = std::make_shared<QueryableDequeData<TObj>>(localDeque);
        }
        break;
      case QueryableType::List:
        {
          std::cout << "[TRACE:Queryable] init wiht list" << std::endl;
          std::list<TObj> localList;
          this->items = std::make_shared<QueryableListData<TObj>>(localList);
        }
        break;
      case QueryableType::MultiSet:
        {
          std::cout << "[TRACE:Queryable] init wiht multisaet" << std::endl;
          std::multiset<TObj, std::function<bool(TObj, TObj)>> localMultiSet(compare);
          this->items = std::make_shared<QueryableMultiSetData<TObj>>(localMultiSet);
        }
        break;
      case QueryableType::Set:
        {
          std::cout << "[TRACE:Queryable] init wiht set" << std::endl;
          std::set<TObj, std::function<bool(TObj, TObj)>> localSet(compare);
          this->items = std::make_shared<QueryableSetData<TObj>>(localSet);
        }
        break;
      case QueryableType::Vector:
      default:
        {
          std::cout << "[TRACE:Queryable] init wiht vector" << std::endl;
          std::vector<TObj> localVector;
          this->items = std::make_shared<QueryableVectorData<TObj>>(localVector);
          std::cout << "size of vector: " << localVector.size() << std::endl;
          std::cout << "own size: " << this->Count() << std::endl;
        }
        break;
    }

    this->type = type;
  }

  Queryable(const Queryable<TObj>& queryable)
    : Queryable(queryable.type)
  {
    this->persistentContainer = queryable.persistentContainer;
    this->type = queryable.type;
    this->items = queryable.items;
  }

  Queryable(
    std::shared_ptr<IQueryableData<TObj, TObj>> queryableData,
    QueryableType type)
  {
    this->items = std::move(queryableData);
    this->type = type;
  }

  Queryable(const std::deque<TObj>& deque)
  {
    this->type = QueryableType::Deque;
    this->items = std::move(std::make_shared<QueryableDequeData<TObj>>(deque));
  }

  Queryable(const std::list<TObj>& list)
  {
    this->type = QueryableType::List;
    this->items = std::move(std::make_shared<QueryableListData<TObj>>(list));
  }

  Queryable(const std::multiset<TObj, std::function<bool(TObj, TObj)>>& multiset)
  {
    this->type = QueryableType::MultiSet;
    this->items = std::move(std::make_shared<QueryableMultiSetData<TObj>>(multiset));
  }

  Queryable(const std::set<TObj, std::function<bool(TObj, TObj)>>& set)
  {
    this->type = QueryableType::Set;
    this->items = std::move(std::make_shared<QueryableSetData<TObj>>(set));
  }

  Queryable(const std::multiset<TObj>& multiset)
  {
    this->type = QueryableType::MultiSet;
    std::multiset<TObj, std::function<bool(TObj, TObj)>> newMultiset(
      multiset.begin(),
      multiset.end(),
      [](TObj a, TObj b) { return a < b; });
    this->items = std::move(std::make_shared<QueryableMultiSetData<TObj>>(newMultiset));
  }

  Queryable(const std::set<TObj>& set)
  {
    this->type = QueryableType::Set;
    std::set<TObj, std::function<bool(TObj, TObj)>> newSet(
      set.begin(),
      set.end(),
      [](TObj a, TObj b) { return a < b; });
    this->items = std::move(std::make_shared<QueryableSetData<TObj>>(newSet));
  }

  Queryable(const std::vector<TObj>& vector)
  {
    this->type = QueryableType::Vector;
    this->items = std::move(std::make_shared<QueryableVectorData<TObj>>(vector));
    std::cout << "size of vector in: " << vector.size() << std::endl;
    std::cout << "own size: " << this->Count() << std::endl;
  }
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

  template<typename TNewAllocator = std::allocator<TObj>>
  std::deque<TObj, TNewAllocator> ToDeque() const
  {
    std::deque<TObj, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  std::list<TObj, TNewAllocator> ToList() const
  {
    std::list<TObj, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  std::multiset<TObj, std::function<bool(TObj, TObj)>> ToMultiSet(
    std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) const
  {
    std::multiset<TObj, std::function<bool(TObj, TObj)>> newItems(compare);

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  std::set<TObj, std::function<bool(TObj, TObj)>> ToSet(
    std::function<bool(TObj, TObj)> compare = [](TObj a, TObj b) { return a < b; }) const
  {
    std::set<TObj, std::function<bool(TObj, TObj)>> newItems(compare);

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  std::vector<TObj, TNewAllocator> ToVector() const
  {
    std::vector<TObj, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj> & ToQueryableDeque()
  {
    std::deque<TObj> copy = this->ToDeque();

    this->items = std::make_shared<QueryableDequeData<TObj, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    this->type = QueryableType::Deque;
    return *this;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj> & ToQueryableList()
  {
    std::list<TObj> copy = this->ToList();

    this->items = std::make_shared<QueryableListData<TObj, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    this->type = QueryableType::List;
    return *this;
  }

  Queryable<TObj> & ToQueryableMultiSet()
  {
    std::multiset<TObj, std::function<bool(TObj, TObj)>> copy = this->ToMultiSet();
    this->items = std::make_shared<QueryableMultiSetData<TObj>>(copy);

    this->type = QueryableType::MultiSet;
    return *this;
  }

  Queryable<TObj> & ToQueryableSet()
  {
    std::set<TObj, std::function<bool(TObj, TObj)>> copy = this->ToSet();
    this->items = std::make_shared<QueryableSetData<TObj>>(copy);

    this->type = QueryableType::Set;
    return *this;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj> & ToQueryableVector()
  {
    std::vector<TObj> copy = this->ToVector();

    this->items = std::make_shared<QueryableVectorData<TObj, TNewAllocator>>();
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

  Queryable<TObj> & Where(std::function<bool(const TObj &)> condition, QueryableType returnType = QueryableType::Default)
  {
    if (returnType == QueryableType::Default)
    {
      returnType = this->type;
    }

    switch (returnType)
    {
      // Think I need to create move constructors or each of these
      case QueryableType::Deque:
        this->items = std::move(std::make_shared<WhereQueryableDequeData<TObj>>(std::move(this->items), std::move(condition)));
        break;
      case QueryableType::List:
        this->items = std::move(std::make_shared<WhereQueryableListData<TObj>>(std::move(this->items), std::move(condition)));
        break;
      case QueryableType::MultiSet:
        this->items = std::move(std::make_shared<WhereQueryableMultiSetData<TObj>>(std::move(this->items), std::move(condition)));
        break;
      case QueryableType::Set:
        this->items = std::move(std::make_shared<WhereQueryableSetData<TObj>>(std::move(this->items), std::move(condition)));
        break;
      case QueryableType::Vector:
        this->items = std::move(std::make_shared<WhereQueryableVectorData<TObj>>(std::move(this->items), std::move(condition)));
        break;
      default: break;
    }

    this->type = returnType;

    return *this;
  }

  Queryable<TObj> WhereCopy(std::function<bool(TObj)> condition, QueryableType returnType = QueryableType::Default)
  {
    Queryable<TObj> returnValue(returnType);

    for (TObj item : *this->items.get())
    {
      if (condition(item))
      {
        returnValue.Add(item);
      }
    }

    return returnValue;
  }

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
  // Queryable<TObj> Take(int count)
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
  // Queryable<TObj> * TakeWhile(std::function<bool(TObj)> doTake)
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
  // Queryable<TObj>* Skip(int count)
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
  // Queryable<TObj>* SkipWhile(std::function<bool(TObj)> doSkip)
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
  //   Queryable<TObj>* retval = this->Skip(toDelete);
  //   return retval;
  // }

  bool Equal(std::vector<TObj> collection)
  {
    return this->Equal<TObj, std::vector>(collection, collection.size());
  }

  bool Equal(std::vector<TObj> collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::vector>(collection, collection.size(), areEqual);
  }

  bool Equal(std::list<TObj> collection)
  {
    return this->Equal<TObj, std::list>(collection, collection.size());
  }

  bool Equal(std::list<TObj> collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::list>(collection, collection.size(), areEqual);
  }

  bool Equal(std::deque<TObj> collection)
  {
    return this->Equal<TObj, std::deque>(collection, collection.size());
  }

  bool Equal(std::deque<TObj> collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::deque>(collection, collection.size(), areEqual);
  }

  bool Equal(std::set<TObj> collection)
  {
    return this->Equal<TObj, std::set>(collection, collection.size());
  }

  bool Equal(std::set<TObj> collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::set>(collection, collection.size(), areEqual);
  }

  bool Equal(std::multiset<TObj> collection)
  {
    return this->Equal<TObj, std::multiset>(collection, collection.size());
  }

  bool Equal(std::multiset<TObj> collection, std::function<bool(TObj, TObj)> areEqual)
  {
    return this->Equal<TObj, std::multiset>(collection, collection.size(), areEqual);
  }

  // with preserveFilter true, you can do the following:
  //   collection.Where(x => x.IsValid).Concat(otherItems, true);
  //
  // and the Where condition will be executed on the incoming items to prevent
  // unwanted items from being added without needing to immediately apply the
  // where condition to the rest of the inital collection
  template<typename T, template<typename...> typename TIterable>
  Queryable<TObj>* Concat(TIterable<TObj> collection, bool preserveFilter = false)
  {
    for (TObj obj : collection)
    {
      if (!preserveFilter || this->items.get()->PassesCondition(obj))
      {
        this->items.get()->Add(obj);
      }
    }

    return this;
  }

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

  template<typename T>
  Queryable<T> Select(
    std::function<T(TObj)> retrieveValue,
    std::function<bool(T,T)> lessThan = [](T a, T b) { return a < b; })
  {
    std::shared_ptr<IQueryableData<T, T>> selectable;

    // copy of shared reference must be made so the original container can still
    // be used. assigning shared pointers can be slower than moving them by hundreds
    // of clock cycles, so this needs to be avoided when possible
    std::shared_ptr<IQueryableData<TObj, TObj>> itemCopy = this->items;

    switch (this->type)
    {
      case QueryableType::Deque:
        selectable = std::move(std::make_shared<SelectQueryableDequeData<TObj, T>>(std::move(itemCopy), retrieveValue));
        break;
      case QueryableType::List:
        selectable = std::move(std::make_shared<SelectQueryableListData<TObj, T>>(std::move(itemCopy), retrieveValue));
        break;
      case QueryableType::MultiSet:
        selectable = std::move(std::make_shared<SelectQueryableMultiSetData<TObj, T>>(std::move(itemCopy), retrieveValue));
        break;
      case QueryableType::Set:
        selectable = std::move(std::make_shared<SelectQueryableSetData<TObj, T>>(std::move(itemCopy), retrieveValue));
        break;
      case QueryableType::Vector:
        selectable = std::move(std::make_shared<SelectQueryableVectorData<TObj, T>>(std::move(itemCopy), retrieveValue));
        break;
      default: break;
    }

    Queryable<T> queryable(std::move(selectable), this->type);
    return queryable;
    // std::shared_ptr<Queryable<T>> queryable = std::make_shared<Queryable<T>>(std::move(selectable), this->type);
    // this->persistentContainer.Set(queryable);
    // return *this->persistentContainer.GetAs<Queryable<T>>().get();
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
  Queryable<TObj> & Sort(
    std::function<bool(TObj, TObj)> comparator = [](TObj a, TObj b) { return a < b; })
  {
    this->items.get()->Sort(comparator);
    return *this;
  }

  template<typename T = TObj>
  Queryable<TObj> & OrderBy(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; })
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return this->Sort([&](TObj a, TObj b){ return retrieveValue(a) < retrieveValue(b); });
  }

  template<typename T = TObj>
  Queryable<TObj> & OrderByDescending(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; })
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return this->Sort([&](TObj a, TObj b){ return retrieveValue(b) < retrieveValue(a); });
  }

  // TODO --> is returing it ordered based on the given comparator okay?
  //          should having an implementation that doesn't change order be done?
  Queryable<TObj> & Except(
    const Queryable<TObj> & collection,
    std::function<bool(TObj, TObj)> comparator = [](TObj a, TObj b) { return a < b; })
  {
    // TODO --> if  nXm < max(nlog(n), mlog(m)) then sorting is not worth it
    // TODO --> don't call toVector if the type is already a random access iterator

    std::vector<TObj> localSorted = this->Sort(comparator).ToVector();
    std::vector<TObj> inputSorted = collection.ToVector();
    std::sort(inputSorted.begin(), inputSorted.end(), comparator);

    int localCount = localSorted.size();
    int inputCount = inputSorted.size();

    if (localCount <= 0 || inputCount <= 0)
    {
      return *this;
    }

    std::vector<TObj> result;
    int localIndex = 0;
    int inputIndex = 0;

    std::function<bool(TObj, TObj)> equal = [&](TObj a, TObj b)
    {
      return !comparator(a, b) && !comparator(b, a);
    };

    while (localIndex < localCount && inputIndex < inputCount)
    {
      TObj localItem = localSorted[localIndex];
      TObj inputItem = inputSorted[inputIndex];

      if (equal(localItem, inputItem))
      {
        TObj equalValue = localItem;

        while (++localIndex < localCount && equal(equalValue, localSorted[localIndex]));
        while (++inputIndex < inputCount && equal(equalValue, inputSorted[inputIndex]));
      }
      else if (comparator(localItem, inputItem))
      {
        result.push_back(localItem);
        localIndex++;
      }
      else
      {
        inputIndex++;
      }
    }

    // gather leftovers
    for (; localIndex < localCount; localIndex++)
    {
      if (!equal(localSorted[localIndex], inputSorted[inputCount - 1]))
      {
        result.push_back(localSorted[localIndex]);
      }
    }

    // this is a linear update. Constant update or updating within the previous
    // looping would be ideal
    this->items.get()->Update(result.begin(), result.end());

    return *this;
  }

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

  template<
    typename TJoinObj,
    typename TJoinOn,
    typename TResult>
  Queryable<TResult> & Join(
    Queryable<TJoinObj> & collection,
    std::function<TJoinOn(TObj)> getLocalJoinOn,
    std::function<TJoinOn(TJoinObj)> getInputJoinOn,
    std::function<TResult(TObj, TJoinObj)> createFrom,
    std::function<bool(TResult, TResult)> outCompare,
    QueryableType returnType = QueryableType::Default)
  {
    static_assert(is_less_comparable<TJoinOn>::value, "Type must be 'less than' comparable");
    typedef Queryable<TResult> TReturn;

    QueryableType type = returnType == QueryableType::Default ? this->type : returnType;
    std::shared_ptr<TReturn> data = std::make_shared<TReturn>(type, outCompare);
    this->persistentContainer.Set(data);
    std::shared_ptr<TReturn> result = this->persistentContainer.GetAs<TReturn>();

    // Sort each collection on passed in key getters                             ( + time complexity: nlog(n) )
    //   this allows us to only need to fully iterate over each collection once  ( + time complexity: n )
    //   and chunks of non-joinable data can be easily bypassed                  ( + non-generalizable benefit )
    // Change inner collection to vector to gaurantee constant time indexing     ( - requires extra space )
    //   may want to only do this if collection type does not have constant time indexing
    this->OrderBy(getLocalJoinOn);
    std::vector<TJoinObj> inputSorted = collection.OrderBy(getInputJoinOn).ToVector();
    int inputSize = inputSorted.size();

    if (inputSize > 0)
    {
      int inputIndex = 0;

      for (TObj localItem : *this->items.get())
      {
        TJoinOn localValue;
        TJoinOn inputValue;

        do
        {
          TJoinObj inputItem = inputSorted[inputIndex];

          localValue = getLocalJoinOn(localItem);
          inputValue = getInputJoinOn(inputItem);

          if (localValue == inputValue)
          {
            int sameValueIndex = inputIndex;
            while (sameValueIndex < inputSize)
            {
              TJoinOn nextValue = getInputJoinOn(inputSorted[sameValueIndex]);

              // if they're not equal then move on
              if ((nextValue < inputValue) || (inputValue < nextValue))
              {
                break;
              }

              result.get()->Add(createFrom(localItem, inputSorted[sameValueIndex++]));
            }
          }

          if (inputValue <= localValue)
          {
            inputIndex++;
          }

        } while (inputValue < localValue && inputIndex < inputSize);
      }
    }

    return *result.get();
  }

  template<typename TOut>
  Queryable<TOut>* Cast()
  {
    // TODO --> make this a deferred action
    typedef Queryable<TOut> TReturn;
    std::shared_ptr<TReturn> data = std::make_shared<TReturn>(this->type);
    this->persistentContainer.Set(data);
    std::shared_ptr<TReturn> result = this->persistentContainer.GetAs<TReturn>();

    for (TObj item : *this->items.get())
    {
      result.get()->Add(static_cast<TOut>(item));
    }

    return result.get();
  }


  template<typename TKey, typename TData = TObj>
  Queryable<Group<TKey, TObj>> GroupBy(
    std::function<TKey(TObj)> getKey,
    QueryableType storageType = QueryableType::Default,
    std::function<bool(TKey, TKey)> keyCompare = [](TKey a, TKey b) { return a < b; },
    std::function<bool(TData, TData)> dataCompare = [](TData a, TData b) { return a < b; })
  {
    QueryableType type = storageType == QueryableType::Default ? this->type : storageType;
    Queryable<Group<TKey, TObj>> queryableGroups(type);

    for (TObj item : *this->items.get())
    {
      TKey key = getKey(item);

      if (!queryableGroups.Any([&](Group<TKey, TObj> group) { return group.HasKey(key); }))
      {
        switch (type)
        {
          case QueryableType::Deque:
            queryableGroups.Add(GroupQueryableDequeData<TKey, TData>(key, type, keyCompare));
            break;
          case QueryableType::List:
            queryableGroups.Add(GroupQueryableListData<TKey, TData>(key, type, keyCompare));
            break;
          case QueryableType::MultiSet:
            queryableGroups.Add(GroupQueryableMultiSetData<TKey, TData>(key, type, keyCompare, dataCompare));
            break;
          case QueryableType::Set:
            queryableGroups.Add(GroupQueryableSetData<TKey, TData>(key, type, keyCompare, dataCompare));
            break;
          case QueryableType::Vector:
          default:
            queryableGroups.Add(GroupQueryableVectorData<TKey, TData>(key, type, keyCompare));
            break;
        }
      }

      queryableGroups
        .First([&](Group<TKey, TObj> group) { return group.HasKey(key); })
        .Add(item);
    }

    queryableGroups.Sort([](Group<TKey, TObj> a, Group<TKey, TObj> b) { return a < b; });

    return queryableGroups;
  }
};

#endif
