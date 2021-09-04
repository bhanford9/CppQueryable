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

// #include "LinkedQueryable.h"
#include "Utilities/Condition.h"
#include "Utilities/Group.h"
#include "Utilities/IGroup.h"
#include "Utilities/PersistentContainer.h"
#include "QueryableData/IQueryableData.h"
#include "QueryableData/QueryableDequeData.h"
#include "QueryableData/QueryableListData.h"
#include "QueryableData/QueryableMultiSetData.h"
#include "QueryableData/QueryableSetData.h"
#include "QueryableData/QueryableVectorData.h"
#include "QueryableType.h"
#include "TypeConstraintUtil.h"

template<typename TObj, typename TCompare = std::less<TObj>>
class Queryable
{
protected:
  std::shared_ptr<IQueryableData<TObj>> items;
  PersistentContainer persistentContainer;
  QueryableType type;

  // may want to create an enumeration for this
  virtual bool IsLinked()
  {
    return false;
  }

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
    TCompare compare = TCompare())
  {
    switch (type)
    {
      case QueryableType::Deque:
        {
          std::deque<TObj> localDeque;
          this->items = std::make_shared<QueryableDequeData<TObj>>(localDeque);
        }
        break;
      case QueryableType::List:
        {
          std::list<TObj> localList;
          this->items = std::make_shared<QueryableListData<TObj>>(localList);
        }
        break;
      case QueryableType::MultiSet:
        {
          std::multiset<TObj, TCompare> localMultiSet(compare);
          this->items = std::make_shared<QueryableMultiSetData<TObj, TCompare>>(localMultiSet);
        }
        break;
      case QueryableType::Set:
        {
          std::set<TObj, TCompare> localSet(compare);
          this->items = std::make_shared<QueryableSetData<TObj, TCompare>>(localSet);
        }
        break;
      case QueryableType::Vector:
      default:
        {
          std::vector<TObj> localVector;
          this->items = std::make_shared<QueryableVectorData<TObj>>(localVector);
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

    for (auto it = queryable.items.get()->begin(); it != queryable.items.get()->end(); it++)
    {
      this->items.get()->Add(*it);
    }
  }

  Queryable(const std::deque<TObj>& deque)
  {
    this->type = QueryableType::Deque;
    this->items = std::make_shared<QueryableDequeData<TObj>>(deque);
  }

  Queryable(const std::list<TObj>& list)
  {
    this->type = QueryableType::List;
    this->items = std::make_shared<QueryableListData<TObj>>(list);
  }

  Queryable(const std::multiset<TObj>& multiset)
  {
    this->type = QueryableType::MultiSet;
    this->items = std::make_shared<QueryableMultiSetData<TObj>>(multiset);
  }

  Queryable(const std::set<TObj>& set)
  {
    this->type = QueryableType::Set;
    this->items = std::make_shared<QueryableSetData<TObj>>(set);
  }

  Queryable(const std::vector<TObj>& vector)
  {
    this->type = QueryableType::Vector;
    this->items = std::make_shared<QueryableVectorData<TObj>>(vector);
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
    if (this->items.get()->PassesCondition(obj))
    {
      this->items.get()->Add(obj);
    }
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  std::deque<TObj, TNewAllocator> ToDeque()
  {
    std::deque<TObj, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  std::list<TObj, TNewAllocator> ToList()
  {
    std::list<TObj, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TNewCompare = std::less<TObj>, typename TNewAllocator = std::allocator<TObj>>
  std::multiset<TObj, TNewCompare, TNewAllocator> ToMultiSet()
  {
    std::multiset<TObj, TNewCompare, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TNewCompare = std::less<TObj>, typename TNewAllocator = std::allocator<TObj>>
  std::set<TObj, TNewCompare, TNewAllocator> ToSet()
  {
    std::set<TObj, TNewCompare, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.insert(item);
    }

    return newItems;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  std::vector<TObj, TNewAllocator> ToVector()
  {
    std::vector<TObj, TNewAllocator> newItems;

    for (TObj item : *this->items.get())
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj>* ToQueryableDeque()
  {
    std::deque<TObj> copy = this->ToDeque();

    this->items = std::make_shared<QueryableDequeData<TObj, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    return this;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj>* ToQueryableList()
  {
    std::list<TObj> copy = this->ToList();

    this->items = std::make_shared<QueryableListData<TObj, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    return this;
  }

  template<typename TNewCompare = std::less<TObj>, typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj>* ToQueryableMultiSet()
  {
    std::multiset<TObj> copy = this->ToMultiSet();

    this->items = std::make_shared<QueryableMultiSetData<TObj, TNewCompare, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    return this;
  }

  template<typename TNewCompare = std::less<TObj>, typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj>* ToQueryableSet()
  {
    std::set<TObj> copy = this->ToSet();

    this->items = std::make_shared<QueryableSetData<TObj, TNewCompare, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    return this;
  }

  template<typename TNewAllocator = std::allocator<TObj>>
  Queryable<TObj>* ToQueryableVector()
  {
    std::vector<TObj> copy = this->ToVector();

    this->items = std::make_shared<QueryableVectorData<TObj, TNewAllocator>>();
    for (TObj item : copy)
    {
      this->items.get()->Add(item);
    }

    return this;
  }

  bool IsEmpty()
  {
    return this->items.get()->begin() == this->items.get()->end();
  }

  TObj At(int index)
  {
    if (index < 0)
    {
      throw std::runtime_error("Index must be greater than zero");
    }

    int i = 0;
    for (TObj obj : *this->items.get())
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
    int i = 0;

    for (auto obj : *this->items.get())
    {
      (void)obj; // silence compiler
      i++;
    }

    return i;
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

  Queryable<TObj> * Where(std::function<bool(const TObj &)> condition)
  {
    this->items.get()->AddCondition(condition);
    return this;
  }

  Queryable<TObj> WhereCopy(std::function<bool(TObj)> condition)
  {
    Queryable<TObj> copy(this->GetType());

    this->ForEach([&](TObj obj)
    {
      if (condition(obj))
      {
        copy.Add(obj);
      }
    });

    return copy;
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
    for (auto it = this->items.get()->rbegin(); it != this->items.get()->rend(); it++)
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

  Queryable<TObj> * Take(int count)
  {
    if (count < 0)
    {
      return this->Skip(this->Count() + count);
    }

    int eraseFromBack = this->Count() - count;
    eraseFromBack = eraseFromBack < 0 ? 0 : eraseFromBack;

    for (int i = 0; i < eraseFromBack; i++)
    {
      // TODO --> erase method does not have great time complexity and some containers
      //   can do it in constant time. so it will be better to implement this per
      //   queryable container class

      // if the last item does not meet the condition, then it should not be considered in the count
      if (!this->items.get()->PassesCondition(*this->items.get()->rbegin()))
      {
        i--;
      }

      // TODO --> need to figure out an optimization for deciding whether its worth
      //    dropping from the back or creating a copy from the front
      //    (i.e. if count > 0.5 * size then drop from back)
      //    (i.e. if count < 16 then take from front)

      this->items.get()->RemoveLast();
    }

    return this;
  }

  Queryable<TObj> * TakeWhile(std::function<bool(TObj)> doTake)
  {
    // consider optimization of doing this without duplicate vector
    // may be better/worse depending on container size
    std::vector<TObj> copy = this->ToVector();
    this->Clear();

    for (TObj item : copy)
    {
      if (doTake(item))
      {
        this->items.get()->Add(item);
      }
      else
      {
        break;
      }
    }

    return this;
  }

  Queryable<TObj>* Skip(int count)
  {
    if (count < 0)
    {
      return this->Take(this->Count() + count);
    }

    int localSize = this->Count();
    if (count > localSize)
    {
      count = localSize;
    }

    QueryableVectorData<TObj> copy = this->items.get()->ToVector();
    this->Clear();

    int i = 0;
    for (auto it = copy.begin(); it != copy.end(); it++)
    {
      if (this->items.get()->PassesCondition(*it) && count <= i++)
      {
        this->items.get()->Add(*it);
      }
    }

    return this;
  }

  Queryable<TObj>* SkipWhile(std::function<bool(TObj)> doSkip)
  {
    // the skip and take methods need to be thought through
    // to come up with better space/time complexities
    int toDelete = 0;

    for (TObj item : *this->items.get())
    {
      if (!doSkip(item))
      {
        break;
      }

      toDelete++;
    }

    Queryable<TObj>* retval = this->Skip(toDelete);
    return retval;
  }

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
  Queryable<T>* Select(std::function<T(TObj)> retrieveValue, QueryableType returnType = QueryableType::Default)
  {
    if (returnType == QueryableType::Default)
    {
      returnType = this->type;
    }

    std::shared_ptr<Queryable<T>> data = std::make_shared<Queryable<T>>(returnType);
    this->persistentContainer.Set(data);
    std::shared_ptr<Queryable<T>> selected = this->persistentContainer.GetAs<Queryable<T>>();

    for (TObj item : *this->items.get())
    {
      selected->Add(retrieveValue(item));
    }

    return this->persistentContainer.GetAs<Queryable<T>>().get();
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
  //   2.1. the default comparator for [multi]sets is the type's less than comparison operator
  //   3. all other types use their built in optimized sorting algorithms
  Queryable<TObj>* Sort(
    std::function<bool(TObj, TObj)> comparator = [](TObj a, TObj b) { return a < b; })
  {
    switch (this->type)
    {
      case QueryableType::Set:
        {
          std::vector<TObj> copy = this->ToVector();
          this->items = std::make_shared<QueryableSetData<TObj, decltype(comparator)>>(comparator);
          for (TObj item : copy)
          {
            this->items.get()->Add(item);
          }
        }
        break;
      case QueryableType::MultiSet:
        {
          std::vector<TObj> copy = this->ToVector();
          this->items = std::make_shared<QueryableMultiSetData<TObj, decltype(comparator)>>(comparator);
          for (TObj item : copy)
          {
            this->items.get()->Add(item);
          }
        }
        break;
      case QueryableType::Deque:
      case QueryableType::List:
      case QueryableType::Vector:
      default:
        this->items.get()->Sort(comparator);
        break;
    }

    return this;
  }

  template<typename T = TObj>
  Queryable<TObj>* OrderBy(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; })
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return this->Sort([&](TObj a, TObj b){ return retrieveValue(a) < retrieveValue(b); });
  }

  template<typename T = TObj>
  Queryable<TObj>* OrderByDescending(
    std::function<T(TObj)> retrieveValue = [](TObj o) { return o; })
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return this->Sort([&](TObj a, TObj b){ return retrieveValue(b) < retrieveValue(a); });
  }

  // TODO --> is returing it ordered based on the given comparator okay?
  //          should having an implementation that doesn't change order be done?
  Queryable<TObj> * Except(
    Queryable<TObj> collection,
    std::function<bool(TObj, TObj)> comparator = [](TObj a, TObj b) { return a < b; })
  {
    // TODO --> if  nXm < max(nlog(n), mlog(m)) then sorting is not worth it
    // TODO --> don't call toVector if the type is already a random access iterator

    std::vector<TObj> localSorted = this->Sort(comparator)->ToVector();
    std::vector<TObj> inputSorted = collection.Sort(comparator)->ToVector();

    int localCount = localSorted.size();
    int inputCount = inputSorted.size();

    if (localCount <= 0 || inputCount <= 0)
    {
      return this;
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
    while (localIndex < localCount)
    {
      if (!equal(localSorted[localIndex], inputSorted[inputCount - 1]))
      {
        result.push_back(localSorted[localIndex++]);
      }
    }

    // TODO --> figure out a better way to do this wrt time & memory
    // TODO --> figure out if its better to return self or a new object
    this->items.get()->Clear();
    for (TObj obj : result)
    {
      this->items.get()->Add(obj);
    }

    return this;
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
    typename TResult,
    typename TResultCompare = std::less<TResult>>
  Queryable<TResult, TResultCompare> * Join(
    Queryable<TJoinObj> * collection,
    std::function<TJoinOn(TObj)> getLocalJoinOn,
    std::function<TJoinOn(TJoinObj)> getInputJoinOn,
    std::function<TResult(TObj, TJoinObj)> createFrom,
    TResultCompare outCompare = TResultCompare(),
    QueryableType returnType = QueryableType::Default)
  {
    static_assert(is_less_comparable<TJoinOn>::value, "Type must be 'less than' comparable");
    typedef Queryable<TResult, TResultCompare> TReturn;

    QueryableType type = returnType == QueryableType::Default ? this->type : returnType;
    std::shared_ptr<TReturn> data = std::make_shared<TReturn>(type, outCompare);
    this->persistentContainer.Set(data);
    std::shared_ptr<TReturn> result = this->persistentContainer.GetAs<TReturn>();

    if (!collection)
    {
      return result.get();
    }

    // Sort each collection on passed in key getters                             ( + time complexity: nlog(n) )
    //   this allows us to only need to fully iterate over each collection once  ( + time complexity: n )
    //   and chunks of non-joinable data can be easily bypassed                  ( + non-generalizable benefit )
    // Change inner collection to vector to gaurantee constant time indexing     ( - requires extra space )
    //   may want to only do this if collection type does not have constant time indexing
    this->OrderBy(getLocalJoinOn);
    std::vector<TJoinObj> inputSorted = collection->OrderBy(getInputJoinOn)->ToVector();
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

    return result.get();
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


  template<
    typename TKey,
    typename TData = TObj,
    typename TKeyCompare = std::less<TKey>,
    typename TDataCompare = std::less<TData>>
  Queryable<IGroup<TKey, TObj, TKeyCompare, TDataCompare>> * GroupBy(
    std::function<TKey(TObj)> getKey,
    QueryableType storageType = QueryableType::Default,
    TDataCompare dataCompare = TDataCompare(),
    TKeyCompare keyCompare = TKeyCompare()
  )
  {
    typedef Group<TKey, TObj, std::deque, TKeyCompare, TDataCompare> TGroupDeque;
    typedef Group<TKey, TObj, std::list, TKeyCompare, TDataCompare> TGroupList;
    typedef Group<TKey, TObj, std::multiset, TKeyCompare, TDataCompare> TGroupMultiSet;
    typedef Group<TKey, TObj, std::set, TKeyCompare, TDataCompare> TGroupSet;
    typedef Group<TKey, TObj, std::vector, TKeyCompare, TDataCompare> TGroupVector;
    typedef Queryable<TGroupDeque> TReturnDeque;
    typedef Queryable<TGroupList> TReturnList;
    typedef Queryable<TGroupMultiSet> TReturnMultiSet;
    typedef Queryable<TGroupSet> TReturnSet;
    typedef Queryable<TGroupVector> TReturnVector;

    typedef IGroup<TKey, TObj, TKeyCompare, TDataCompare> TGroup;
    typedef Queryable<TGroup> TReturn;

    QueryableType type = storageType == QueryableType::Default ? this->type : storageType;
    TReturn * queryableGroups = NULL;

    switch (type) {
      case QueryableType::Deque:
        {
          std::shared_ptr<TReturnDeque> data = std::make_shared<TReturnDeque>(type);
          this->persistentContainer.Set(data);
          queryableGroups = this->persistentContainer
            .GetAs<TReturnDeque>()
            .get()
            ->template Cast<TGroup>();
        }
        break;
      case QueryableType::List:
        {
          std::shared_ptr<TReturnList> data = std::make_shared<TReturnList>(type);
          this->persistentContainer.Set(data);
          queryableGroups = this->persistentContainer
            .GetAs<TReturnList>()
            .get()
            ->template Cast<TGroup>();
        }
        break;
      case QueryableType::MultiSet:
        {
          std::shared_ptr<TReturnMultiSet> data = std::make_shared<TReturnMultiSet>(type);
          this->persistentContainer.Set(data);
          queryableGroups = this->persistentContainer
            .GetAs<TReturnMultiSet>()
            .get()
            ->template Cast<TGroup>();
        }
        break;
      case QueryableType::Set:
        {
          std::shared_ptr<TReturnSet> data = std::make_shared<TReturnSet>(type);
          this->persistentContainer.Set(data);
          queryableGroups = this->persistentContainer
            .GetAs<TReturnSet>()
            .get()
            ->template Cast<TGroup>();
        }
        break;
      case QueryableType::Vector:
        {
          std::shared_ptr<TReturnVector> data = std::make_shared<TReturnVector>(type);
          this->persistentContainer.Set(data);
          queryableGroups = this->persistentContainer
            .GetAs<TReturnVector>()
            .get()
            ->template Cast<TGroup>();
        }
        break;
      default:
        return NULL;
    }

    for (TObj item : *this->items.get())
    {
      TKey key = getKey(item);

      if (!queryableGroups->Any([&](TGroup group) { return group.GetKey() == key; }))
      {
        // these ugly switch statements are telling me that I am missing a
        //   layer of abstraction or a key architectural feature
        switch (type)
        {
          case QueryableType::Deque:
            queryableGroups->Add(TGroupDeque(key, type, keyCompare, dataCompare));
            break;
          case QueryableType::List:
            queryableGroups->Add(TGroupList(key, type, keyCompare, dataCompare));
            break;
          case QueryableType::MultiSet:
            queryableGroups->Add(TGroupMultiSet(key, type, keyCompare, dataCompare));
            break;
          case QueryableType::Set:
            queryableGroups->Add(TGroupSet(key, type, keyCompare, dataCompare));
            break;
          case QueryableType::Vector:
          default:
            queryableGroups->Add(TGroupVector(key, type, keyCompare, dataCompare));
            break;
        }
      }

      queryableGroups
        ->First([&](TGroup group)
        {
          TKey groupKey = group.GetKey();
          return !(keyCompare(groupKey, key) || keyCompare(key, groupKey));
        })
        .Add(item);
    }

    return queryableGroups->Sort();
  }
};

#endif
