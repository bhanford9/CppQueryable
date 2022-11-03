#ifndef CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H
#define CPPQUERYABLE_QUERYABLE_WHEREQUERYABLEMULTISETDATA_H

#include <set>

#include "WhereQueryableData.hpp"
#include "../QueryableMultiSetData.hpp"

template <typename TObj, typename TCompare = std::less<TObj>, typename TAllocator = std::allocator<
              TObj>>
class WhereQueryableMultiSetData final : public WhereQueryableData<
        TObj, std::multiset, TObj, TCompare, TAllocator>
{
public:
    WhereQueryableMultiSetData(const WhereQueryableMultiSetData & other)
        : WhereQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(other)
    {
    }

    WhereQueryableMultiSetData(WhereQueryableMultiSetData && other) noexcept
        : WhereQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(std::move(other))
    {
    }

    WhereQueryableMultiSetData(
        std::shared_ptr<IQueryableData<TObj>> data,
        std::function<bool(TObj)> condition)
        : WhereQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    WhereQueryableMultiSetData(
        std::shared_ptr<QueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>> && data,
        std::function<bool(TObj)> condition)
        : WhereQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>(
            std::move(data),
            std::move(condition))
    {
    }

    WhereQueryableMultiSetData & operator=(const WhereQueryableMultiSetData & other)
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>::operator =(other);
        return *this;
    }

    WhereQueryableMultiSetData & operator=(WhereQueryableMultiSetData && other) noexcept
    {
        if (this == &other) return *this;
        WhereQueryableData<TObj, std::multiset, TObj, TCompare, TAllocator>::operator =(
            std::move(other));
        return *this;
    }

    virtual ~WhereQueryableMultiSetData() override = default;

    virtual std::shared_ptr<IQueryableData<TObj>> Clone() override
    {
        return std::make_shared<WhereQueryableMultiSetData<TObj, TCompare, TAllocator>>(*this);
    }

    virtual void InternalAdd(TObj item) override
    {
        this->items->insert(item);
    }

    virtual std::shared_ptr<IQueryableData<TObj>> GetRealizedQueryableData() override
    {
        // If all QueryableData's have a constructor that takes begin, end, Args... then this method can be a one liner

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
