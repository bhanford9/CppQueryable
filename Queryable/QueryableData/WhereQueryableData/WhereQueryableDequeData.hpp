#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEDEQUEDATA_H

#include <deque>

#include "WhereQueryableData.hpp"
#include "../QueryableDequeData.hpp"

template <typename TObj, typename TAllocator = std::allocator<TObj>>
class WhereQueryableDequeData final : public WhereQueryableData<TObj, std::deque, TObj, TAllocator>
{
public:
    WhereQueryableDequeData(const WhereQueryableDequeData & other)
        : WhereQueryableData<TObj, std::deque, TObj, TAllocator>(other)
    {
    }

    WhereQueryableDequeData(WhereQueryableDequeData && other) noexcept
        : WhereQueryableData<TObj, std::deque, TObj, TAllocator>(std::move(other))
    {
    }

    WhereQueryableDequeData(
        std::shared_ptr<IQueryableData<TObj>> data,
        std::function<bool(TObj)> condition)
        : WhereQueryableData<TObj, std::deque, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    WhereQueryableDequeData(
        std::shared_ptr<QueryableData<TObj, std::deque, TObj, TAllocator>> && data,
        std::function<bool(TObj)> condition)
        : WhereQueryableData<TObj, std::deque, TObj, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    WhereQueryableDequeData & operator=(const WhereQueryableDequeData & other)
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::deque, TObj, TAllocator>::operator =(other);
        return *this;
    }

    WhereQueryableDequeData & operator=(WhereQueryableDequeData && other) noexcept
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::deque, TObj, TAllocator>::operator =(std::move(other));
        return *this;
    }

    virtual ~WhereQueryableDequeData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<WhereQueryableDequeData<TObj, TAllocator>>(*this);
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
