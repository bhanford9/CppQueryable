#ifndef CPPQUERYABLE_QUERYABLE_QUERYABLE_H
#define CPPQUERYABLE_QUERYABLE_QUERYABLE_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <set>
#include <vector>

#include "TypeConstraintUtil.h"

template<typename TObj, template<typename...> typename TIterable>
class Queryable
{
  static_assert(can_iterate<TIterable<TObj>>::value, "Class must be able to be iterated over");
  static_assert(has_size_method<TIterable<TObj>>::value, "Class must have a size method");

  // TODO --> inherit Queryable with child classes that override specific methods for optimization per container type:
  //    vector, list, deque, set, multiset, forward_list, etc.

  // forward_list not currently supported because it does not have a size method

protected:
  TIterable<TObj> items;

public:
  Queryable() { }
  Queryable(TIterable<TObj> items)
  {
    this->Initialize(items);
  }

  void Initialize(TIterable<TObj> items)
  {
    this->items = items;
  }

  TIterable<TObj> GetContainer()
  {
    return this->items;
  }

  std::vector<TObj> ToVector()
  {
    std::vector<TObj> newItems;

    for (TObj item : this->items)
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  std::set<TObj> ToSet()
  {
    std::set<TObj> newItems;

    for (TObj item : this->items)
    {
      newItems.insert(item);
    }

    return newItems;
  }

  std::multiset<TObj> ToMultiSet()
  {
    std::multiset<TObj> newItems;

    for (TObj item : this->items)
    {
      newItems.insert(item);
    }

    return newItems;
  }

  std::deque<TObj> ToDeque()
  {
    std::deque<TObj> newItems;

    for (TObj item : this->items)
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  std::list<TObj> ToList()
  {
    std::list<TObj> newItems;

    for (TObj item : this->items)
    {
      newItems.push_back(item);
    }

    return newItems;
  }

  TObj At(int index)
  {
    // Since only random access iterators provide + and - operators, the library provides two
    // function templates advance and distance. These function templates use + and - for random
    // access iterators (and are, therefore, constant time for them); for input, forward and
    // bidirectional iterators they use ++ to provide linear time implementations.

    int count = this->Count();

    if (count <= index)
    {
      throw std::runtime_error("Specified index was greater than the size of the collection");
    }

    if (count < 0)
    {
      throw std::runtime_error("Index must be greater than zero");
    }

    auto it = this->items.begin();
    std::advance(it, index);
    return *it;
  }

  int Count()
  {
    // distance is a linear count. may be necessary for child classes that dont hold size member
    // return std::distance(this->items.begin(), this->items.end());
    return this->items.size();
  }

  int CountIf(std::function<bool(TObj)> condition)
  {
    int count = 0;

    for (TObj item : this->items)
    {
      if (condition(item))
      {
        count++;
      }
    }

    return count;
  }

  void ForEach(std::function<void(TObj)> clause)
  {
    for (TObj item : this->items)
    {
      clause(item);
    }
  }

  Queryable<TObj, std::vector> OnEach(std::function<TObj(TObj)> clause)
  {
    std::vector<TObj> newItems;

    for (TObj item : this->items)
    {
      newItems.push_back(clause(item));
    }

    Queryable<TObj, std::vector> queryableItems(newItems);
    return queryableItems;
  }

  Queryable<TObj, std::vector> Where(std::function<bool(TObj)> clause)
  {
    std::vector<TObj> newItems;

    for (TObj item : this->items)
    {
      if (clause(item))
      {
        newItems.push_back(item);
      }
    }

    Queryable<TObj, std::vector> queryableItems(newItems);
    return queryableItems;
  }

  TObj * First(std::function<bool(TObj)> clause)
  {
    if (this->Count() == 0)
    {
      throw std::runtime_error("Cannot get element of empty collection");
    }

    for (TObj item : this->items)
    {
      if (clause(item))
      {
        return &item;
      }
    }

    return NULL;
  }

  TObj First()
  {
    if (this->Count() == 0)
    {
      throw std::runtime_error("Cannot get first element of empty collection");
    }

    return *this->items.begin();
  }

  TObj * Last(std::function<bool(TObj)> clause)
  {
    for (int i = this->count() - 1; i >= 0; i--)
    {
      if (clause(this->items[i]))
      {
        return &this->items[i];
      }
    }

    return NULL;
  }

  TObj * Last()
  {
    int count = this->Count();
    if (count > 0)
    {
      return this->items[count - 1];
    }

    return NULL;
  }

  Queryable<TObj, std::vector> Take(int count)
  {
    std::vector<TObj> newItems;

    int i = 0;
    for (TObj item : this->items)
    {
      if (i++ > count)
      {
        break;
      }

      newItems.push_back(item);
    }

    Queryable<TObj, std::vector> queryableItems(newItems);
    return queryableItems;
  }

  Queryable<TObj, std::vector> TakeWhile(std::function<bool(TObj)> doTake)
  {
    std::vector<TObj> newItems;

    for (TObj item : this->items)
    {
      if (!doTake(item))
      {
        break;
      }

      newItems.push_back(item);
    }

    Queryable<TObj, std::vector> queryableItems(newItems);
    return queryableItems;
  }

  Queryable<TObj, TIterable> Skip(int count)
  {
    return Queryable<TObj, TIterable>(this->items.erase(this->items.begin(), this->items.begin() + count));
  }

  Queryable<TObj, TIterable> SkipWhile(std::function<bool(TObj)> doSkip)
  {
    int toDelete = 0;

    for (TObj item : this->items)
    {
      if (doSkip(item))
      {
        toDelete++;
      }
    }

    return this->Skip(toDelete);
  }

  bool Equal(TIterable<TObj> collection)
  {
    static_assert(is_equatable<TObj>::value, "Type must be equatable");

    int localCount = this->Count();
    int inputCount = Queryable<TObj, TIterable>(collection).Count();

    if (localCount == inputCount)
    {
      for (int i = 0; i < localCount; i++)
      {
        if (!(this->items[i] == collection[i]))
        {
          return false;
        }
      }
    }

    return true;
  }

  Queryable<TObj, TIterable> Concat(TIterable<TObj> collection, std::function<void(TIterable<TObj>*, TObj)> appender)
  {
    for (TObj obj : collection)
    {
      appender(&this->items, obj);
    }

    Queryable<TObj, TIterable> queryableItems(this->items);
    return queryableItems;
  }

  template<typename T>
  T Sum(std::function<T(TObj)> clause)
  {
    static_assert(std::is_arithmetic<T>::value, "Type must be numeric");

    T sum = 0;

    for (TObj item : this->items)
    {
      sum += clause(item);
    }

    return sum;
  }

  template<typename T>
  T Max(std::function<T(TObj)> clause)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T max;

    for (TObj item : this->items)
    {
      T newValue = clause(item);

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
  T Max(T startSeed, std::function<T(TObj)> clause)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T max = startSeed;

    for (TObj item : this->items)
    {
      T newValue = clause(item);

      if (max < newValue)
      {
        max = newValue;
      }
    }

    return max;
  }

  template<typename T>
  T Min(std::function<T(TObj)> clause)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    bool isFirst = true;
    T min;

    for (TObj item : this->items)
    {
      T newValue = clause(item);

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
  T Min(T startSeed, std::function<T(TObj)> clause)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    T min = startSeed;

    for (TObj item : this->items)
    {
      T newValue = clause(item);

      if (newValue < min)
      {
        min = newValue;
      }
    }

    return min;
  }

  template<typename T>
  double Average(std::function<T(TObj)> clause)
  {
    static_assert(std::is_arithmetic<T>::value, "Type must be numeric");

    double sum = 0;
    ulong count = 0;

    for (TObj item : this->items)
    {
      sum += clause(item);
      count++;
    }

    return count > 0 ? sum / count : 0;
  }

  bool Any(std::function<bool(TObj)> clause)
  {
    for (TObj item : this->items)
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
    for (TObj item : this->items)
    {
      if (!clause(item))
      {
        return false;
      }
    }

    return true;
  }

  template<typename T>
  Queryable<T, std::vector> Select(std::function<T(TObj)> clause)
  {
    std::vector<T> selected;

    for (TObj item : this->items)
    {
      selected.push_back(clause(item));
    }

    return selected;
  }

  bool Contains(TObj obj)
  {
    static_assert(is_equatable<TObj>::value, "Item must be equatable");

    for (TObj item : this->items)
    {
      if (item == obj)
      {
        return true;
      }
    }

    return false;
  }

  template<typename T>
  Queryable<TObj, std::vector> OrderBy(std::function<T(TObj)> clause)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    std::vector<TObj> sorted = this->items;
    std::sort(sorted.begin(), sorted.end(), [&](TObj a, TObj b){ return clause(a) < clause(b); });

    Queryable<TObj, std::vector> queryableItems(sorted);
    return queryableItems;
  }

  template<typename T>
  Queryable<TObj, std::vector> OrderByDescending(std::function<T(TObj)> clause)
  {
    static_assert(is_less_comparable<T>::value, "Type must be 'less than' comparable");

    std::vector<TObj> sorted = this->items;
    std::sort(sorted.begin(), sorted.end(), [&](TObj a, TObj b){ return !(clause(a) < clause(b)); });

    Queryable<TObj, std::vector> queryableItems(sorted);
    return queryableItems;
  }

  Queryable<TObj, std::vector> Except(TIterable<TObj> collection)
  {
    static_assert(is_equatable<TObj>::value, "Item must be equatable");
    static_assert(is_less_comparable<TObj>::value, "Type must be 'less than' comparable");

    Queryable<TObj, TIterable> inputCollection(collection);

    std::vector<TObj> localSorted = this->OrderBy<TObj>([](TObj obj){ return obj; }).ToVector();
    std::vector<TObj> inputSorted = inputCollection.OrderBy<TObj>([](TObj obj){ return obj; }).ToVector();

    int localCount = this->Count();
    int inputCount = inputCollection.Count();

    TObj localMax = localSorted[localCount - 1];
    TObj inputMax = inputSorted[inputCount - 1];

    std::vector<TObj> result;

    int localIndex = 0;
    int inputIndex = 0;

    while (inputIndex < inputCount && localIndex < localCount)
    {
      TObj localItem = localSorted[localIndex];
      TObj inputItem = inputSorted[inputIndex];

      if (localItem < inputItem)
      {
        result.push_back(localItem);
        localIndex++;
      }
      else
      {
        inputIndex++;
      }
    }

    Queryable<TObj, std::vector> output(result);
    return output;
  }

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

  template<typename TJoinObj, typename TJoinOn, typename TOut>
  Queryable<TOut, std::vector> Join(
    TIterable<TJoinObj> collection,
    std::function<TJoinOn(TObj)> getLocalJoinOn,
    std::function<TJoinOn(TJoinObj)> getInputJoinOn,
    std::function<TOut(TObj, TJoinObj)> createFrom)
  {
    static_assert(is_equatable<TJoinOn>::value, "Type must be equatable");
    static_assert(is_less_comparable<TJoinOn>::value, "Type must be 'less than' comparable");

    std::vector<TOut> result;

    Queryable<TJoinObj, TIterable> inputCollection(collection);
    int inputSize = inputCollection.Count();
    int localSize = this->Count();

    if (localSize == 0 || inputSize == 0)
    {
      return result;
    }

    std::vector<TObj> localSorted = this->OrderBy(getLocalJoinOn).ToVector();
    std::vector<TJoinObj> inputSorted = inputCollection.OrderBy(getInputJoinOn).ToVector();

    int inputIndex = 0;

    for (int i = 0; i < localSize; i++) // TObj localItem : localSorted)
    {
      TObj localItem = localSorted[i];
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
          TJoinObj sameValueItem = inputSorted[sameValueIndex];
          while (getInputJoinOn(sameValueItem) == inputValue)
          {
            result.push_back(createFrom(localItem, sameValueItem));

            if (sameValueIndex == inputSize - 1)
            {
              break;
            }

            sameValueItem = inputSorted[++sameValueIndex];
          }
        }

        if (inputValue < localValue)
        {
          inputIndex++;
        }

      } while (inputValue < localValue && inputIndex < inputSize);
    }

    Queryable<TOut, std::vector> output(result);
    return output;
  }
};

#endif
