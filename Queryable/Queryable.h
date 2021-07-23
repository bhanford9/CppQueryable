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
#include "DeferredUtilities/PersistentContainer.h"
#include "QueryableData/IQueryableData.h"
#include "QueryableData/QueryableDequeData.h"
#include "QueryableData/QueryableListData.h"
#include "QueryableData/QueryableMultiSetData.h"
#include "QueryableData/QueryableSetData.h"
#include "QueryableData/QueryableVectorData.h"
#include "QueryableType.h"
#include "TypeConstraintUtil.h"

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
  std::shared_ptr<IQueryableData<TObj>> items;
  PersistentContainer selected;
  Condition<TObj> condition;
  QueryableType type;

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

    this->condition.MarkApplied();
    return newCount;
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
  Queryable(QueryableType type = QueryableType::Vector)
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
          std::multiset<TObj> localMultiSet;
          this->items = std::make_shared<QueryableMultiSetData<TObj>>(localMultiSet);
        }
        break;
      case QueryableType::Set:
        {
          std::set<TObj> localSet;
          this->items = std::make_shared<QueryableSetData<TObj>>(localSet);
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
  {
    this->items = queryable.items;
    this->selected = queryable.selected;
    this->condition = queryable.condition;
    this->type = queryable.type;
  }

  Queryable<TObj> * Applied()
  {
    this->ApplyCondition();
    return this;
  }

  void Clear()
  {
    this->items.get()->Clear();
    this->condition.MarkApplied(false);
  }

  void Add(TObj obj)
  {
    this->items.get()->Add(obj);
    this->condition.MarkApplied(false);
  }

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

    this->condition.MarkApplied();
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

    this->condition.MarkApplied();
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

    this->condition.MarkApplied();
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

    this->condition.MarkApplied();
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

    this->condition.MarkApplied();
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
      if (this->condition(item) && condition(item))
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
      if (this->condition(item))
      {
        action(item);
      }
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

  Queryable<TObj> * Where(std::function<bool(TObj)> condition, bool apply = false)
  {
    this->condition += condition;
    return apply ? this->Applied() : this;
  }

  TObj First(std::function<bool(TObj)> condition)
  {
    for (TObj item : *this->items.get())
    {
      if (this->condition(item) && condition(item))
      {
        return item;
      }
    }

    throw std::runtime_error("No item fitting the condition was found.");
  }

  TObj First()
  {
    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        return item;
      }
    }

    throw std::runtime_error("Cannot get first item of empty collection.");
  }

  TObj Last(std::function<bool(TObj)> condition)
  {
    for (auto it = this->items.get()->rbegin(); it != this->items.get()->rend(); it++)
    {
      if (this->condition(*it) && condition(*it))
      {
        return *it;
      }
    }

    throw std::runtime_error("No item fitting the condition was found.");
  }

  TObj Last()
  {
    for (auto it = this->items.get()->rbegin(); it != this->items.get()->rend(); it++)
    {
      if (this->condition(*it))
      {
        return *it;
      }
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
      if (!this->condition(*this->items.get()->rbegin()))
      {
        i--;
      }

      // TODO --> need to figure out an optimization for deciding whether its worth
      //    dropping from the back or creating a copy from the front
      //    (i.e. if count > 0.5 * size then drop from back)
      //    (i.e. if count < 16 then take from front)

      this->items.get()->RemoveLast();
      // this->items->erase(--this->items->end());
    }

    this->condition.MarkApplied();
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
      if (this->condition(item))
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
    }

    this->condition.MarkApplied();
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

    for (auto it = copy.begin() + count; it != copy.end(); it++)
    {
      this->items.get()->Add(*it);
    }

    this->condition.MarkApplied();
    return this;
  }

  Queryable<TObj>* SkipWhile(std::function<bool(TObj)> doSkip)
  {
    // the skip and take methods need to be thought through
    // to come up with better space/time complexities
    int toDelete = 0;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        if (!doSkip(item))
        {
          break;
        }

        toDelete++;
      }
    }

    Queryable<TObj>* retval = this->Skip(toDelete);
    this->condition.MarkApplied();
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
    if (preserveFilter)
    {
      this->condition.MarkApplied(false);
    }

    for (TObj obj : collection)
    {
      if (this->condition(obj))
      {
        this->items.get()->Add(obj);
      }
    }

    return this;
  }

  template<typename T>
  T Sum(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_aggregatable<T>::value, "Type must be implement the '+=' operator");

    T sum = T();

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        sum += retrieveValue(item);
      }
    }

    return sum;
  }

  template<typename T>
  TObj MaxItem(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T maxValue = T();
    TObj maxItem = TObj();

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
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
    }

    if (isFirst)
    {
      throw std::runtime_error("Cannot find maximum item of an empty colleciton.");
    }

    return maxItem;
  }

  template<typename T>
  T Max(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MaxItem(retrieveValue));
  }

  template<typename T>
  T Max(std::function<T(TObj)> retrieveValue, T startSeed)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T max = startSeed;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        T newValue = retrieveValue(item);

        if (max < newValue)
        {
          max = newValue;
        }
      }
    }

    return max;
  }

  template<typename T>
  TObj MinItem(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T minValue = T();
    TObj minItem = TObj();

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
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
    }

    if (isFirst)
    {
      throw std::runtime_error("Cannot find minimum item of an empty colleciton.");
    }

    return minItem;
  }

  template<typename T>
  T Min(std::function<T(TObj)> retrieveValue)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");
    return retrieveValue(this->MinItem(retrieveValue));
  }

  template<typename T>
  T Min(std::function<T(TObj)> retrieveValue, T startSeed)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T min = startSeed;

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        T newValue = retrieveValue(item);

        if (newValue < min)
        {
          min = newValue;
        }
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
      if (this->condition(item))
      {
        sum += retrieveValue(item);
        count++;
      }
    }

    // consider alternative way of handling count of zero

    return count > 0 ? sum / count : 0;
  }

  bool Any(std::function<bool(TObj)> condition)
  {
    for (TObj item : *this->items.get())
    {
      if (this->condition(item) && condition(item))
      {
        return true;
      }
    }

    return false;
  }

  bool All(std::function<bool(TObj)> condition)
  {
    for (TObj item : *this->items.get())
    {
      if (this->condition(item) && !condition(item))
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
    this->selected.Set(data);
    std::shared_ptr<Queryable<T>> selected = this->selected.GetAs<Queryable<T>>();

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        selected->Add(retrieveValue(item));
      }
    }

    return this->selected.GetAs<Queryable<T>>().get();
  }

  bool Contains(TObj obj)
  {
    static_assert(is_equatable<TObj>::value, "Item must be equatable");

    for (TObj item : *this->items.get())
    {
      if (this->condition(item) && item == obj)
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
    this->ApplyCondition();

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
    this->ApplyCondition();

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

  TObj Aggregate(std::function<TObj(TObj, TObj)> accumulate, TObj * seed = NULL)
  {
    TObj aggregatedValue = TObj();

    if (seed != NULL)
    {
      aggregatedValue = *seed;
    }

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        aggregatedValue = accumulate(aggregatedValue, item);
      }
    }

    return aggregatedValue;
  }

  template<typename T>
  T Aggregate(std::function<T(T, TObj)> accumulate, T * seed = NULL)
  {
    T aggregatedValue = T();

    if (seed != NULL)
    {
      aggregatedValue = *seed;
    }

    for (TObj item : *this->items.get())
    {
      if (this->condition(item))
      {
        aggregatedValue = accumulate(aggregatedValue, item);
      }
    }

    return aggregatedValue;
  }

  template<typename TFinalizer>
  TFinalizer Aggregate(
    std::function<TObj(TObj, TObj)> accumulate,
    std::function<TFinalizer(TObj)> finalizer,
    TObj * seed = NULL)
  {
    return finalizer(this->Aggregate(accumulate, seed));
  }

  template<typename T, typename TFinalizer>
  TFinalizer Aggregate(
    std::function<T(T, TObj)> accumulate,
    std::function<TFinalizer(T)> finalizer,
    TObj * seed = NULL)
  {
    return finalizer(this->Aggregate<T>(accumulate, seed));
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
