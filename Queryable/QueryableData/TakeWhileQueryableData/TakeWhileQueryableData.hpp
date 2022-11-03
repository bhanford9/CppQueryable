#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDATA_H

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
class TakeWhileQueryableData : public QueryableData<TObj, TIterable, TIterating, TArgs...>
{
protected:
    std::shared_ptr<IWhileCondition<TIterating>> condition;
    std::shared_ptr<QueryableData<TObj, TIterable, TIterating, TArgs...>> original;
    bool sizeIsCalculated;

public:
    TakeWhileQueryableData(const TakeWhileQueryableData & other)
        : QueryableData<TObj, TIterable, TIterating, TArgs...>(other), condition(other.condition),
          original(other.original), sizeIsCalculated(other.sizeIsCalculated)
    {
    }

    TakeWhileQueryableData(TakeWhileQueryableData && other) noexcept
        : QueryableData<TObj, TIterable, TIterating, TArgs...>(std::move(other)),
          condition(std::move(other.condition)), original(std::move(other.original)),
          sizeIsCalculated(other.sizeIsCalculated)
    {
    }

    TakeWhileQueryableData(
        std::shared_ptr<QueryableData<TObj, TIterable, TIterating, TArgs...>> && data,
        std::shared_ptr<IWhileCondition<TIterating>> && condition)
        : condition(std::move(condition)), original(std::move(data)), sizeIsCalculated(false)
    {
        // std::cout << "TakeWhileQueryableData move constructor" << std::endl;
    }

    TakeWhileQueryableData(
        const std::shared_ptr<QueryableData<TObj, TIterable, TIterating, TArgs...>> & data,
        std::shared_ptr<IWhileCondition<TIterating>> && condition)
        : original(data), condition(std::move(condition)), sizeIsCalculated(false)
    {
        // std::cout << "TakeWhileQueryableData copy constructor" << std::endl;
    }

    TakeWhileQueryableData & operator=(const TakeWhileQueryableData & other)
    {
        if (this == &other) return *this;
        QueryableData<TObj, TIterable, TIterating, TArgs...>::operator =(other);
        condition = other.condition;
        original = other.original;
        sizeIsCalculated = other.sizeIsCalculated;
        return *this;
    }

    TakeWhileQueryableData & operator=(TakeWhileQueryableData && other) noexcept
    {
        if (this == &other) return *this;
        QueryableData<TObj, TIterable, TIterating, TArgs...>::operator =(std::move(other));
        condition = std::move(other.condition);
        original = std::move(other.original);
        sizeIsCalculated = other.sizeIsCalculated;
        return *this;
    }

    virtual ~TakeWhileQueryableData() override = default;

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

        this->condition->Reset();

        // not sure I like needing to get the realized queryable data
        std::shared_ptr<IQueryableData<TIterating>> realized = this->original->
            GetRealizedQueryableData();

        for (const TIterating & item : *realized)
        {
            if (this->condition->Passes(item))
            {
                count++;
            }
            else
            {
                break;
            }
        }

        this->size = count;
        this->sizeIsCalculated = true;

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
        // std::cout << "While Queryable Next" << std::endl;

        if (!this->condition->Passes(this->original->Get(type)))
        {
            this->original->ForceEnd(type);
        }

        this->original->Next(type, iterated, isForcingToEnd);

        return *this;
    }

    virtual IQueryableData<TIterating> & Prev(IteratorType type, size_t & iterated) override
    {
        // std::cout << "While Queryable Prev" << std::endl;

        if (!this->condition->Passes(this->original->Get(type)))
        {
            this->original->ForceBegin(type);
        }

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
        // std::cout << "TakeWhileQueryableData::begin" << std::endl;
        this->condition->Reset();
        QueryableIterator<TIterating> child = this->original->begin();

        if (!this->condition->Passes(*child))
        {
            child = this->original->end();
        }

        size_t startIndex = child.index;
        QueryableIterator<TIterating> retVal(this->Clone(), startIndex, IteratorType::BeginForward);

        return retVal;
    }

    // End only serves as a check of the last element while iterating begin.
    // This will never be used to increment/decrement
    virtual QueryableIterator<TIterating> end() override
    {
        // std::cout << "TakeWhileQueryableData::end" << std::endl;
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

        if (!this->condition->Passes(*child))
        {
            child = this->original->rend();
        }

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
};

#endif
