#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLEMULTISETDATA_H

#include <set>

#include "SkipWhileQueryableData.hpp"

template <typename TObj, typename TCompare = std::less<TObj>, typename TAllocator = std::allocator<
              TObj>>
class SkipWhileQueryableMultiSetData final : public SkipWhileQueryableData<
        TObj, std::multiset, TObj, TCompare, TAllocator>
{
public:
    SkipWhileQueryableMultiSetData(const SkipWhileQueryableMultiSetData & other)
        : SkipWhileQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(other)
    {
    }

    SkipWhileQueryableMultiSetData(SkipWhileQueryableMultiSetData && other) noexcept
        : SkipWhileQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(std::move(other))
    {
    }

    SkipWhileQueryableMultiSetData(
        std::shared_ptr<IQueryableData<TObj>> data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    SkipWhileQueryableMultiSetData(
        std::shared_ptr<QueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    SkipWhileQueryableMultiSetData & operator=(const SkipWhileQueryableMultiSetData & other)
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>::operator =(other);
        return *this;
    }

    SkipWhileQueryableMultiSetData & operator=(SkipWhileQueryableMultiSetData && other) noexcept
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>::operator =(
            std::move(other));
        return *this;
    }

    virtual ~SkipWhileQueryableMultiSetData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<SkipWhileQueryableMultiSetData<TObj, TCompare, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->insert(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner

        std::multiset<TObj, TCompare, TAllocator> data(
            this->items->value_comp(),
            this->items->get_allocator());

        for (const TObj & value : *this)
        {
            data.insert(value);
        }

        return std::make_shared<QueryableMultiSetData<TObj, TCompare, TAllocator>>(std::move(data));
    }
};

#endif
