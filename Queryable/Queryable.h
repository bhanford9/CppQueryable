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

#include "DeferredUtilities/Condition.h"
#include "TypeConstraintUtil.h"
#include "QueryableData/IQueryableData.h"
#include "QueryableData/QueryableVectorData.h"

template<typename TObj>
class Queryable
{
  // static_assert(can_iterate<TIterable<TObj>>::value, "Class must be able to be iterated over");
  // static_assert(has_size_method<TIterable<TObj>>::value, "Class must have a size method");

  // TODO --> inherit Queryable with child classes that override specific methods for optimization per container type:
  //    vector, list, deque, set, multiset, forward_list, etc.

  // forward_list not currently supported because it does not have a size method


  // TODO --> defered execution for WHERE so that doing .WHERE(X).FOREACH(Y) only iterates over the set once

protected:
  std::unique_ptr<IQueryableData<TObj>> items;
  Condition<TObj> condition;

  // should avoid using this method if possible
  int ApplyCondition()
  {
    if (!this->condition)
    {
      // if no condition has been specified just return the size of the collection
      return this->items.get()->Count();
    }

    std::vector<TObj> copy = this->ToVector();
    this->Clear();
    int newCount = 0;

    for (TObj obj : copy)
    {
      if (this->condition(obj))
      {
        this->items.get()->Add(obj);
        newCount++;
      }
    }

    return newCount;
  }

public:
  Queryable() { }

