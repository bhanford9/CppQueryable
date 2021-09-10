#ifndef CPPQUERYABLE_QUERYABLE_LINKEDQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_LINKEDQUERYABLEDATA_H

#include <algorithm>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <vector>

#include "../TypeConstraintUtil.h"
#include "../Utilities/Condition.h"
#include "IQueryableData.h"
#include "QueryableData.h"

template<typename TOriginal, typename TCurrent, template<typename, typename ...> typename TIterable, typename ...TArgs>
class LinkedQueryableData : public QueryableData<TCurrent, TIterable, TArgs...>
{
  static_assert(can_iterate<TIterable<TCurrent, TArgs...>>::value, "Class must be able to be iterated over");
protected:
  typedef typename QueryableData<TCurrent, TIterable, TArgs...>::TForwardIterator TForwardIterator;
  typedef typename QueryableData<TCurrent, TIterable, TArgs...>::TReverseIterator TReverseIterator;

  // TODO --> consider trying to make this a unique_ptr instead
  std::shared_ptr<IQueryableData<TOriginal>> original;
  Iterator<TOriginal> originalBeginning;
  Iterator<TOriginal> originalEnding;
  Iterator<TOriginal> originalRBeginning;
  Iterator<TOriginal> originalREnding;

  void LinkedIncrementPastCondition(Iterator<TOriginal> & iterator, uint64_t & index)
  {
    if (this->CanSkip())
    {
      TCurrent current = this->ToCurrent(*iterator);
      while (index < this->size && this->DoSkip(current))
      {
        ++iterator;
        current = this->ToCurrent(*iterator);
        index = iterator.Index;
        this->beginning.Index = index;
      }
    }
  }

  void LinkedInitForwardBegin()
  {
    this->beginning.Increment = [&](uint64_t & index)
    {
      if (index < this->size)
      {
        // TOOD --> create this variable with passed in allocator
        TOriginal value;

        do
        {
          ++this->originalBeginning;
          index = this->originalBeginning.Index;

          if (index < this->size)
          {
            value = *this->originalBeginning;
          }
        }
        while (index < this->size && this->DoSkip(value));
      }
    };
    this->beginning.Decrement = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        --this->originalBeginning;
        index = this->originalBeginning.Index;

        if (index >= 0)
        {
          value = *this->originalBeginning;
        }
      }
      while (index >= 0 && this->DoSkip(value));
    };

    this->beginning.Dereference = [&]() -> TCurrent& { this->value = this->ToCurrent(*this->originalBeginning); return this->value; };
    this->beginning.ConstDereference = [&]() -> const TCurrent& { this->value = this->ToCurrent(*this->originalBeginning); return this->value; };
  }

  void LinkedInitForwardEnd()
  {
    this->ending.Increment = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        ++this->originalEnding;
        index = this->originalEnding.Index;

        if (index < this->size)
        {
          value = *this->originalEnding;
        }
      }
      while (index < this->size && this->DoSkip(value));
    };
    this->ending.Decrement = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        --this->originalEnding;
        index = this->originalEnding.Index;

        if (index >= 0)
        {
          value = *this->originalEnding;
        }
      }
      while (index >= 0 && this->DoSkip(value));
    };

    this->ending.Dereference = [&]() -> TCurrent& { this->value = this->ToCurrent(*this->originalEnding); return this->value; };
    this->ending.ConstDereference = [&]() -> const TCurrent& { this->value = this->ToCurrent(*this->originalEnding); return this->value; };
  }

  void LinkedInitReverseBegin()
  {
    this->rbeginning.Increment = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        ++this->originalRBeginning;
        index = this->originalRBeginning.Index;

        if (index < this->size)
        {
          value = *this->originalRBeginning;
        }
      }
      while (index <= this->size && this->DoSkip(value));
    };
    this->rbeginning.Decrement = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        --this->originalRBeginning;
        index = this->originalRBeginning.Index;

        if (index >= 0)
        {
          value = *this->originalRBeginning;
        }
      }
      while (index >= 0 && this->DoSkip(value));
    };

    this->rbeginning.Dereference = [&]() -> TCurrent& { this->value = this->ToCurrent(*this->originalRBeginning); return this->value; };
    this->rbeginning.ConstDereference = [&]() -> const TCurrent& { this->value = this->ToCurrent(*this->originalRBeginning); return this->value; };
  }

  void LinkedInitReverseEnd()
  {
    this->rending.Increment = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        ++this->originalREnding;
        index = this->originalREnding.Index;

        if (index < this->size)
        {
          value = *this->originalREnding;
        }
      }
      while (index <= this->size && this->DoSkip(value));
    };
    this->rending.Decrement = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        --this->originalREnding;
        index = this->originalREnding.Index;

        if (index >= 0)
        {
          value = *this->originalREnding;
        }
      }
      while (index >= 0 && this->DoSkip(value));
    };

    this->rending.Dereference = [&]() -> TCurrent& { this->value = this->ToCurrent(*this->originalREnding); return this->value; };
    this->rending.ConstDereference = [&]() -> const TCurrent& { this->value = this->ToCurrent(*this->originalREnding); return this->value; };
  }

public:

  LinkedQueryableData(std::shared_ptr<IQueryableData<TOriginal>> data)
    : QueryableData<TCurrent, TIterable, TArgs...>()
  {
    this->original = std::move(data);
    this->size = this->original->StorageSize();
    this->LinkedInitForwardBegin();
    this->LinkedInitForwardEnd();
    this->LinkedInitReverseBegin();
    this->LinkedInitReverseEnd();
  }
  virtual ~LinkedQueryableData() { }

  virtual TCurrent ToCurrent(TOriginal original) = 0;
  virtual bool DoSkip(TCurrent value) = 0;
  virtual bool CanSkip() = 0;

  void Clear() override
  {
    this->original->Clear();
    this->size = 0;
  }

  std::vector<TCurrent> ToVector() override
  {
    std::vector<TCurrent> objs;
    std::vector<TOriginal> originals = this->original->ToVector();

    for (TOriginal obj : originals)
    {
      TCurrent current = this->ToCurrent(obj);
      if (!this->DoSkip(current))
      {
        objs.push_back(current);
      }
    }

    return objs;
  }

  Iterator<TCurrent> begin() override
  {
    this->originalBeginning = this->original->begin();
    this->beginIterator = this->items.begin();
    this->beginning.Index = this->originalBeginning.Index;
    this->LinkedIncrementPastCondition(this->originalBeginning, this->originalBeginning.Index);

    return this->beginning;
  }

  Iterator<TCurrent> end() override
  {
    this->originalEnding = this->original->end();
    this->endIterator = this->items.end();
    this->ending.Index = this->size;
    return this->ending;
  }

  Iterator<TCurrent> rbegin() override
  {
    this->originalRBeginning = this->original->rbegin();
    this->rbeginIterator = this->items.rbegin();
    this->rbeginning.Index = this->originalRBeginning.Index;
    this->LinkedIncrementPastCondition(this->originalRBeginning, this->originalRBeginning.Index);

    return this->rbeginning;
  }

  Iterator<TCurrent> rend() override
  {
    this->originalREnding = this->original->rend();
    this->rendIterator = this->items.rend();
    this->rending.Index = this->size;
    return this->rending;
  }
};

#endif
