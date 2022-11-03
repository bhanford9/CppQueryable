#ifndef CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLESETDATA_H
#define CPPQUERYABLE_QUERYABLE_TAKEWHILEQUERYABLEDATA_TAKEWHILEQUERYABLESETDATA_H

#include <set>

#include "TakeWhileQueryableData.hpp"

template <typename TObj, typename TCompare = std::less<TObj>, typename TAllocator = std::allocator<
              TObj>>
class TakeWhileQueryableSetData final : public TakeWhileQueryableData<
        TObj, std::set, TObj, TCompare, TAllocator>
{
public:
    TakeWhileQueryableSetData(const TakeWhileQueryableSetData & other)
        : TakeWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(other)
    {
    }

    TakeWhileQueryableSetData(TakeWhileQueryableSetData && other) noexcept
        : TakeWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(std::move(other))
    {
    }

    TakeWhileQueryableSetData(
        std::shared_ptr<IQueryableData<TObj>> data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    TakeWhileQueryableSetData(
        std::shared_ptr<QueryableData<TObj, std::set, TObj, TCompare, TAllocator>> && data,
        std::shared_ptr<IWhileCondition<TObj>> && condition)
        : TakeWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    TakeWhileQueryableSetData & operator=(const TakeWhileQueryableSetData & other)
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>::operator =(other);
        return *this;
    }

    TakeWhileQueryableSetData & operator=(TakeWhileQueryableSetData && other) noexcept
    {
        if (this == &other) return *this;
        TakeWhileQueryableData<TObj, std::set, TObj, TCompare, TAllocator>::operator =(
            std::move(other));
        return *this;
    }

    virtual ~TakeWhileQueryableSetData() override
    {
    }

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<TakeWhileQueryableSetData<TObj, TCompare, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->insert(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner

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