  std::vector<TObj> ToVector()
  {
    std::vector<TObj> newItems;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        newItems.push_back(item);
      }
    }

    return newItems;
  }

  std::set<TObj> ToSet()
  {
    std::set<TObj> newItems;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        newItems.insert(item);
      }
    }

    return newItems;
  }

  std::multiset<TObj> ToMultiSet()
  {
    std::multiset<TObj> newItems;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        newItems.insert(item);
      }
    }

    return newItems;
  }

  std::deque<TObj> ToDeque()
  {
    std::deque<TObj> newItems;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        newItems.push_back(item);
      }
    }

    return newItems;
  }

  std::list<TObj> ToList()
  {
    std::list<TObj> newItems;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        newItems.push_back(item);
      }
    }

    return newItems;
  }

  template <typename T>
  T* As()
  {
    return static_cast<T*>(this);
  }

  virtual TObj At(int index)
  {
    if (index < 0)
    {
      throw std::runtime_error("Index must be greater than zero");
    }

    int i = 0;
    for (TObj obj : *this->items.get())
    {
      // `i` purposefully not incremented if condtion is false
      if (this->condition(obj) && index == i++)
      {
        return obj;
      }
    }

    throw std::runtime_error("Specified index was outside the bounds of the container");
  }

  int Count()
  {
    return this->ApplyCondition();
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

  Queryable<TObj> * OnEach(std::function<void(TObj&)> action)
  {
    // TODO --> evaluate if it would be useful to create an implementation of this for sets

    for (TObj & item : *this->items.get())
    {
      action(item);
    }

    return this;
  }

  Queryable<TObj> * Where(std::function<bool(TObj)> condition)
  {
    // QueryableVectorData<TObj> copy = this->items.get()->ToVector();
    // this->items.get()->Clear();
    //
    // for (TObj item : copy)
    // {
    //   if (condition(item))
    //   {
    //     this->items.get()->Add(item);
    //   }
    // }

    this->condition += condition;
    return this;
  }

  TObj First(std::function<bool(TObj)> condition)
  {
    if (this->Count() == 0)
    {
      throw std::runtime_error("Cannot get element of empty collection");
    }

    for (auto item : *this->items)
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
    if (this->Count() == 0)
    {
      throw std::runtime_error("Cannot get first element of empty collection");
    }

    return *this->items.get()->begin();
  }

  TObj Last(std::function<bool(TObj)> condition)
  {
    int count = this->Count();

    if (count == 0)
    {
      throw std::runtime_error("Cannot get element of empty collection");
    }

    for (auto it = this->items.get()->rbegin(); it != this->items.get()->rend(); it++)
    {
      TObj item = *it;

      if (condition(item))
      {
        return item;
      }
    }

    throw std::runtime_error("No item fitting the condition was found.");
  }

  TObj Last()
  {
    if (this->Count() == 0)
    {
      throw std::runtime_error("Cannot get last element of empty collection");
    }

    return *this->items.get()->rbegin();
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
      this->items.get()->RemoveLast();
      // this->items->erase(--this->items->end());
    }

    return this;
  }

  Queryable<TObj> * TakeWhile(std::function<bool(TObj)> doTake)
  {
    // done this way to allow returning the same container that was used to call this method
    // need to refactor with implementations of container-specific queriable classes.
    // each container queriable can have its own implementation of adding members

    int toTake = 0;

    for (TObj item : *this->items.get())
    {
      if (!doTake(item))
      {
        break;
      }

      toTake++;
    }

    return this->Take(toTake);
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
    this->items.get()->Clear();

    for (auto it = copy.begin() + count; it != copy.end(); it++)
    {
      TObj value = *it;
      this->items.get()->Add(value);
    }

    return this;
  }

  Queryable<TObj>* SkipWhile(std::function<bool(TObj)> doSkip)
  {
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

  // Wait to do this until after each container has its child class because they'll
  //  implement individual appenders.
  //
  // For this and similar methods that require optimizations, we can have the public
  //  method not include the parameter for the optimization and then call an internal
  //  overriden method that handles the optimization and returns to the parent.
  // Queryable<TObj>* Concat(TIterable<TObj> collection, std::function<void(TIterable<TObj>*, TObj)> appender)
  // {
  //   for (TObj obj : collection)
  //   {
  //     appender(&this->items, obj);
  //   }
  //
  //   Queryable<TObj, TIterable> queryableItems(this->items);
  //   return queryableItems;
  // }

  template<typename T>
  T Sum(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_aggregatable<T>::value, "Type must be implement the '+=' operator");

    T sum = 0;

    for (TObj item : *this->items.get())
    {
      sum += retrieveValue(item);
    }

    return sum;
  }

  template<typename T>
  T Max(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T max;

    for (TObj item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (isFirst)
      {
        isFirst = false;
        max = newValue;
      }
      else if (max < newValue)
      {
        max = newValue;
      }
    }

    return max;
  }


  template<typename T>
  T Max(T startSeed, std::function<T(TObj)> retrieveValue)
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

  template<typename T>
  T Min(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T min;

    for (TObj item : *this->items.get())
    {
      T newValue = retrieveValue(item);

      if (isFirst)
      {
        isFirst = false;
        min = newValue;
      }
      else if (newValue < min)
      {
        min = newValue;
      }
    }

    return min;
  }

  template<typename T>
  T Min(T startSeed, std::function<T(TObj)> retrieveValue)
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

  template<typename T>
  double Average(std::function<T(TObj)> retrieveValue)
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

  bool Any(std::function<bool(TObj)> clause)
  {
    for (TObj item : *this->items.get())
    {
      if (clause(item))
      {
        return true;
      }
    }

    return false;
  }

  bool All(std::function<bool(TObj)> clause)
  {
    for (TObj item : *this->items.get())
    {
      if (!clause(item))
      {
        return false;
      }
    }

    return true;
  }

  template<typename T>
  Queryable<T> Select(std::function<T(TObj)> retrieveValue)
  {
    QueryableVectorData<T> * selected = std::make_shared<QueryableVectorData<T>>().get();

    for (TObj item : *this->items)
    {
      this->selected->Add(retrieveValue(item));
    }

    // test if this polymorphically works due to the constructor
    return selected;
  }

  bool Contains(TObj obj)
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

  template<typename T>
  Queryable<TObj>* OrderBy(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    std::sort(
      this->items.get()->begin(),
      this->items.get()->end(),
      [&](TObj a, TObj b){ return retrieveValue(a) < retrieveValue(b); });

    return this;
  }

  template<typename T>
  Queryable<TObj>* OrderByDescending(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    std::sort(
      this->items.get()->begin(),
      this->items.get()->end(),
      [&](TObj a, TObj b){ return !(retrieveValue(a) < retrieveValue(b)); });

    return this;
  }

  // Queryable<TObj, std::vector> Except(TIterable<TObj> collection)
  // {
  //   static_assert(is_equatable<TObj>::value, "Item must be equatable");
  //   static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");
  //
  //   Queryable<TObj, TIterable> inputCollection(collection);
  //
  //   std::vector<TObj> localSorted = this->OrderBy<TObj>([](TObj obj){ return obj; }).ToVector();
  //   std::vector<TObj> inputSorted = inputCollection.OrderBy<TObj>([](TObj obj){ return obj; }).ToVector();
  //
  //   int localCount = this->Count();
  //   int inputCount = inputCollection.Count();
  //
  //   TObj localMax = localSorted[localCount - 1];
  //   TObj inputMax = inputSorted[inputCount - 1];
  //
  //   std::vector<TObj> result;
  //
  //   int localIndex = 0;
  //   int inputIndex = 0;
  //
  //   while (inputIndex < inputCount && localIndex < localCount)
  //   {
  //     TObj localItem = localSorted[localIndex];
  //     TObj inputItem = inputSorted[inputIndex];
  //
  //     if (localItem < inputItem)
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
  //   Queryable<TObj, std::vector> output(result);
  //   return output;
  // }

  TObj Aggregate(std::function<TObj(TObj, TObj)> accumulate)
  {
    static_assert(is_aggregatable<TObj>::value, "Type must be able to be aggregated");

    int count = this->Count();

    if (count == 0)
    {
      throw std::runtime_error("Cannot aggregate empty collection");
    }

    TObj aggregatedValue = this->First();

    for (int i = 1; i < count; i++)
    {
      aggregatedValue += accumulate(aggregatedValue, this->At(i));
    }

    return aggregatedValue;
  }

  TObj Aggregate(TObj * seed, std::function<TObj(TObj, TObj)> accumulate)
  {
    static_assert(is_aggregatable<TObj>::value, "Type must be able to be aggregated (+= operator)");
    static_assert(is_addable<TObj>::value, "Type must be able to be aggregated (+ operator)");

    return seed != NULL ? (seed + this->Aggregate(accumulate)) : this->Aggregate(accumulate);
  }

  template<typename T>
  T Aggregate(T * seed, std::function<T(T, TObj)> accumulate)
  {
    static_assert(is_aggregatable<T>::value, "Type must be able to be aggregated (+= operator)");
    static_assert(is_addable<T>::value, "Type must be able to be aggregated (+ operator)");

    int count = this->Count();

    T aggregatedValue = *seed;

    for (int i = 1; i < count; i++)
    {
      aggregatedValue = accumulate(aggregatedValue, this->At(i));
    }

    return aggregatedValue;
  }

  template<typename TFinalizer>
  TFinalizer Aggregate(
    TObj * seed,
    std::function<TObj(TObj, TObj)> accumulate,
    std::function<TFinalizer(TObj)> finalizer)
  {
    static_assert(is_aggregatable<TObj>::value, "Type must be able to be aggregated (+= operator)");
    static_assert(is_addable<TObj>::value, "Type must be able to be aggregated (+ operator)");

    return finalizer(this->Aggregate(seed, accumulate));
  }

  template<typename T, typename TFinalizer>
  TFinalizer Aggregate(
    T * seed,
    std::function<T(T, TObj)> accumulate,
    std::function<TFinalizer(T)> finalizer)
  {
    static_assert(is_aggregatable<T>::value, "Type must be able to be aggregated (+= operator)");
    static_assert(is_addable<T>::value, "Type must be able to be aggregated (+ operator)");

    return finalizer(this->Aggregate<T>(seed, accumulate));
  }
  //
  // template<typename TJoinObj, typename TJoinOn, typename TOut>
  // Queryable<TOut, std::vector> Join(
  //   TIterable<TJoinObj> collection,
  //   std::function<TJoinOn(TObj)> getLocalJoinOn,
  //   std::function<TJoinOn(TJoinObj)> getInputJoinOn,
  //   std::function<TOut(TObj, TJoinObj)> createFrom)
  // {
  //   static_assert(is_equatable<TJoinOn>::value, "Type must be equatable");
  //   static_assert(is_less_comparable<TJoinOn>::value, "Type must be 'less than' comparable");
  //
  //   std::vector<TOut> result;
  //
  //   Queryable<TJoinObj, TIterable> inputCollection(collection);
  //   int inputSize = inputCollection.Count();
  //   int localSize = this->Count();
  //
  //   if (localSize == 0 || inputSize == 0)
  //   {
  //     return result;
  //   }
  //
  //   std::vector<TObj> localSorted = this->OrderBy(getLocalJoinOn).ToVector();
  //   std::vector<TJoinObj> inputSorted = inputCollection.OrderBy(getInputJoinOn).ToVector();
  //
  //   int inputIndex = 0;
  //
  //   for (int i = 0; i < localSize; i++) // TObj localItem : localSorted)
  //   {
  //     TObj localItem = localSorted[i];
  //     TJoinOn localValue;
  //     TJoinOn inputValue;
  //
  //     do
  //     {
  //       TJoinObj inputItem = inputSorted[inputIndex];
  //
  //       localValue = getLocalJoinOn(localItem);
  //       inputValue = getInputJoinOn(inputItem);
  //
  //       if (localValue == inputValue)
  //       {
  //         int sameValueIndex = inputIndex;
  //         TJoinObj sameValueItem = inputSorted[sameValueIndex];
  //         while (getInputJoinOn(sameValueItem) == inputValue)
  //         {
  //           result.push_back(createFrom(localItem, sameValueItem));
  //
  //           if (sameValueIndex == inputSize - 1)
  //           {
  //             break;
  //           }
  //
  //           sameValueItem = inputSorted[++sameValueIndex];
  //         }
  //       }
  //
  //       if (inputValue < localValue)
  //       {
  //         inputIndex++;
  //       }
  //
  //     } while (inputValue < localValue && inputIndex < inputSize);
  //   }
  //
  //   Queryable<TOut, std::vector> output(result);
  //   return output;
  // }
};

#endif
