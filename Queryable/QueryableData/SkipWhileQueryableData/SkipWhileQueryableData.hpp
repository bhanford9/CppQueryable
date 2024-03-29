#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEDATA_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>

#include "../IQueryableData.hpp"
#include "../QueryableData.hpp"
#include "../QueryableVectorData.hpp"
#include "../../Utilities/IWhileCondition.hpp"

template <typename TObj, template<typename, typename ...> class TIterable, typename TIterating,
          typename ...TArgs>
class SkipWhileQueryableData : public QueryableData<TObj, TIterable, TIterating, TArgs...>
{
protected:
    std::shared_ptr<IWhileCondition<TIterating>> condition;
    std::shared_ptr<QueryableData<TObj, TIterable, TIterating, TArgs...>> original;
    bool sizeIsCalculated;
    bool finishedSkipping;

    void IncrementPastSkips(IteratorType type, size_t & iterated, bool & isForcingToEnd)
    {
        while (this->original->CanIncrement(type) && this->DoSkip(this->original->Get(type)))
        {
            size_t internalIterated = 1;
            this->original->Next(type, internalIterated, isForcingToEnd);
            iterated += internalIterated;
        }
    }

public:
    SkipWhileQueryableData(const SkipWhileQueryableData & other)
        : QueryableData<TObj, TIterable, TIterating, TArgs...>(other), condition(other.condition),
          original(other.original), sizeIsCalculated(other.sizeIsCalculated),
          finishedSkipping(other.finishedSkipping)
    {
    }

    SkipWhileQueryableData(SkipWhileQueryableData && other) noexcept
        : QueryableData<TObj, TIterable, TIterating, TArgs...>(std::move(other)),
          condition(std::move(other.condition)), original(std::move(other.original)),
          sizeIsCalculated(other.sizeIsCalculated), finishedSkipping(other.finishedSkipping)
    {
    }

    SkipWhileQueryableData(
        std::shared_ptr<QueryableData<TObj, TIterable, TIterating, TArgs...>> && data,
        std::shared_ptr<IWhileCondition<TIterating>> && condition)
        : condition(std::move(condition)), original(std::move(data)), sizeIsCalculated(false),
          finishedSkipping(false)
    {
        // std::cout << "SkipWhileQueryableData move constructor" << std::endl;
    }

    SkipWhileQueryableData(
        const std::shared_ptr<QueryableData<TObj, TIterable, TIterating, TArgs...>> & data,
        std::shared_ptr<IWhileCondition<TIterating>> && condition)
        : condition(std::move(condition)), original(data), sizeIsCalculated(false),
          finishedSkipping(false)
    {
        // std::cout << "SkipWhileQueryableData copy constructor 1" << std::endl;
    }

    SkipWhileQueryableData & operator=(const SkipWhileQueryableData & other)
    {
        if (this == &other) return *this;
        QueryableData<TObj, TIterable, TIterating, TArgs...>::operator =(other);
        condition = other.condition;
        original = other.original;
        sizeIsCalculated = other.sizeIsCalculated;
        finishedSkipping = other.finishedSkipping;
        return *this;
    }

    SkipWhileQueryableData & operator=(SkipWhileQueryableData && other) noexcept
    {
        if (this == &other) return *this;
        QueryableData<TObj, TIterable, TIterating, TArgs...>::operator =(std::move(other));
        condition = std::move(other.condition);
        original = std::move(other.original);
        sizeIsCalculated = other.sizeIsCalculated;
        finishedSkipping = other.finishedSkipping;
        return *this;
    }

    virtual ~SkipWhileQueryableData() override = default;

    // TODO --> this is a pretty bad method to call for this class. finding a way
    //    to track this instead of iterating over the container would be good.
    virtual size_t Count() override
    {
        // TODO --> size is calculated needs to act like the state of an IEnumerable
        //   where the size can simply be returned if it has already been enumerated

        // if (this->sizeIsCalculated)
        // {
        //   std::cout << "size is already calculated" << std::endl;
        //   return this->size;
        // }

        size_t count = 0;

        this->finishedSkipping = false;
        this->condition->Reset();

        // not sure I like needing to get the realized queryable data
        std::shared_ptr<IQueryableData<TIterating>> realized = this->original->
            GetRealizedQueryableData();

        for (const TIterating & item : *realized)
        {
            if (!this->DoSkip(item))
            {
                count++;
            }
        }

        this->size = count;
        this->sizeIsCalculated = true;
        this->condition->Reset();
        this->finishedSkipping = false;

        return count;
    }

