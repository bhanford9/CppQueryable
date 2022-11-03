#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLEDEQUEDATA_H

#include <deque>

#include "TakeWhileQueryableData.hpp"

template <typename TObj, typename TAllocator = std::allocator<TObj>>
class TakeWhileQueryableDequeData final : public TakeWhileQueryableData<
        TObj, std::deque, TObj, TAllocator>
{
public:
    TakeWhileQueryableDequeData(const TakeWhileQueryableDequeData & other)
        : TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>(other)
    {
    }

    TakeWhileQueryableDequeData(TakeWhileQueryableDequeData && other) noexcept
        : TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>(std::move(other))
    {
    }

    TakeWhileQueryableDequeData(
        std::shared_ptr<IQueryableData<TObj>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "TakeWhileQueryable Deque Data Constructor 0" << std::endl;
    }

    TakeWhileQueryableDequeData(
        std::shared_ptr<QueryableData<TObj, std::deque, TObj, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
        // std::cout << "TakeWhileQueryable Deque Data Constructor 1" << std::endl;
    }

    TakeWhileQueryableDequeData(
        const std::shared_ptr<QueryableData<TObj, std::deque, TObj, TAllocator>> & data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>(data, std::move(condition))
    {
        // std::cout << "TakeWhileQueryable Deque Data Constructor 3" << std::endl;
    }
    
    TakeWhileQueryableDequeData & operator=(const TakeWhileQueryableDequeData & other)
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>::operator =(other);
        return *this;
    }

    TakeWhileQueryableDequeData & operator=(TakeWhileQueryableDequeData && other) noexcept
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TObj, std::deque, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~TakeWhileQueryableDequeData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<TakeWhileQueryableDequeData<TObj, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->push_back(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner
        std::deque<TObj, TAllocator> data(this->items->get_allocator());

        for (const TObj & value : *this)
        {
            data.push_back(value);
        }

        return std::make_shared<QueryableDequeData<TObj, TAllocator>>(std::move(data));
    }
};

#endif
