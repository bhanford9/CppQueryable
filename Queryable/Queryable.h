#ifndef FIRST_QUERYABLE_QUERYABLE_H
#define FIRST_QUERYABLE_QUERYABLE_H

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

#include "TypeConstraintUtil.h"

template<typename TObj, template<typename...> typename TIterable>
class Queryable
{
  static_assert(can_iterate<TIterable<TObj>>::value, "Class must be able to be iterated over");

protected:
  TIterable<TObj> items;

public:
  Queryable(TIterable<TObj> items)
  {
    this->items = items;
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

  TObj At(int index)
  {
    int i = 0;

    for (TObj item : this->items)
    {
      if (i++ == index)
      {
        return item;
      }
    }

    throw std::exception("Invalid Index Provided");
  }

  int Count()
  {
    int count = 0;

    for (TObj item : this->items)
    {
      count++;
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
    for (TObj item : this->items)
    {
      if (clause(item))
      {
        return &item;
      }
    }

    return NULL;
  }

  TObj * First()
  {
    if (this->Count() > 0)
    {
      return this->items[0];
    }

    return NULL;
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

  void Concat(TIterable<TObj> collection, std::function<void(TIterable<TObj>*, TObj)> appender)
  {
    for (TObj obj : collection)
    {
      appender(&this->items, obj);
    }
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