    virtual void Add(TIterating item) override
    {
        // pretty sure we don't want this method to exist
        // if (this->condition(item))
        // {
        //   this->InternalAdd(item);
        //   this->size++;
        // }
    }

    // virtual TIterable<TObj, TArgs...> & GetContainer() override
    // {
    //   return this->original->GetContainer();
    // }

    virtual void InternalAdd(TIterating item) = 0;

    virtual TIterating & Get(IteratorType type) override
    {
        return this->original->Get(type);
    }

    virtual bool CanIncrement(IteratorType type) override
    {
        return this->original->CanIncrement(type);
    }

    virtual bool CanDecrement(IteratorType type) override
    {
        return this->original->CanDecrement(type);
    }

    virtual const TIterating & ConstGet(IteratorType type) override
    {
        return this->original->ConstGet(type);
    }

    virtual IQueryableData<TIterating> & Next(
        IteratorType type,
        size_t & iterated,
        bool & isForcingToEnd) override
    {
        // std::cout << "Skip While Queryable Next" << std::endl;
        this->original->Next(type, iterated, isForcingToEnd);

        return *this;
    }

    virtual IQueryableData<TIterating> & Prev(IteratorType type, size_t & iterated) override
    {
        // std::cout << "While Queryable Prev" << std::endl;

        // TODO --> Prev may not have very applicable use here
        this->original->Prev(type, iterated);

        return *this;
    }

    virtual IQueryableData<TIterating> & Add(int addend, IteratorType type) override
    {
        // this is the worse possible way to implement this and should be overriden for random access iterators
        std::cout << "bad" << std::endl;
        size_t dummy = 0;
        while (this->original->CanIncrement(type) && addend-- > 0)
        {
            bool isForcingToEnd = false;
            this->Next(type, dummy, isForcingToEnd);
        }

        return *this;
    }

    virtual IQueryableData<TIterating> & Subtract(int subtrahend, IteratorType type) override
    {
        // this is the worse possible way to implement this and should be overriden for random access iterators
        std::cout << "bad" << std::endl;
        size_t dummy = 0;
        while (this->original->CanDecrement(type) && subtrahend-- > 0)
        {
            this->Prev(type, dummy);
        }

        return *this;
    }

    // remove the possibility to iterate if the first element does not pass condition
    virtual QueryableIterator<TIterating> begin() override
    {
        // std::cout << "SkipWhileQueryableData::begin" << std::endl;
        this->condition->Reset();
        this->finishedSkipping = false;
        QueryableIterator<TIterating> child = this->original->begin();

        // while (this->DoSkip(*child)) ++child;
        size_t startIndex = child.index;
        bool isForcingToEnd = false;
        this->IncrementPastSkips(IteratorType::BeginForward, startIndex, isForcingToEnd);

        QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::BeginForward);

        return retVal;
    }

    // End only serves as a check of the last element while iterating begin.
    // This will never be used to increment/decrement
    virtual QueryableIterator<TIterating> end() override
    {
        // std::cout << "SkipWhileQueryableData::end" << std::endl;
        QueryableIterator<TIterating> child = this->original->end();

        size_t startIndex = child.index;
        QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::EndForward);

        return retVal;
    }

    // remove the possibility to iterate if the first element does not pass condition
    virtual QueryableIterator<TIterating> rbegin() override
    {
        this->condition->Reset();
        QueryableIterator<TIterating> child = this->original->rbegin();

        size_t startIndex = child.index;
        QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::BeginReverse);

        return retVal;
    }

    // Rend only serves as a check of the last element while iterating begin.
    // This will never be used to increment/decrement
    virtual QueryableIterator<TIterating> rend() override
    {
        QueryableIterator<TIterating> child = this->original->end();

        size_t startIndex = child.index;
        QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::EndReverse);

        return retVal;
    }

    bool DoSkip(const TIterating & item)
    {
        if (!this->finishedSkipping)
        {
            const bool passes = this->condition->Passes(item);
            this->finishedSkipping = !passes;
        }

        return !this->finishedSkipping;
    }
};

#endif
