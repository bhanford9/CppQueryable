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
      while (index < this->size && this->DoSkip(*iterator))
      {
        ++iterator;
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

    // Add and Subtract are needed for sorting random access iterators
    // (i.e. Vector, Deque, Array)

    // Two iterators can be subtracted to get a scalar value and then that
    // scalar value can be added/subtracted to the iterator to access a value
    // at a new position in constant time.

    // When subtracting two iterators, you always get the difference of the
    // original underlying container, so for WhereQueryableData's you still
    // have to iterate over and sort all of the underlying elements which is
    // highly inefficient compared to what would be expected

    // Documentation needs to be clear about this so that it is understood that
    // if a Queryable that had Where or Select called on it is intended to be
    // used more than once, then one of the copy methods should be used to ensure
    // extra (unecessary) iterations/operations are not taking place
    this->beginning.Add = [&](int addend, uint64_t & index)
    {
      while (addend > 0)
      {
        ++this->originalBeginning;
        addend -= (this->originalBeginning.Index - index);
        index = this->originalBeginning.Index;
      }
    };
    this->beginning.Subtract = [&](int subtrahend, uint64_t & index)
    {
      while (subtrahend > 0)
      {
        --this->originalBeginning;
        subtrahend -= (index - this->originalBeginning.Index);
        index = this->originalBeginning.Index;
      }
    };
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

    // Add and Subtract are needed for sorting random access iterators
    // (i.e. Vector, Deque, Array)

    // Two iterators can be subtracted to get a scalar value and then that
    // scalar value can be added/subtracted to the iterator to access a value
    // at a new position in constant time.

    // When subtracting two iterators, you always get the difference of the
    // original underlying container, so for WhereQueryableData's you still
    // have to iterate over and sort all of the underlying elements which is
    // highly inefficient compared to what would be expected

    // Documentation needs to be clear about this so that it is understood that
    // if a Queryable that had Where or Select called on it is intended to be
    // used more than once, then one of the copy methods should be used to ensure
    // extra (unecessary) iterations/operations are not taking place
    this->ending.Add = [&](int addend, uint64_t & index)
    {
      while (addend > 0)
      {
        ++this->originalEnding;
        addend -= (this->originalEnding.Index - index);
        index = this->originalEnding.Index;
      }
    };
    this->ending.Subtract = [&](int subtrahend, uint64_t & index)
    {
      while (subtrahend > 0)
      {
        --this->originalEnding;
        subtrahend -= (index - this->originalEnding.Index);
        index = this->originalEnding.Index;
      }
    };
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

    // Add and Subtract are needed for sorting random access iterators
    // (i.e. Vector, Deque, Array)

    // Two iterators can be subtracted to get a scalar value and then that
    // scalar value can be added/subtracted to the iterator to access a value
    // at a new position in constant time.

    // When subtracting two iterators, you always get the difference of the
    // original underlying container, so for WhereQueryableData's you still
    // have to iterate over and sort all of the underlying elements which is
    // highly inefficient compared to what would be expected

    // Documentation needs to be clear about this so that it is understood that
    // if a Queryable that had Where or Select called on it is intended to be
    // used more than once, then one of the copy methods should be used to ensure
    // extra (unecessary) iterations/operations are not taking place
    this->rbeginning.Add = [&](int addend, uint64_t & index)
    {
      while (addend > 0)
      {
        ++this->originalRBeginning;
        addend -= (this->originalRBeginning.Index - index);
        index = this->originalRBeginning.Index;
      }
    };
    this->rbeginning.Subtract = [&](int subtrahend, uint64_t & index)
    {
      while (subtrahend > 0)
      {
        --this->originalRBeginning;
        subtrahend -= (index - this->originalRBeginning.Index);
        index = this->originalRBeginning.Index;
      }
    };
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

    // Add and Subtract are needed for sorting random access iterators
    // (i.e. Vector, Deque, Array)

    // Two iterators can be subtracted to get a scalar value and then that
    // scalar value can be added/subtracted to the iterator to access a value
    // at a new position in constant time.

    // When subtracting two iterators, you always get the difference of the
    // original underlying container, so for WhereQueryableData's you still
    // have to iterate over and sort all of the underlying elements which is
    // highly inefficient compared to what would be expected

    // Documentation needs to be clear about this so that it is understood that
    // if a Queryable that had Where or Select called on it is intended to be
    // used more than once, then one of the copy methods should be used to ensure
    // extra (unecessary) iterations/operations are not taking place
    this->rending.Add = [&](int addend, uint64_t & index)
    {
      while (addend > 0)
      {
        ++this->originalREnding;
        addend -= (this->originalREnding.Index - index);
        index = this->originalREnding.Index;
      }
    };
    this->rending.Subtract = [&](int subtrahend, uint64_t & index)
    {
      while (subtrahend > 0)
      {
        --this->originalREnding;
        subtrahend -= (index - this->originalREnding.Index);
        index = this->originalREnding.Index;
      }
    };
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
  LinkedQueryableData(const LinkedQueryableData<TOriginal, TCurrent, TIterable, TArgs...> & data)
    : QueryableData<TCurrent, TIterable, TArgs...>(data)
  {
  }
  virtual ~LinkedQueryableData() { }

  virtual TCurrent ToCurrent(TOriginal original) = 0;
  virtual bool CanSkip() = 0;

  // if we ever want to evaluate this for QueryableData types that require
  // different TOriginal and TCurrent types, will need to change signature to take
  // a TCurrent instead of a TOriginal. Its faster in the iterator incrementing
  // if we do not have to convert from TOriginal to TCurrent though
  virtual bool DoSkip(TOriginal value) = 0;

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
      if (!this->DoSkip(obj))
      {
        objs.push_back(this->ToCurrent(obj));
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
