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

  IQueryableData<TOriginal> * original;
  Iterator<TOriginal> originalBeginning;
  Iterator<TOriginal> originalEnding;

  void LinkedIncrementPastCondition(Iterator<TOriginal> & iterator, uint64_t & index)
  {
    if (this->CanSkip())
    {
      TCurrent current = this->ToCurrent(*iterator);
      while (index < this->size && this->DoSkip(current))
      {
        iterator++;
        current = this->ToCurrent(*iterator);
        index = iterator.GetIndex();
        this->beginning.SetIndex(index);
      }
    }
  }

  void LinkedInitForwardBegin()
  {
    // this->beginning.Get = [&]() { return &this->beginIterator; };

    this->beginning.Increment = [&](uint64_t & index)
    {
      if (index < this->size)
      {
        // TOOD --> create this variable with passed in allocator
        TOriginal value;

        do
        {
          this->originalBeginning++;
          index = this->originalBeginning.GetIndex();
          this->beginning.SetIndex(index);
          value = *this->originalBeginning;
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
        this->originalBeginning.Decrement(index);
        value = *this->originalBeginning;
      }
      while (index >= 0 && this->DoSkip(value));
    };

    this->beginning.Dereference = [&]() -> TCurrent& { this->value = this->ToCurrent(*this->originalBeginning); return this->value; };
    this->beginning.ConstDereference = [&]() -> const TCurrent& { this->value = this->ToCurrent(*this->originalBeginning); return this->value; };
    // this->beginning.Assign = [&](const Iterator<TCurrent> & value) { this->beginIterator = TForwardIterator(*static_cast<TForwardIterator*>(value.Get())); };
  }

  void LinkedInitForwardEnd()
  {
    // this->ending.Get = [&]() { return &this->endIterator; };

    this->ending.Increment = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        this->originalEnding.Increment(index);
        value = *this->originalEnding;
      }
      while (index < this->size && this->DoSkip(value));
    };
    this->ending.Decrement = [&](uint64_t & index)
    {
      // TOOD --> create this variable with passed in allocator
      TOriginal value;

      do
      {
        this->originalEnding.Decrement(index);
        value = *this->originalEnding;
      }
      while (index >= 0 && this->DoSkip(value));
    };

    this->ending.Dereference = [&]() -> TCurrent& { this->value = this->ToCurrent(*this->originalEnding); return this->value; };
    this->ending.ConstDereference = [&]() -> const TCurrent& { this->value = this->ToCurrent(*this->originalBeginning); return this->value; };
    // this->ending.Assign = [&](const Iterator<TObj> & value) { this->endIterator = TForwardIterator(*static_cast<TForwardIterator*>(value.Get())); };
  }
  //
  // void InitReverseBegin()
  // {
  //   this->rbeginning.Get = [&]() { return &this->rbeginIterator; };
  //
  //   this->rbeginning.Increment = [&](uint64_t & index)
  //   {
  //     ++this->rbeginIterator;
  //     if (this->condition)
  //       this->RIncrementPastCondition(this->rbeginIterator, index);
  //   };
  //   this->rbeginning.Decrement = [&](uint64_t & index)
  //   {
  //     --this->rbeginIterator;
  //     if (this->condition)
  //       this->RDecrementPastCondition(this->rbeginIterator, index);
  //   };
  //
  //   this->rbeginning.Dereference = [&]() -> TObj& { this->value = *this->rbeginIterator; return this->value; };
  //   this->rbeginning.ConstDereference = [&]() -> const TObj& { return *this->rbeginIterator; };
  //   this->rbeginning.Assign = [&](const Iterator<TObj> & value) { this->rbeginIterator = TReverseIterator(*static_cast<TReverseIterator*>(value.Get())); };
  // }
  //
  // void InitReverseEnd()
  // {
  //   this->rending.Get = [&]() { return &this->rendIterator; };
  //
  //   this->rending.Increment = [&](uint64_t & index)
  //   {
  //     ++this->rendIterator;
  //     if (this->condition)
  //       this->RIncrementPastCondition(this->rendIterator, index);
  //   };
  //   this->rending.Decrement = [&](uint64_t & index)
  //   {
  //     --this->rendIterator;
  //     if (this->condition)
  //       this->RDecrementPastCondition(this->rendIterator, index);
  //   };
  //
  //   this->rending.Dereference = [&]() -> TObj& { this->value = *this->rendIterator; return this->value; };
  //   this->rending.ConstDereference = [&]() -> const TObj& { return *this->rendIterator; };
  //   this->rending.Assign = [&](const Iterator<TObj> & value) { this->rendIterator = TReverseIterator(*static_cast<TReverseIterator*>(value.Get())); };
  // }

public:

  LinkedQueryableData(IQueryableData<TOriginal> * data)
    : QueryableData<TCurrent, TIterable, TArgs...>()
  {
    this->original = data;
    this->size = this->original->StorageSize();
    this->LinkedInitForwardBegin();
    this->LinkedInitForwardEnd();
    // this->InitReverseBegin();
    // this->InitReverseEnd();
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
    this->beginning.SetIndex(this->originalBeginning.GetIndex());
    this->LinkedIncrementPastCondition(this->originalBeginning, this->originalBeginning.GetIndex());

    return this->beginning;
  }

  Iterator<TCurrent> end() override
  {
    this->originalEnding = this->original->end();
    this->endIterator = this->items.end();
    this->ending.SetIndex(this->size);
    return this->ending;
  }

  Iterator<TCurrent> rbegin() override
  {
    // this->rbeginIterator = this->items.rbegin();
    // this->RIncrementPastCondition(this->rbeginIterator, this->rbeginning.GetIndex());

    return this->rbeginning;
  }

  Iterator<TCurrent> rend() override
  {
    // this->rendIterator = this->items.rend();
    // this->rending.SetIndex(this->size);
    return this->rending;
  }
};

#endif
