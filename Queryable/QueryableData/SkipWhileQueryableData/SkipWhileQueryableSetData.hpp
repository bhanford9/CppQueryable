#ifndef CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_SKIPWHILEQUERYABLEDATA_SKIPWHILEQUERYABLESETDATA_H

#include <set>

#include "SkipWhileQueryableData.hpp"

template <typename TObj, typename TCompare = std::less<TObj>, typename TAllocator = std::allocator<
              TObj>>
class SkipWhileQueryableSetData final : public SkipWhileQueryableData<
        TObj, std::set, TObj, TCompare, TAllocator>
{
public:
    SkipWhileQueryableSetData(const SkipWhileQueryableSetData & other)
        : SkipWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(other)
    {
    }

    SkipWhileQueryableSetData(SkipWhileQueryableSetData && other) noexcept
        : SkipWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(std::move(other))
    {
    }

    SkipWhileQueryableSetData(
        std::shared_ptr<IQueryableData<TObj>> data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    SkipWhileQueryableSetData(
        std::shared_ptr<QueryableData<TObj, std::set, TObj, TCompare, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : SkipWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    SkipWhileQueryableSetData & operator=(const SkipWhileQueryableSetData & other)
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>::operator =(other);
        return *this;
    }

    SkipWhileQueryableSetData & operator=(SkipWhileQueryableSetData && other) noexcept
    {
        if (this == &other) return *this;
        SkipWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>::operator =(
            std::move(other));
        return *this;
    }

    virtual ~SkipWhileQueryableSetData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<SkipWhileQueryableSetData<TObj, TCompare, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->insert(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that skips begin, end, Args... then this method can be a one liner

        std::set<TObj, TCompare, TAllocator> data(
            this->items->value_comp(),
            this->items->get_allocator());

        for (const TObj & value : *this)
        {
            data.insert(value);
        }

        return std::make_shared<QueryableSetData<TObj, TCompare, TAllocator>>(std::move(data));
    }
};

#endif
